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

#ifndef JETSON_BRIDGE_DEFINES_H
#define JETSON_BRIDGE_DEFINES_H

#define JETSON_BRIDGE_EXIT_SUCCESS 0x00
#define JETSON_BRIDGE_EXIT_FAILED 0x01
#define JETSON_BRIDGE_START_BYTE 0x55
#define JETSON_BRIDGE_MSG_ID_NAK 0xF8
#define JETSON_BRIDGE_MSG_ID_MOTOR 0x00
#define JETSON_BRIDGE_MSG_ID_IMUREQ 0x02
#define JETSON_BRIDGE_MSG_ID_SERVO 0x01


#endif
