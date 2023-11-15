#include "motor_proc.h"

#define M1IN1 0b1
#define M1IN2 0b10
#define M2IN1 0b100
#define M2IN2 0b1000
#define M3IN1 0b10000
#define M3IN2 0b100000
#define M4IN1 0b10000
#define M4IN2 0b100000

//MOTOR 1 & 2 are LEFT MOTORS
//MOTOR 2 & 4 are BACK MOTORS

#define CW 1
#define CCW 0

void move_robot(int8_t forward_effort, int8_t turning_effort) //TURNING EFFORT CANNOT BE GREATER THAN FORWARD EFFORT
{
	uint8_t direction = CW;
	if(forward_effort  < 0)
	{
		direction = CCW;
		forward_effort *= -1;
	}

	if(turning_effort <= 0)
	{
		motor1_control(direction, forward_effort + (turning_effort * forward_effort / 100));
		motor2_control(direction, forward_effort + (turning_effort * forward_effort / 100));
		motor3_control(direction, forward_effort);
		motor4_control(direction, forward_effort);
	}
	else
	{
		motor1_control(direction, forward_effort);
		motor2_control(direction, forward_effort);
		motor3_control(direction, forward_effort - (turning_effort * forward_effort / 100));
		motor4_control(direction, forward_effort - (turning_effort * forward_effort / 100));
	}

	return;
}

void crab_robot(int8_t effort)
{
	uint8_t direction1 = CW;
	uint8_t direction2 = CCW;
	if(effort  < 0)
	{
		direction1 = CCW;
		direction2 = CW;
		effort *= -1;
	}

	motor1_control(direction1, effort);
	motor2_control(direction2, effort);
	motor3_control(direction1, effort);
	motor4_control(direction2, effort);

}

void motor1_control(int8_t direction, int8_t speed)
{
	if(!speed)
	{
		HAL_GPIO_WritePin(GPIOC, M1IN1 | M1IN2, GPIO_PIN_RESET);
		return;
	}

	if(!direction)
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

void motor2_control(int8_t direction, int8_t speed)
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

void motor3_control(int8_t direction, int8_t speed)
{
	if(!speed)
	{
		HAL_GPIO_WritePin(GPIOA, M3IN1 | M3IN2, GPIO_PIN_RESET);
		return;
	}

	if(!direction)
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

void motor4_control(int8_t direction, int8_t speed)
{
	if(!speed)
	{
		HAL_GPIO_WritePin(GPIOC, M4IN1 | M4IN2, GPIO_PIN_RESET);
		return;
	}

	if(!direction)
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
