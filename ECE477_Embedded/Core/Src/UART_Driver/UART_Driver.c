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
#include "Jetson_Bridge.h"
#include "main.h"

/* for memcpy*/
#include <string.h>

/* Static Definitions */
static UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;


/* Static Functions */
static uint8_t UART_Driver_TxBuffer[8u];
static uint8_t UART_Driver_RxBuffer[16u];
static uint8_t UART_Driver_RxMsg[8u];

static void UART_Driver_RxMsgHandler(void)
{
 void;
}

/**
  * @brief UART Initialization Function
  * @param None
  * @retval None
*/
void UART_Driver_Init(void)
{

      /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA1_Ch1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Ch1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Ch1_IRQn);
    /* DMA1_Ch2_3_DMA2_Ch1_2_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Ch2_3_DMA2_Ch1_2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Ch2_3_DMA2_Ch1_2_IRQn);

    __HAL_RCC_GPIOA_CLK_ENABLE();

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
    Error_Handler();
    }
}

void UART_Driver_TX(uint8_t *data_buff, uint8_t buff_len)
{
  memcpy(UART_Driver_TxBuffer, data_buff, buff_len);
  HAL_UART_Transmit_DMA(&huart1, UART_Driver_TxBuffer, sizeof(UART_Driver_TxBuffer));

}

void UART_Driver_RxInit(void)
{
  	HAL_UART_Receive_DMA (&huart1, UART_Driver_RxBuffer, sizeof(UART_Driver_RxBuffer));    /* USER CODE END WHILE */
}

void DMA1_Ch1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Ch1_IRQn 0 */

  /* USER CODE END DMA1_Ch1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA1_Ch1_IRQn 1 */

  /* USER CODE END DMA1_Ch1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel 2 to 3 and DMA2 channel 1 to 2 interrupts.
  */
void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart1);
}


void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
  memcpy(UART_Driver_RxMsg, UART_Driver_RxBuffer, sizeof(UART_Driver_RxMsg));
  Jetson_Bridge_RxBridgeMsg(UART_Driver_RxMsg, sizeof(UART_Driver_RxMsg));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  memcpy(UART_Driver_RxMsg, UART_Driver_RxBuffer + (sizeof(UART_Driver_RxBuffer) / 2), sizeof(UART_Driver_RxMsg));
  Jetson_Bridge_RxBridgeMsg(UART_Driver_RxMsg, sizeof(UART_Driver_RxMsg));
}
