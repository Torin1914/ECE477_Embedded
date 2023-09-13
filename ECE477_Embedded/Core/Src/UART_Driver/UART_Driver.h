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


/* Function Definitions */
void UART_Driver_Init(void);
void UART_Driver_TX(uint8_t *data_buff, uint8_t buff_len);
void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void);
void USART1_IRQHandler(void);

#endif