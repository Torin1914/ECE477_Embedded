/**
 * @file Jetson_Bridge_Defines.h
 * @author Zachary Neel (zneel@purdue.edu)
 * @brief This library handles the bridge protocol between the Jetson and the micro
 * @version 0.1
 * @date 2023-09-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef JETSON_BRIDGE_TYPES_H
#define JETSON_BRIDGE_TYPES_H

typedef struct bridge_msg {
    uint8_t start_byte;
    uint8_t msg_id;
    uint8_t data [4];
    uint16_t crc;
} Jetson_Bridge_Msg_T;

#endif
