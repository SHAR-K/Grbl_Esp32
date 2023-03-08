#pragma once

/*
  flame.h - 
*/



// flame pin initialization routine.
void FlameSensor_init();


void handleOnFlameTriggered();


void flameSensorLoop();
void FlameCheckTask(void* pvParameters);