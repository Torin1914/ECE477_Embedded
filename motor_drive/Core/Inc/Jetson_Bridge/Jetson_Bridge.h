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
#include "Jetson_Bridge_Types.h"


void Jetson_Bridge_TxGyro();
void Jetson_Bridge_MailboxUpdate(void);
void Jetson_Bridge_TxMsg(Jetson_Bridge_Msg_T tx_msg);
void Jetson_Bridge_formatMsg(Jetson_Bridge_Msg_T * msg, uint8_t msg_id, uint8_t * data);
uint32_t Jetson_Bridge_RxBridgeMsg(uint8_t * rx_buff, uint8_t rx_buff_size);

#endif
