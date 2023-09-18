/**
 * @file Jetson_Bridge.h
 * @author Zachary Neel (zneel@purdue.edu)
 * @brief This library handles the bridge protocol between the Jetson and the micro
 * @version 0.1
 * @date 2023-09-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef JETSON_BRIDGE_H
#define JETSON_BRIDGE_H

#include "main.h"

#define UART_DRIVER_START_BYTE 0x55

void Jetson_Bridge_RxBridgeMsg(uint8_t * rx_buff, uint8_t rx_buff_size);

#endif
