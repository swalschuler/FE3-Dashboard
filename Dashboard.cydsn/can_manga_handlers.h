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

#ifndef CAN_MANGA_HANDLERS_H
#define CAN_MANGA_HANDLERS_H

#include "CAN.h"
    
// Define live variables
extern volatile uint8_t CAPACITOR_VOLT;
extern volatile uint8_t CURTIS_FAULT_CHECK;
extern volatile uint8_t CURTIS_HEART_BEAT_CHECK;
extern volatile uint16_t ACK_RX;
extern volatile uint16_t ERROR_TOLERANCE;
extern volatile uint16_t ABS_MOTOR_RPM;
extern volatile uint16_t THROTTLE_HIGH;
extern volatile uint16_t THROTTLE_LOW;
    
void curtisHeartBeatHandler()
{
    CURTIS_HEART_BEAT_CHECK = 1;
}

// Handles capacitor voltage 
void capacitorVoltHandler(CAN_RX_STRUCT msg)
{
    CAPACITOR_VOLT = msg.rxdata.byte[CAN_DATA_BYTE_1];
    ABS_MOTOR_RPM = msg.rxdata.byte[CAN_DATA_BYTE_5];
};

// If you ever see 0xA6, just set CURTIS to 1 (so there has been a fault)
void curtisFaultHandler()
{
    CURTIS_FAULT_CHECK = 1;
};

void ackRecievedHandler(CAN_RX_STRUCT msg)
{
    ACK_RX = msg.rxdata.byte[CAN_DATA_BYTE_1];
};

void errorToleranceHandler(CAN_RX_STRUCT msg)
{
    ERROR_TOLERANCE = msg.rxdata.byte[CAN_DATA_BYTE_1];
}

void throttleHandler(CAN_RX_STRUCT msg)
{
    THROTTLE_HIGH = msg.rxdata.byte[CAN_DATA_BYTE_2];
    THROTTLE_LOW = msg.rxdata.byte[CAN_DATA_BYTE_3];
}
#endif

/* [] END OF FILE */
