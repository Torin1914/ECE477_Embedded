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
		servo2_control(20);
	}
	else
	{
		servo2_control(120);
		for(int i=0;i<1000;i++)for(int j=0;j<400;j++)__NOP();
		servo1_control(160);
	}
 }
