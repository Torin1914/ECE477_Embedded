#include "servo_proc.h"

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
	if(!close)
	{
		servo1_control(120);
		servo2_control(50);
		HAL_Delay(1000);
	}
	else
	{
		servo1_control(160);
		HAL_Delay(150);
		servo2_control(120);
	}
 }