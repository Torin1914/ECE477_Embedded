#include "servo_proc.h"

uint8_t servo_closed = 0;

void servo1_control(int angle)
{
	if(angle >= 0 && angle <= 180)
	{
		TIM3->CCR1 = servo_angle(angle);
	}
}

void servo2_control(int angle)
{
	if(angle >= 0 && angle <= 180)
	{
		TIM3->CCR2 = servo_angle(angle);
	}
}

int servo_angle(int angle)
{
	return (angle * (1000.0 / 90) + 500);
}

/**
 * @brief 
 * 
 * @param close 0 if open, else if closed
 */
 void servo_proc_GrabBall(uint8_t close)
 {
	servo_closed = close;
 }

 uint8_t servo_proc_GetClose()
 {
	return servo_closed;
 }
