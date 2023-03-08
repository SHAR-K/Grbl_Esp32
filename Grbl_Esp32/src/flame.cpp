
/*
  flame.h - 
*/

#include "Grbl.h"


// flame pin initialization routine.
#ifdef PIN_FLAME_USE_INTERRUPT
  static bool flameTriggered = false;
void flameSensorISR()
  {
  flameTriggered = true;
  }
#endif



void FlameSensor_init()
{

  #ifdef FLAME_PIN
    pinMode(FLAME_PIN, INPUT);
    
    #ifdef PIN_FLAME_USE_INTERRUPT
       attachInterrupt(digitalPinToInterrupt(FLAME_PIN), flameSensorISR, FALLING);   // Attach Interrupt
    #endif

  #endif
  



  
      grbl_msg_sendf(CLIENT_ALL, MsgLevel::Info, "FlameSensor on pin %s", pinName(FLAME_PIN).c_str());
          xTaskCreate(FlameCheckTask,
                    "FlameCheckTask",
                    2048,
                    NULL,
                    5,  // priority
                    NULL);
}

void handleOnFlameTriggered()
{
  #ifdef DEBUG_MODE
    static int count = 0;
    grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "!!!flame triggered.:  %d ",count);
    Serial.println(++count);


     if (sys.state != State::Alarm && sys.state != State::Homing) {
        if (sys_rt_exec_alarm == ExecAlarm::None) {
            grbl_msg_sendf(CLIENT_ALL, MsgLevel::Info, "!!!Warning!!! --------Flame sensor");
            delay(10);
            mc_reset();                                // Initiate system kill.
            sys_rt_exec_alarm = ExecAlarm::HardLimit;  // Indicate hard limit critical event
            mc_homing_cycle( 0 );

        }
    } 
    #ifdef BUZZER_PIN
      turnOnBuzzer();
      delay(1000);
      turnOffBuzzer();
    #endif

  #endif
}


void flameSensorLoop()
{
  

    #ifdef PIN_FLAME_USE_INTERRUPT
        if (flameTriggered) {


            handleOnFlameTriggered();
            
            flameTriggered = false;           // clear flag

    
    
        }
        #endif
    
  }

void FlameCheckTask(void* pvParameters) {
    while (true) {
      flameSensorLoop();
      vTaskDelay(100 / portTICK_PERIOD_MS);    // delay a while
    }
}