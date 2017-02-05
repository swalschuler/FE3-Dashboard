#include "can_manager.h"

volatile uint8_t can_buffer[8];
volatile DataPacket can_queue[CAN_QUEUE_LENGTH];
volatile uint16_t can_head = 0, can_tail = 0;

void can_get(DataPacket* data_queue, uint16_t* data_head, uint16_t* data_tail)
{
    //CAN_GlobalIntEnable();
	*data_head = *data_tail = 0;

	uint8_t atomic_state = CyEnterCriticalSection(); // BEGIN ATOMIC

	while(can_head != can_tail) // move and convert can message queue to data queue
	{
		data_queue[*data_tail].id = can_queue[can_head].id;
		data_queue[*data_tail].length = can_queue[can_head].length;
		data_queue[*data_tail].millicounter = can_queue[can_head].millicounter;

		data_queue[*data_tail].data[0] = can_queue[can_head].data[0];
		data_queue[*data_tail].data[1] = can_queue[can_head].data[1];
		data_queue[*data_tail].data[2] = can_queue[can_head].data[2];
		data_queue[*data_tail].data[3] = can_queue[can_head].data[3];
		data_queue[*data_tail].data[4] = can_queue[can_head].data[4];
		data_queue[*data_tail].data[5] = can_queue[can_head].data[5];
		data_queue[*data_tail].data[6] = can_queue[can_head].data[6];
		data_queue[*data_tail].data[7] = can_queue[can_head].data[7];

		can_head = (can_head + 1) % CAN_QUEUE_LENGTH; // discard copied packet

		*data_tail = (*data_tail + 1) % DATA_QUEUE_LENGTH; // increment data tail

		if(*data_tail == *data_head) // if need to roll data queue
			*data_head = (*data_head + 1) % DATA_QUEUE_LENGTH;
	} // for all can messages in queue

	can_head = can_tail = 0;
	CyExitCriticalSection(atomic_state); // END ATOMIC
    //CAN_GlobalIntDisable();
} // can_receive()


uint16_t can_read(const DataPacket* data_queue, const uint16_t data_head, const uint16_t data_tail, const uint16_t ID, const uint16_t Entry)
{
    uint16_t pos;
    uint16_t newest = 0;
    
    //if (data_head == data_tail)
        //return 0;
    
    for(pos=data_head; pos!=data_tail; pos=(pos+1)%DATA_QUEUE_LENGTH)
	{
        if(data_queue[pos].id == ID)
        {
            newest = data_queue[pos].data[Entry];
        }
    }
    
    //if (data_queue.id == ID)
    //    return data_queue[pos].data[Entry]; 
    return (newest);
}

