#ifndef __MOTOR_DRIVER_H
#define __MOTOR_DRIVER_H

#include "stm32f0xx_hal.h"

void move_robot(int8_t, int8_t);
void rotate_robot(int8_t);
void crab_robot(int8_t);

void motor1_control(int8_t, int8_t);
void motor2_control(int8_t, int8_t);
void motor3_control(int8_t, int8_t);
void motor4_control(int8_t, int8_t);

#define M1IN1 0b1
#define M1IN2 0b10
#define M2IN1 0b100
#define M2IN2 0b1000
#define M3IN1 0b10000
#define M3IN2 0b100000
#define M4IN1 0b10000
#define M4IN2 0b100000

#endif
