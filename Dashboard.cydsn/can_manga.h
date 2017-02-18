/* ========================================
 * Can API for FRUCD
 * Schuyler Alschuler 2016 - 2017
 * ========================================
*/

#ifndef CAN_MANGA_H
#define CAN_MANGA_H

#include "CAN.h"
#include "can_manga_handlers.h"

// Struct to hold data and a count of how many times the CAN bus has sent
// messages updating the value (to avoid using bad data)
typedef struct MangaMessage_s
{
    volatile uint32_t count;
    volatile uint8_t value;
} MangaMessage;
void can_manga_message_update(volatile MangaMessage *mmsg, uint8_t data);

// Basic CAN functionality
void can_receive(uint8_t *msg, int ID);
void can_test_send();
void can_send(uint8_t data[8], uint32_t ID);

// Advanced CAN functionality
void can_send_cmd(uint8_t SetInterlock, uint16_t VCL_Throttle_High, uint16_t VCL_Throttle_Low);
void can_send_status(uint8_t state);

uint8_t getpedallow();
uint8_t getpedalhigh();


#endif

