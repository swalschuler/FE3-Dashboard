/* ========================================
 * This file is used for declaring functions which will be executed for a particular CAN ID.
 * ========================================

    Make sure to use macros to access data bytes. They are not in
    the order you expect! These macros were defined by Cypress in CAN_1.h.
    
    CAN_1_DATA_BYTE_1    
    CAN_1_DATA_BYTE_2    
    CAN_1_DATA_BYTE_3    
    CAN_1_DATA_BYTE_4    
    CAN_1_DATA_BYTE_5
    CAN_1_DATA_BYTE_6
    CAN_1_DATA_BYTE_7
    CAN_1_DATA_BYTE_8
*/

#include "can_manga_handlers.h"
    
// Define and initialize variables
volatile MangaMessage CAPACITOR_VOLT = {0, 0};
volatile MangaMessage CURTIS_FAULT_CHECK = {0, 0};
volatile MangaMessage CURTIS_HEART_BEAT_CHECK = {0, 0};
volatile MangaMessage ACK_RX = {0, 0};
volatile MangaMessage ERROR_TOLERANCE = {0, 0};
volatile MangaMessage ABS_MOTOR_RPM = {0, 0};
volatile MangaMessage THROTTLE_HIGH = {0, 0};
volatile MangaMessage THROTTLE_LOW = {0, 0};
    
// If you ever see 0xA6, just set CURTIS to 1 (so there has been a fault)
void curtisFaultHandler()
{
    can_manga_message_update(&CURTIS_FAULT_CHECK, 0x0);
}

uint8_t manga_getCurtisFaultCheck()
{
    if (CURTIS_FAULT_CHECK.count == 0)
        return 0;
    else
    {
        CURTIS_FAULT_CHECK.count -= 1;
        return 1; // Has a fault message available
    }
}

void curtisHeartBeatHandler()
{
    can_manga_message_update(&CURTIS_HEART_BEAT_CHECK, 0x0);
}

uint8_t manga_getCurtisHeartBeatCheck()
{
    if (CURTIS_HEART_BEAT_CHECK.count == 0)
        return 0;
    else
    {
        CURTIS_HEART_BEAT_CHECK.count -= 1;
        return 1; // Has a heartbeat message available
    }
}

// Handles capacitor voltage 
void capacitorVoltHandler(CAN_RX_STRUCT msg)
{
    uint8_t capacitorVolt = msg.rxdata.byte[CAN_DATA_BYTE_1];
    uint8_t absMotorRPM = msg.rxdata.byte[CAN_DATA_BYTE_5];
    
    can_manga_message_update(&CAPACITOR_VOLT, capacitorVolt);
    can_manga_message_update(&ABS_MOTOR_RPM, absMotorRPM);
}

uint8_t manga_getCapacitorVoltage()
{
    if (CAPACITOR_VOLT.count == 0)
        return 0;
    else
    {
        CAPACITOR_VOLT.count -= 1;
        return CAPACITOR_VOLT.value;
    }
}

uint8_t manga_getAbsMotorRPM()
{
    if (ABS_MOTOR_RPM.count == 0)
        return 0;
    else
    {
        ABS_MOTOR_RPM.count -= 1;
        return ABS_MOTOR_RPM.value;
    }
}


void ackReceivedHandler(CAN_RX_STRUCT msg)
{
    uint8_t ackRx = msg.rxdata.byte[CAN_DATA_BYTE_1];

    can_manga_message_update(&ACK_RX, ackRx);
}

uint8_t manga_getAckReceive()
{
    if (ACK_RX.count == 0)
        return 0;
    else
    {
        ACK_RX.count -= 1;
        return ACK_RX.value;
    }
}

void errorToleranceHandler(CAN_RX_STRUCT msg)
{
    uint8_t errotTolerance = msg.rxdata.byte[CAN_DATA_BYTE_1];

    can_manga_message_update(&ERROR_TOLERANCE, errotTolerance);
}

uint8_t manga_getErrorTolerance()
{
    if (ERROR_TOLERANCE.count == 0)
        return 0;
    else
    {
        ERROR_TOLERANCE.count -= 1;
        return ERROR_TOLERANCE.value;
    }
}

void throttleHandler(CAN_RX_STRUCT msg)
{
    uint8_t throttleHigh = msg.rxdata.byte[CAN_DATA_BYTE_2];
    uint8_t throttleLow = msg.rxdata.byte[CAN_DATA_BYTE_3];
    
    can_manga_message_update(&THROTTLE_HIGH, throttleHigh);
    can_manga_message_update(&THROTTLE_LOW, throttleLow);
}

uint8_t manga_getThrottleLow()
{
    if (THROTTLE_LOW.count == 0)
        return 0;
    else
    {
        THROTTLE_LOW.count -= 1;
        return THROTTLE_LOW.value;
    }
}

uint8_t manga_getThrottleHigh()
{
    if (THROTTLE_HIGH.count == 0)
        return 0;
    else
    {
        THROTTLE_HIGH.count -= 1;
        return THROTTLE_HIGH.value;
    }
}
