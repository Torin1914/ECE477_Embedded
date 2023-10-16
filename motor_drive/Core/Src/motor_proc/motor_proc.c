#include "motor_proc.h"

#define M1IN1 0b1
#define M1IN2 0b10
#define M2IN1 0b100
#define M2IN2 0b1000
#define M3IN1 0b10000
#define M3IN2 0b100000
#define M4IN1 0b10000
#define M4IN2 0b100000

void motor1_control(int direction, int speed)
{
	if(!speed)
	{
		HAL_GPIO_WritePin(GPIOC, M1IN1 | M1IN2, GPIO_PIN_RESET);
		return;
	}

	if(direction)
	{
		HAL_GPIO_WritePin(GPIOC, M1IN1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, M1IN2, GPIO_PIN_RESET);
		TIM2->CCR1 = speed;
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, M1IN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, M1IN2, GPIO_PIN_SET);
		TIM2->CCR1 = speed;
	}

	return;
}

void motor2_control(int direction, int speed)
{
	if(!speed)
	{
		HAL_GPIO_WritePin(GPIOC, M2IN1 | M2IN2, GPIO_PIN_RESET);
		return;
	}

	if(direction)
	{
		HAL_GPIO_WritePin(GPIOC, M2IN1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, M2IN2, GPIO_PIN_RESET);
		TIM2->CCR2 = speed;
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, M2IN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, M2IN2, GPIO_PIN_SET);
		TIM2->CCR2 = speed;
	}

	return;
}

void motor3_control(int direction, int speed)
{
	if(!speed)
	{
		HAL_GPIO_WritePin(GPIOA, M3IN1 | M3IN2, GPIO_PIN_RESET);
		return;
	}

	if(direction)
	{
		HAL_GPIO_WritePin(GPIOA, M3IN1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, M3IN2, GPIO_PIN_RESET);
		TIM2->CCR3 = speed;
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, M3IN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, M3IN2, GPIO_PIN_SET);
		TIM2->CCR3 = speed;
	}

	return;
}

void motor4_control(int direction, int speed)
{
	if(!speed)
	{
		HAL_GPIO_WritePin(GPIOC, M4IN1 | M4IN2, GPIO_PIN_RESET);
		return;
	}

	if(direction)
	{
		HAL_GPIO_WritePin(GPIOC, M4IN1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, M4IN2, GPIO_PIN_RESET);
		TIM2->CCR4 = speed;
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, M4IN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, M4IN2, GPIO_PIN_SET);
		TIM2->CCR4 = speed;
	}

	return;
}
