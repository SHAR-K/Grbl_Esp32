/*
  Probe.cpp -
*/

#include "Grbl.h"

#ifdef BUZZER_PIN
  void turnOnBuzzer(){
    digitalWrite(BUZZER_PIN, HIGH);
  }

  void turnOffBuzzer(){
    digitalWrite(BUZZER_PIN, LOW);
  }
  
  void BuzzerON(){
    grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "Buzzer on");
    turnOnBuzzer();
    delay(500);
    turnOffBuzzer();
  }

#endif

// buzzer pin initialization routine.
void buzzer_init() {

  if (BUZZER_PIN != UNDEFINED_PIN) {
    
    #ifdef DISABLE_BUZZER_PIN_PULL_UP
      pinMode(BUZZER_PIN, INPUT);
    #else
      pinMode(BUZZER_PIN, OUTPUT);  // Enable internal pull-up resistors. Normal high operation.
      turnOffBuzzer();
    #endif

    grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "Buzzer on pin %s", pinName(BUZZER_PIN).c_str());
  }
}



  

