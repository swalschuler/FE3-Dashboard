/* ========================================
 * Can API for FRUCD
 * Schuyler Alschuler 2016 - 2017
 * ========================================
*/

#ifndef CAN_MANGA_H
#define CAN_MANGA_H

#include "CAN.h"

void can_receive(CAN_RX_STRUCT msg, int ID);
void can_test_send();
void can_send(uint8_t data[8], uint32_t ID);

void can_send_cmd(
    uint8_t SetInterlock,
    uint16_t VCL_Throttle_High,
    uint16_t VCL_Throttle_Low
);

void can_send_status(
    uint8_t state);

uint8_t Curtis_Heart_Beat_Check();
uint16_t getErrorTolerance();
#endif

/* [] END OF FILE */
