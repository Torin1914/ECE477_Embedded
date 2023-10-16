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
