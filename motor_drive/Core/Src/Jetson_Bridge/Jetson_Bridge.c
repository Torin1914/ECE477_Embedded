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
#include "UART_Driver_Defines.h"
#include "servo_proc.h"
#include "motor_proc.h"
#include "i2c_proc.h"

#define G_SENSITIVITY 8.75


/* for memcpy*/
#include <string.h>

/* list of mailboxes/messages waited to be transmitted */
static Jetson_Bridge_Msg_T Jetson_Bridge_TxBuffer[JETSON_BRIDGE_TXBUFFERSIZE];
static uint8_t Jetson_Bridge_TxIdx = 0;
static uint8_t Jetson_Bridge_TxCurr = 0;


static uint16_t Jetson_Bridge_getCRC(Jetson_Bridge_Msg_T * msg)
{
    return 0u;
}

void Jetson_Bridge_TxGyro()
{
    /* format gyro_x message */
    int32_t angle_x = (int16_t) i2c_proc_getAngleX();
    /*transmit gyro_x message*/
    Jetson_Bridge_TxMsg(JETSON_BRIDGE_MSG_ID_ANGLE_X, (uint8_t *) &angle_x);

    /* format gyro_y message */
    int32_t angle_y = i2c_proc_getAngleY();
    /*transmit gyro_y message*/
    Jetson_Bridge_TxMsg(JETSON_BRIDGE_MSG_ID_ANGLE_Y, (uint8_t *) &angle_y);

    int32_t angle_z = i2c_proc_getAngleZ();
    /*transmit gyro_z message*/
    Jetson_Bridge_TxMsg(JETSON_BRIDGE_MSG_ID_ANGLE_Z, (uint8_t *) &angle_z);
}

void Jetson_Bridge_TxAccel()
{
    /* format gyro_x message */
    int32_t accel_x = (int16_t) i2c_proc_getAccelX();
    /*transmit gyro_x message*/
    Jetson_Bridge_TxMsg(JETSON_BRIDGE_MSG_ID_ACCEL_X, (uint8_t *) &accel_x);

    /* format gyro_y message */
    int32_t accel_y = i2c_proc_getAccelY();
    /*transmit gyro_y message*/
    Jetson_Bridge_TxMsg(JETSON_BRIDGE_MSG_ID_ACCEL_Y, (uint8_t *) &accel_y);

    int32_t accel_z = i2c_proc_getAccelZ();
    /*transmit gyro_z message*/
    Jetson_Bridge_TxMsg(JETSON_BRIDGE_MSG_ID_ACCEL_Z, (uint8_t *) &accel_z);
}

/**
 * @brief Transmit message by adding it to the TX fifo
 * 
 * @param tx_msg
 */
void Jetson_Bridge_TxMsg(uint8_t msg_id, uint8_t * data)
{

    Jetson_Bridge_TxBuffer[Jetson_Bridge_TxIdx].start_byte = JETSON_BRIDGE_START_BYTE;
    Jetson_Bridge_TxBuffer[Jetson_Bridge_TxIdx].msg_id = msg_id;
    memcpy(Jetson_Bridge_TxBuffer[Jetson_Bridge_TxIdx].data, data, sizeof(Jetson_Bridge_TxBuffer[Jetson_Bridge_TxIdx].data));
    Jetson_Bridge_TxBuffer[Jetson_Bridge_TxIdx].crc = Jetson_Bridge_getCRC(&Jetson_Bridge_TxBuffer[Jetson_Bridge_TxIdx]);

    Jetson_Bridge_TxIdx = (Jetson_Bridge_TxIdx + 1) % JETSON_BRIDGE_TXBUFFERSIZE;
    if(UART_Driver_BridgeMsg(Jetson_Bridge_TxBuffer[Jetson_Bridge_TxCurr]) == UART_DRIVER_SUCCESS)
    {
        Jetson_Bridge_TxCurr = (Jetson_Bridge_TxCurr + 1) % JETSON_BRIDGE_TXBUFFERSIZE;
    }
}

/**
 * @brief 
 * 
 * @param tx_msg 
 */

void Jetson_Bridge_MailboxUpdate(void)
{

    if(Jetson_Bridge_TxCurr != Jetson_Bridge_TxIdx)
    {
        if(UART_Driver_BridgeMsg(Jetson_Bridge_TxBuffer[Jetson_Bridge_TxCurr]) == UART_DRIVER_SUCCESS)
        {
            Jetson_Bridge_TxCurr = (Jetson_Bridge_TxCurr + 1) % JETSON_BRIDGE_TXBUFFERSIZE;
        }
    }
}


uint32_t Jetson_Bridge_RxBridgeMsg(uint8_t * rx_buff, uint8_t rx_buff_size)
{
    /* nak buffer in case needed */
    uint32_t data = 0;

    /* copy RX buffer to a message */
    Jetson_Bridge_Msg_T rx_msg;
    rx_msg.start_byte = rx_buff[0];
    rx_msg.msg_id = rx_buff[1];
    memcpy(rx_msg.data, &rx_buff[2], sizeof(rx_msg.data));
    memcpy(&rx_msg.crc, &rx_buff[6], sizeof(rx_msg.crc));

    /* check for start byte. if invalid start byte, return error */
    if(rx_msg.start_byte != JETSON_BRIDGE_START_BYTE)
    {
        Jetson_Bridge_TxMsg(JETSON_BRIDGE_MSG_ID_NAK_INVALIDSTART, (uint8_t *) &data);
        return JETSON_BRIDGE_EXIT_FAILED;
    }

    switch(rx_msg.msg_id)
    {
        case JETSON_BRIDGE_MSG_ID_MOTOR:
            move_robot(((int8_t) rx_msg.data[0]) - 100, ((int8_t) rx_msg.data[1]) - 100);
            break;
        case JETSON_BRIDGE_MSG_ID_SERVO:
            servo_proc_GrabBall(rx_msg.data[0]);
            break;
        case JETSON_BRIDGE_MSG_ID_IMUGYROREQ:
            Jetson_Bridge_TxGyro();
            break;
        case JETSON_BRIDGE_MSG_ID_IMUACCELREQ:
            Jetson_Bridge_TxAccel();
            break;
        default:
            uint32_t data = 0;
            Jetson_Bridge_TxMsg(JETSON_BRIDGE_MSG_ID_NAK_INVALIDID, (uint8_t *) &data);
            return JETSON_BRIDGE_EXIT_FAILED;
    }
    (void) rx_buff;

    return JETSON_BRIDGE_EXIT_SUCCESS;
}
