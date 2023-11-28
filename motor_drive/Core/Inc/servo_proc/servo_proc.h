#ifndef __SERVO_PROC_H
#define __SERVO_PROC_H

#include "stm32f0xx_hal.h"

void servo1_control(int);
void servo2_control(int);
int servo_angle(int);
void servo_proc_GrabBall(uint8_t close);
 uint8_t servo_proc_GetClose();

#endif
