/**
 * @file Jetson_Bridge.c
 * @author Zachary Neel (zneel@purdue.edu)
 * @brief This library handles the bridge protocol between the Jetson and the micro
 * @version 0.1
 * @date 2023-09-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* header file */
#include "Jetson_Bridge.h"
#include "UART_Driver.h"

/* for memcpy*/
#include <string.h>

void Jetson_Bridge_RxBridgeMsg(uint8_t * rx_buff, uint8_t rx_buff_size)
{
    (void) rx_buff;
}
