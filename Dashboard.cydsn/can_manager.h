#include <project.h>
#include "data.h"

static uint16_t CANID_Recv_list[] =
{
    0x466, //Curtis Debug Info
    0x566, //Curtis Status
    0x666  //Curtis Recv Ack to Dashcmd
};

void can_send_cmd(
    uint8_t SetInterlock,
    uint16_t VCL_Throttle,
    uint16_t VCL_Brake
);

void can_send_status(
    uint8_t state);

void can_get(DataPacket* data_queue, uint16_t* data_head, uint16_t* data_tail);

uint16_t can_read(const DataPacket* data_queue, const uint16_t data_head, const uint16_t data_tail, const uint16_t ID, const uint16_t Entry);

uint8_t Curtis_Fault_Check(const DataPacket* data_queue, const uint16_t data_head, const uint16_t data_tail);

uint8_t Curtis_Heart_Beat_Check(const DataPacket* data_queue, const uint16_t data_head, const uint16_t data_tail);