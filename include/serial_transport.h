#ifndef ENABLE_SERIAL_TRANSPORT_H
#define ENABLE_SERIAL_TRANSPORT_H

#include "globals.h"
#include "rcommand.h"

// Most of the functions dont do anything but it will be useful if someday we
// implement the receiving stuff or want to use a queue for some reason

esp_err_t serial_transport_init(void);
void serial_transport_deinit(void);

void serial_transport_enqueuedata(MessageBuffer_t *message);
void serial_transport_queuereset(void);
uint32_t serial_transport_queuewaiting(void);

#endif