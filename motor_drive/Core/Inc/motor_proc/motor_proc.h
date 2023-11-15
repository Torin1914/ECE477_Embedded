#ifndef __MOTOR_DRIVER_H
#define __MOTOR_DRIVER_H

#include "stm32f0xx_hal.h"

void move_robot(int8_t, int8_t);
void crab_robot(int8_t);

void motor1_control(int8_t, int8_t);
void motor2_control(int8_t, int8_t);
void motor3_control(int8_t, int8_t);
void motor4_control(int8_t, int8_t);

#endif
