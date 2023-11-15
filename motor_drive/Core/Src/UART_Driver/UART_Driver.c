/**
 * @file UART_Driver.c
 * @author Zachary Neel (zneel@purdue.edu)
 * @brief
 * @version 0.1
 * @date 2023-09-13
 *
 * @copyright Copyright (c) 2023
 *
 */

/* header file */
#include "UART_Driver.h"
#include "UART_Driver_Defines.h"
#include "Jetson_Bridge.h"
#include "main.h"

/* for memcpy*/
#include <string.h>

/* Static Functions */
static uint8_t UART_Driver_TxBuffer[8u];
static uint8_t UART_Driver_RxBuffer[16u];
static uint8_t UART_Driver_RxMsg[8u];


uint8_t UART_Driver_BridgeMsg(Jetson_Bridge_Msg_T tx_msg)
{
    uint8_t buff[8u];
    buff[0] = tx_msg.start_byte;
    buff[1] = tx_msg.msg_id;
    memcpy(&buff[2], tx_msg.data, sizeof(tx_msg.data));
    memcpy(&buff[6], &tx_msg.crc, sizeof(tx_msg.crc));

    return UART_Driver_TX(buff, sizeof(buff));
}

uint8_t UART_Driver_TX(uint8_t *data_buff, uint8_t buff_len)
{
  memcpy(UART_Driver_TxBuffer, data_buff, buff_len);
  if (HAL_UART_Transmit_DMA(&huart1, UART_Driver_TxBuffer, sizeof(UART_Driver_TxBuffer)) == HAL_BUSY)
  {
    return UART_DRIVER_BUSY;
  }
  else
  {
    return UART_DRIVER_SUCCESS;
  }
}

void UART_Driver_RxInit(void)
{
  	HAL_UART_Receive_DMA(&huart1, UART_Driver_RxBuffer, sizeof(UART_Driver_RxBuffer));    /* USER CODE END WHILE */
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
  memcpy(UART_Driver_RxMsg, UART_Driver_RxBuffer, sizeof(UART_Driver_RxMsg));
  (void) Jetson_Bridge_RxBridgeMsg(UART_Driver_RxMsg, sizeof(UART_Driver_RxMsg));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  memcpy(UART_Driver_RxMsg, UART_Driver_RxBuffer + (sizeof(UART_Driver_RxBuffer) / 2), sizeof(UART_Driver_RxMsg));
  (void) Jetson_Bridge_RxBridgeMsg(UART_Driver_RxMsg, sizeof(UART_Driver_RxMsg));
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Transmit next message in the buffer */
  Jetson_Bridge_MailboxUpdate();
}
