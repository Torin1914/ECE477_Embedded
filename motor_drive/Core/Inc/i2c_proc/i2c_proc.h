#ifndef __I2C_PROC_H
#define __I2C_PROC_H

#include "stm32f0xx_hal.h"

void i2c_proc_updateGyroData(I2C_HandleTypeDef);
void i2c_proc_updateAccelData(I2C_HandleTypeDef);

int16_t i2c_proc_getAngleX();
int16_t i2c_proc_getAngleY();
int16_t i2c_proc_getAngleZ();

int16_t i2c_proc_getAccelX();
int16_t i2c_proc_getAccelY();
int16_t i2c_proc_getAccelZ();

#endif
