#ifndef __I2C_PROC_H
#define __I2C_PROC_H

#include "stm32f0xx_hal.h"

void getGyroData(I2C_HandleTypeDef);
void getAccelData(I2C_HandleTypeDef*);

#endif
