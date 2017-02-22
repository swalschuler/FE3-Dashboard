/* ========================================
 * Can API for FRUCD
 * Schuyler Alschuler 2016 - 2017
 * ========================================
*/

#include "CAN.h"
#include "can_manga.h"
#include "can_manga_handlers.h"

volatile uint8_t pedalHigh = 0;
volatile uint8_t pedalLow = 0;

void can_receive(uint8_t *msg, int ID)
{
    uint8 InterruptState = CyEnterCriticalSection();
    
    uint8_t data[8];
    int i = 0;
    for (i = 0; i < 8; i++)
        data[i] = msg[i];
        
    switch (ID) 
    {
        case 0x0566:
            capacitorVoltHandler(data);
            break;
        case 0xA6:
            curtisFaultHandler();
            break;
        case 0x726:
            curtisHeartBeatHandler();
            break;
        case 0x0666:
            ackReceivedHandler(data);
            break;
         case 0x0201:
            errorToleranceHandler(data);
            break;
        case 0x0200: 
            pedalHigh = data[CAN_DATA_BYTE_2];
            pedalLow = data[CAN_DATA_BYTE_3];
            //throttleHandler(data);
            break;
    }
    
    CyExitCriticalSection(InterruptState);
}

void can_test_send()
{
    //CAN_1_DATA_BYTES_MSG msg;
    CAN_TX_MSG HeartB;
    
    HeartB.id = 0x300;
    HeartB.rtr = 0;
    HeartB.ide = 0;
    HeartB.dlc = 1;
    
    HeartB.irq = 0;
    
    HeartB.msg->byte[0] = (uint8) 1;
    HeartB.msg->byte[1] = (uint8) 1;
    HeartB.msg->byte[2] = (uint8) 1;
    HeartB.msg->byte[3] = (uint8) 1;
    HeartB.msg->byte[4] = (uint8) 1;
    HeartB.msg->byte[5] = (uint8) 1;
    HeartB.msg->byte[6] = (uint8) 1;
    HeartB.msg->byte[7] = (uint8) 1;
    
    CAN_SendMsg(&HeartB);
}

void can_send(uint8_t data[8], uint32_t ID)
{
    uint8_t i;
	CAN_TX_MSG message;
	CAN_DATA_BYTES_MSG payload;
	message.id = ID; 
	message.rtr = 0;
	message.ide = 0;
	message.dlc = 0x08;
	message.irq = 0;
	message.msg = &payload;
	for(i=0;i<8;i++)
		payload.byte[i] = data[i];
	CAN_SendMsg(&message); 
}

void can_send_status(
    uint8_t state)
{
    //max and min voltage means the voltage of single cell
        uint8_t data[8];
        
        data[0] = state;
        data[1] = 0;
        
        data[2] = 0;
        data[3] = 0;
        
        data[4] = 0;
        data[5] = 0;
        data[6] = 0;
        data[7] = 0;

        can_send(data, 0x626);

        
} // can_send_status()

void can_send_cmd(
    uint8_t SetInterlock,
    uint16_t VCL_Throttle_High,
    uint16_t VCL_Throttle_Low
)
{
    //max and min voltage means the voltage of single cell
        
        uint8_t data[8];
        
        data[0] = SetInterlock;
        
        data[1] = VCL_Throttle_High;
        data[2] = VCL_Throttle_Low;
        
        data[3] = 0;
        data[4] = 0;
        
        data[5] = 0;
        data[6] = 0;
        data[7] = 0;

        can_send(data, 0x766);
        CyDelay(1);

} // can_send_cmd()

void can_manga_message_update(volatile MangaMessage *mmsg, uint8_t data)
{
 mmsg->value = data;
 mmsg->count += 1;
}

uint8_t getpedallow()
{
    return pedalLow;
}

uint8_t getpedalhigh()
{
    return pedalHigh;
}
