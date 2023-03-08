#pragma once
// clang-format off

/*
    LC ESP32 V1.0.h
    Part of Grbl_ESP32

    Pin assignments for the ESP32 Development Controller.
    https://github.com////////
    3
    
    2023----Jacob Chan

    Grbl_ESP32 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Grbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Grbl_ESP32.  If not, see <http://www.gnu.org/licenses/>.
*/

#define MACHINE_NAME            "LC_ESP32_V1"
#define DEBUG_MODE                    // comment to disable serial debug message output



#define STEPPERS_DISABLE_PIN                GPIO_NUM_33

#define X_LIMIT_PIN                         GPIO_NUM_36
#define X_STEP_PIN                          GPIO_NUM_25
#define X_DIRECTION_PIN                     GPIO_NUM_26

#define Y_LIMIT_PIN                         GPIO_NUM_39
#define Y_STEP_PIN                          GPIO_NUM_27
#define Y_DIRECTION_PIN                     GPIO_NUM_5

#define SPINDLE_TYPE                        SpindleType::LASER
#define LASER_OUTPUT_PIN                    GPIO_NUM_32
// #define LASER_ENABLE_PIN                    GPIO_NUM_22  // labeled SpinEnbl


#define ENABLE_SD_CARD
#define SDCARD_DET_PIN                      GPIO_NUM_35
// #define SDCARD_SCK_PIN                      GPIO_NUM_14
// #define SDCARD_DO_PIN                       GPIO_NUM_12
// #define SDCARD_DI_PIN                       GPIO_NUM_13
// #define SDCARD_CS_PIN                       GPIO_NUM_15

#define BUZZER_PIN                          GPIO_NUM_23  // labeled buzzer
#define MOTION_PIN                          GPIO_NUM_22  // labeled motion sensor
#define FLAME_PIN                           GPIO_NUM_34  // labeled flame sensor

#define MOTION_TAP_THRES 100          // the larger value, the more insensitive
#define MOTION_TAP_DUR 40             // the smaller value, the more insensitive

#define PIN_FLAME_USE_ADC             // comment to use digital read method for FLAME sensor
#define FLAME_ADC_THRES 1700          // the smaller value, the more insensitive
#define FLAME_CHECK_TIMES_THRES 5     // > FLAME_CHECK_TIMES_THRES, then triggered. the larger value, the more insensitive

#define PIN_MOTION_USE_INTERRUPT      // commment to use polling mode
#define PIN_FLAME_USE_INTERRUPT

#define PIN_I2C_SCL GPIO_NUM_18
#define PIN_I2C_SDA GPIO_NUM_19

#define DEFAULT_HOMING_ENABLE           1
#define DEFAULT_HARD_LIMIT_ENABLE       1  

#define DEFAULT_LASER_FULL_POWER 10
#define DEFAULT_HOMING_CYCLE_0  	((1<<X_AXIS)|(1<<Y_AXIS))






