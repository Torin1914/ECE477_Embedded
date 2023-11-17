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

#define JETSON_BRIDGE_TXBUFFERSIZE 16u

#define JETSON_BRIDGE_EXIT_SUCCESS 0x00u
#define JETSON_BRIDGE_EXIT_FAILED 0x01u
#define JETSON_BRIDGE_START_BYTE 0x55u

#define JETSON_BRIDGE_MSG_ID_MOTOR 0x00u
#define JETSON_BRIDGE_MSG_ID_SERVO 0x01u
#define JETSON_BRIDGE_MSG_ID_IMUGYROREQ 0x03u
#define JETSON_BRIDGE_MSG_ID_IMUACCELREQ 0x04u

#define JETSON_BRIDGE_MSG_ID_ANGLE_X 0x08u
#define JETSON_BRIDGE_MSG_ID_ANGLE_Y 0x09u
#define JETSON_BRIDGE_MSG_ID_ANGLE_Z 0x0Au

#define JETSON_BRIDGE_MSG_ID_ACCEL_X 0x05u
#define JETSON_BRIDGE_MSG_ID_ACCEL_Y 0x06u
#define JETSON_BRIDGE_MSG_ID_ACCEL_Z 0x07u

#define JETSON_BRIDGE_MSG_ID_NAK_INVALIDSTART 0xF8
#define JETSON_BRIDGE_MSG_ID_NAK_INVALIDID 0xF7


#endif
