#include "i2c_proc.h"

#define IMU_ADDRESS 212
#define GYRO_ADDRESS 0x22
#define ACCEL_ADDRESS 0x28

#define G_SENSITIVITY 8.75
#define A_SENSITIVITY .061

#define ACCELX_ADJ .242
#define ACCELY_ADJ .0022

void getGyroData(I2C_HandleTypeDef hi2c2, float* angx, float* angy, float* angz)
{
	/*HAL_I2C_DeInit(&hi2c2);
	HAL_I2C_Init(&hi2c2);

	uint8_t gyroData[6];
	uint8_t commandByte = 0x22;
	HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c2, 212, 1, 100);
	HAL_StatusTypeDef status1 = HAL_I2C_Master_Transmit(&hi2c2, 212, &commandByte, 1, HAL_MAX_DELAY);
	while (HAL_I2C_GetState(hi2c2) != HAL_I2C_STATE_READY)
    {
    }
	HAL_StatusTypeDef status2 = HAL_I2C_Master_Receive_DMA(&hi2c2, 212, gyroData, sizeof(gyroData));
	while (HAL_I2C_GetState(hi2c2) != HAL_I2C_STATE_READY)
    {
    }
	uint32_t error1 = HAL_I2C_GetError(&hi2c2);
	HAL_StatusTypeDef ret1 = HAL_I2C_IsDeviceReady(&hi2c2, 212, 1, 100);
	uint32_t error2 = HAL_I2C_GetError(&hi2c2);
	HAL_StatusTypeDef ret2 = HAL_I2C_IsDeviceReady(&hi2c2, 212, 1, 100);
	int16_t gyro[3];
	gyro[0] = (int16_t)((gyroData[1] << 8) | gyroData[0]); // X-axis
	gyro[1] = (int16_t)((gyroData[3] << 8) | gyroData[2]); // Y-axis
	gyro[2] = (int16_t)((gyroData[5] << 8) | gyroData[4]); // Z-axis*/

	uint8_t gyroData[6];
	HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(&hi2c2, 212, 0x22, I2C_MEMADD_SIZE_8BIT, gyroData, 6, HAL_MAX_DELAY);

	int16_t gyro[3];
	gyro[0] = (int16_t)((gyroData[1] << 8) | gyroData[0]); // X-axis
	gyro[1] = (int16_t)((gyroData[3] << 8) | gyroData[2]); // Y-axis
	gyro[2] = (int16_t)((gyroData[5] << 8) | gyroData[4]); // Z-axis

	float gyroX = gyro[0] * G_SENSITIVITY / 1000;
	float gyroY = gyro[1] * G_SENSITIVITY / 1000;
	float gyroZ = gyro[2] * G_SENSITIVITY / 1000; //deg/sec

	*angx = *angx + (gyroX * 1.0 / 60.0);
	*angy = *angy + (gyroY * 1.0 / 60.0);
	*angz = *angz + (gyroZ * 1.0 / 60.0);

	return;
}

void getAccelData(I2C_HandleTypeDef hi2c2, float* v0x, float* v0y, float* v0z, float* posx, float* posy, float* posz)
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

	*posx = *posx + (*v0x * (1.0/60)) + ((accelX * (1.0/60) * (1.0/60)) / 2.0);
	*posy = *posy + (*v0y * (1.0/60)) + ((accelY * (1.0/60) * (1.0/60)) / 2.0);
	*posz = *posz + (*v0z * (1.0/60)) + ((accelZ * (1.0/60) * (1.0/60)) / 2.0);

	*v0x = *v0x + accelX * (1.0/60);
	*v0y = *v0y + accelY * (1.0/60);
	*v0z = *v0z + accelZ * (1.0/60);

	return;
}
