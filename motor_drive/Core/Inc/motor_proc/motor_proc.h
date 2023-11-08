#ifndef __MOTOR_DRIVER_H
#define __MOTOR_DRIVER_H

#include "stm32f0xx_hal.h"

void move_robot(uint8_t, uint8_t);

void motor1_control(uint8_t, uint8_t);
void motor2_control(uint8_t, uint8_t);
void motor3_control(uint8_t, uint8_t);
void motor4_control(uint8_t, uint8_t);

#endif
