#pragma once

/*
  motionsensor.h - 
*/



// flame pin initialization routine.
void initMotionSensor();
void motionSensorISR();


void handleOnMotionTriggered();


void motionSensorLoop();
void MotionCheckTask(void* pvParameters);