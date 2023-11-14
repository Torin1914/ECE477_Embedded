/**
 * @file UART_Driver.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef UART_DRIVER_H
#define UART_DRIVER_H

/* Includes */
#include "stm32f0xx_hal.h"
#include "stm32f091xc.h"
#include "Jetson_Bridge_Types.h"
#include "Jetson_Bridge_Types.h"



/* Function Definitions */
uint8_t UART_Driver_TX(uint8_t *data_buff, uint8_t buff_len);
uint8_t UART_Driver_BridgeMsg(Jetson_Bridge_Msg_T tx_msg);
void UART_Driver_RxInit(void);

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
#endif
