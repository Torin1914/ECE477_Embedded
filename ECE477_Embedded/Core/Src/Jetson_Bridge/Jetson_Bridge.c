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
#include "Jetson_Bridge_Defines.h"
#include "Jetson_Bridge_Types.h"
#include "UART_Driver.h"

/* for memcpy*/
#include <string.h>

static uint16_t Jetson_Bridge_getCRC(Jetson_Bridge_Msg_T msg)
{
    return 0u;
}

void Jetson_Bridge_TxMsg(Jetson_Bridge_Msg_T tx_msg)
{
    uint8_t buff[8u];
    buff[0] = tx_msg.start_byte;
    buff[1] = tx_msg.msg_id;
    memcpy(&buff[2], tx_msg.data, sizeof(tx_msg.data));
    memcpy(&buff[6], &tx_msg.crc, sizeof(tx_msg.crc));
    UART_Driver_TX(buff, sizeof(buff));
}



void Jetson_Bridge_RxBridgeMsg(uint8_t * rx_buff, uint8_t rx_buff_size)
{
    Jetson_Bridge_Msg_T rx_msg;
    rx_msg.start_byte = rx_buff[0];
    rx_msg.msg_id = rx_buff[1];
    memcpy(rx_msg.data, &rx_buff[2], sizeof(rx_msg.data));
    memcpy(&rx_msg.crc, &rx_buff[6], sizeof(rx_msg.crc));

    if(rx_msg.start_byte != JETSON_BRIDGE_START_BYTE)
    {
        Jetson_Bridge_Msg_T tx_nak;
        tx_nak.start_byte = JETSON_BRIDGE_START_BYTE;
        tx_nak.msg_id = JETSON_BRIDGE_MSG_ID_NAK;
        tx_nak.data[0u] = 0u;
        tx_nak.data[1u] = 0u;
        tx_nak.data[2u] = 0u;
        tx_nak.data[3u] = 0u;
        tx_nak.crc = Jetson_Bridge_getCRC(tx_nak);
        Jetson_Bridge_TxMsg(tx_nak);
        UART_Driver_RxInit(); /* reinitialize the DMA to clear the RX buffer */
    }
    (void) rx_buff;
}
