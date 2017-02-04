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
    

// Handles 0x300
void testHandler(CAN_RX_STRUCT msg)
{
    return;
};

    
#endif

/* [] END OF FILE */
