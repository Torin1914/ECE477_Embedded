#ifndef __I2C_PROC_H
#define __I2C_PROC_H

#include "stm32f0xx_hal.h"

void i2c_proc_updateGyroData(I2C_HandleTypeDef);
void i2c_proc_updateAccelData(I2C_HandleTypeDef);

float i2c_proc_getAngleX();
float i2c_proc_getAngleY();
float i2c_proc_getAngleZ();

float i2c_proc_getAccelX();
float i2c_proc_getAccelY();
float i2c_proc_getAccelZ();

#endif
