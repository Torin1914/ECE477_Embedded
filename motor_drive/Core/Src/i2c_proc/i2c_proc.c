#include "i2c_proc.h"
#include "motor_proc.h"
#define IMU_ADDRESS 212
#define GYRO_ADDRESS 0x22
#define ACCEL_ADDRESS 0x28

#define G_SENSITIVITY 8.75
#define A_SENSITIVITY .061

#define ACCELX_ADJ .242
#define ACCELY_ADJ .0022

static float angle_x;
static float angle_y;
static float angle_z;

static float pos_x;
static float pos_y;
static float pos_z;

static float vel_x;
static float vel_y;
static float vel_z;

void i2c_proc_updateGyroData(I2C_HandleTypeDef hi2c2)
{
	uint8_t gyroData[6];
	HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(&hi2c2, 212, 0x22, I2C_MEMADD_SIZE_8BIT, gyroData, 6, HAL_MAX_DELAY);

	int16_t gyro[3];
	gyro[0] = (int16_t)((gyroData[1] << 8) | gyroData[0]); // X-axis
	gyro[1] = (int16_t)((gyroData[3] << 8) | gyroData[2]); // Y-axis
	gyro[2] = (int16_t)((gyroData[5] << 8) | gyroData[4]); // Z-axis

	float gyroX = gyro[0] * G_SENSITIVITY / 1000;
	float gyroY = gyro[1] * G_SENSITIVITY / 1000;
	float gyroZ = gyro[2] * G_SENSITIVITY / 1000; //deg/sec

	//integration of gyro to get approx angle since reset
	angle_x = angle_x + (gyroX * 1.0 / 60.0);
	angle_y = angle_y + (gyroY * 1.0 / 60.0);
	angle_z = angle_z + (gyroZ * 1.0 / 60.0);

	return;
}

void i2c_proc_updateAccelData(I2C_HandleTypeDef hi2c2)
{
	uint8_t accelData[6];
	HAL_I2C_Mem_Read(&hi2c2, IMU_ADDRESS, ACCEL_ADDRESS, I2C_MEMADD_SIZE_8BIT, accelData, 6, HAL_MAX_DELAY);

	int16_t accel[3];
	accel[0] = (int16_t)((accelData[1] << 8) | accelData[0]); // X-axis
	accel[1] = (int16_t)((accelData[3] << 8) | accelData[2]); // Y-axis
	accel[2] = (int16_t)((accelData[5] << 8) | accelData[4]); // Z-axis

	float accelX = (accel[0] * A_SENSITIVITY / 1000 * 9.81) - ACCELX_ADJ;
	float accelY = (accel[1] * A_SENSITIVITY / 1000 * 9.81) - ACCELY_ADJ;
	float accelZ = accel[2] * A_SENSITIVITY / 1000 * 9.81; //m/s2

	vel_x = vel_x + accelX * (1.0/60);
	vel_y = vel_y + accelY * (1.0/60);
	vel_z = vel_z + accelZ * (1.0/60);

	pos_x = pos_x + (vel_x * (1.0/60)) + ((accelX * (1.0/60) * (1.0/60)) / 2.0);
	pos_y = pos_y + (vel_y * (1.0/60)) + ((accelY * (1.0/60) * (1.0/60)) / 2.0);
	pos_z = pos_z + (vel_z * (1.0/60)) + ((accelZ * (1.0/60) * (1.0/60)) / 2.0);

	return;
}

float i2c_proc_getAngleX()
{
	return angle_x;
}

float i2c_proc_getAngleY()
{
	return angle_y;
}

float i2c_proc_getAngleZ()
{
	return angle_y;
}

float i2c_proc_getAccelX()
{
	return pos_x;
}

float i2c_proc_getAccelY()
{
	return pos_y;
}

float i2c_proc_getAccelZ()
{
	return pos_z;
}
