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

#endif

/* [] END OF FILE */
