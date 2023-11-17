#include "i2c_proc.h"
#include "motor_proc.h"
#define IMU_ADDRESS 212
#define GYRO_ADDRESS 0x22
#define ACCEL_ADDRESS 0x28

#define G_SENSITIVITY 8.75
#define A_SENSITIVITY .061

#define ACCELX_ADJ .242
#define ACCELY_ADJ .0022

static int16_t angle_x;
static int16_t angle_y;
static int16_t angle_z;

static int16_t accel_x;
static int16_t accel_y;
static int16_t accel_z;

void i2c_proc_updateGyroData(I2C_HandleTypeDef hi2c2)
{
	uint8_t gyroData[6];
	(void) HAL_I2C_Mem_Read(&hi2c2, 212, 0x22, I2C_MEMADD_SIZE_8BIT, gyroData, 6, HAL_MAX_DELAY);

	int16_t gyro[3];
	gyro[0] = (int16_t)((gyroData[1] << 8) | gyroData[0]); // X-axis
	gyro[1] = (int16_t)((gyroData[3] << 8) | gyroData[2]); // Y-axis
	gyro[2] = (int16_t)((gyroData[5] << 8) | gyroData[4]); // Z-axis

	__disable_irq();
	angle_x = gyro[0];
	angle_y = gyro[1];
	angle_z = gyro[2]; //deg/sec
	__enable_irq();

	return;
}

void i2c_proc_updateAccelData(I2C_HandleTypeDef hi2c2)
{
	uint8_t accelData[6];
	(void) HAL_I2C_Mem_Read(&hi2c2, IMU_ADDRESS, ACCEL_ADDRESS, I2C_MEMADD_SIZE_8BIT, accelData, 6, HAL_MAX_DELAY);

	int16_t accel[3];
	accel[0] = (int16_t)((accelData[1] << 8) | accelData[0]); // X-axis
	accel[1] = (int16_t)((accelData[3] << 8) | accelData[2]); // Y-axis
	accel[2] = (int16_t)((accelData[5] << 8) | accelData[4]); // Z-axis

	__disable_irq();
	accel_x = accel[0];
	accel_y = accel[1];
	accel_z = accel[2];
	__enable_irq();

	return;
}

int16_t i2c_proc_getAngleX()
{
	return angle_x;
}

int16_t i2c_proc_getAngleY()
{
	return angle_y;
}

int16_t i2c_proc_getAngleZ()
{
	return angle_z;
}

int16_t i2c_proc_getAccelX()
{
	return accel_x;
}

int16_t i2c_proc_getAccelY()
{
	return accel_y;
}

int16_t i2c_proc_getAccelZ()
{
	return accel_z;
}
