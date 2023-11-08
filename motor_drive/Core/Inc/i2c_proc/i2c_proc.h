#ifndef __I2C_PROC_H
#define __I2C_PROC_H

#include "stm32f0xx_hal.h"

void getGyroData(I2C_HandleTypeDef, float*, float*, float*);
void getAccelData(I2C_HandleTypeDef, float*, float*, float*, float*, float*, float*);

#endif
