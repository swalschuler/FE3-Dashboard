/* ========================================
 * This file is used for declaring functions which will be executed for a particular CAN ID.
 * ========================================
 */

#ifndef CAN_MANGA_HANDLERS_H
#define CAN_MANGA_HANDLERS_H

#include "CAN.h"
#include "can_manga.h"
    
// If you ever see 0xA6, just set CURTIS to 1 (so there has been a fault)
void curtisFaultHandler();
uint8_t manga_getCurtisFaultCheck();

void curtisHeartBeatHandler();
uint8_t manga_getCurtisHeartBeatCheck();

// Handles capacitor voltage 
void capacitorVoltHandler(CAN_RX_STRUCT msg);
uint8_t manga_getCapacitorVoltage();
uint8_t manga_getAbsMotorRPM();

void ackReceivedHandler(CAN_RX_STRUCT msg);
uint8_t manga_getAckReceive();

void errorToleranceHandler(CAN_RX_STRUCT msg);
uint8_t manga_getErrorTolerance();

void throttleHandler(CAN_RX_STRUCT msg);
uint8_t manga_getThrottleLow();
uint8_t manga_getThrottleHigh();


#endif
