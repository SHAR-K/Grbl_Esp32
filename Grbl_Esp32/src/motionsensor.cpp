
/*
  flame.h - 
*/

#include "Grbl.h"

ADXL345 motionSensor = ADXL345();

// flame pin initialization routine.

#ifdef PIN_MOTION_USE_INTERRUPT
  static bool motionTriggered = false;
  void motionSensorISR()
    {
    motionTriggered = true;
    }
#endif

void initMotionSensor()
{
  motionSensor.powerOn();                     // Power on the ADXL345
  grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "Motion sensor poweron %s", pinName(PIN_I2C_SDA).c_str());

  // validate device ID
  while (motionSensor.getDeviceID() != 0xE5) {
    grbl_msg_sendf(CLIENT_ALL, MsgLevel::Info, "Could not find a valid adxl345 sensor, check wiring!");
    delay(500);
    motionSensor.powerOn();  // try again
  }

  motionSensor.setRangeSetting(16);           // Give the range settings
                                              // Accepted values are 2g, 4g, 8g or 16g
                                              // Higher Values = Wider Measurement Range
                                              // Lower Values = Greater Sensitivity
   
  // motionSensor.setActivityXYZ(1, 1, 1);       // Set to activate movement detection in the axes "motionSensor.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  // motionSensor.setActivityThreshold(75);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)
 
  motionSensor.setTapDetectionOnXYZ(1, 1, 1); // Detect taps in the directions turned ON "motionSensor.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)
 
  // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
  motionSensor.setTapThreshold(MOTION_TAP_THRES);           // 62.5 mg per increment
  motionSensor.setTapDuration(MOTION_TAP_DUR);            // 625 μs per increment
 
  // Setting all interupts to take place on INT1 pin
  motionSensor.setImportantInterruptMapping(1, 1, 1, 1, 1);     // Sets "motionSensor.setEveryInterruptMapping(single tap, double tap, free fall, activity, inactivity);" 
                                                        // Accepts only 1 or 2 values for pins INT1 and INT2. This chooses the pin on the ADXL345 to use for Interrupts.
                                                        // This library may have a problem using INT2 pin. Default to INT1 pin.
  // interrupt signal invert, LOW level on active
  motionSensor.setInterruptLevelBit(1);
  // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
  // motionSensor.ActivityINT(1);
  motionSensor.singleTapINT(1);

  #ifdef MOTION_PIN
    pinMode(MOTION_PIN, INPUT);
    #ifdef PIN_MOTION_USE_INTERRUPT
      attachInterrupt(digitalPinToInterrupt(MOTION_PIN), motionSensorISR, FALLING);   // Attach Interrupt
    #endif
  #endif
  
  grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "MotionSensor on pin %s", pinName(MOTION_PIN).c_str());

  xTaskCreate(MotionCheckTask,
              "MotionCheckTask",
              2048,
              NULL,
              5,  // priority
              NULL);
}
void handleOnMotionTriggered()
{
  #ifdef DEBUG_MODE
    static int count = 0;
    grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "!!!motion triggered. total count:  %d ",++count);



    if (sys.state != State::Alarm && sys.state != State::Homing) {
      if (sys_rt_exec_alarm == ExecAlarm::None) {

          grbl_msg_sendf(CLIENT_ALL, MsgLevel::Info, "!!!Warning!!! Check the machine state!!");
          mc_reset();                                // Initiate system kill.
          sys_rt_exec_alarm = ExecAlarm::MOTION;  // Indicate hard limit critical event

      }
    }   




    #ifdef BUZZER_PIN
        grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "Buzzer on");
        turnOnBuzzer();
        delay(500);
        turnOffBuzzer();

    #endif

  #endif
}
void motionSensorLoop()
{

  #ifdef PIN_MOTION_USE_INTERRUPT
    if (motionTriggered) {

      handleOnMotionTriggered();
      motionSensor.getInterruptSource(); // clear int status
      motionTriggered = false;           // clear flag
//      grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "loooooooooooooooooooooooop ");
}
  #else // polling mode
    int state = digitalRead(MOTION_PIN);
    if (!state)
    {
      handleOnMotionTriggered();
      motionSensor.getInterruptSource(); // clear int status
    }

  #endif // PIN_MOTION_USE_INTERRUPT

}






void MotionCheckTask(void* pvParameters) {
    while (true) {
      motionSensorLoop();
      vTaskDelay(100 / portTICK_PERIOD_MS);    // delay a while
    }


//     if (limit_sw_queue == NULL) {
//         limit_sw_queue = xQueueCreate(10, sizeof(int));
//         xTaskCreate(limitCheckTask,
//                     "limitCheckTask",
//                     2048,
//                     NULL,
//                     5,  // priority
//                     NULL);
     }