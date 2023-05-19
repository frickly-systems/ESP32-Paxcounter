#include "serial_transport.h"

#include <esp32/rom/crc.h>

esp_err_t serial_transport_init(void) {
  // If VERBOSE is set the main.cpp inits the Serial port thus we only do if
  // it's not
#if !VERBOSE
  Serial.begin(115200);
#endif

  return ESP_OK;
}

void serial_transport_deinit(void) {}

void serial_transport_enqueuedata(MessageBuffer_t *message) {
  // Resulting message is basically
  // "PORT:{PORT};DATA:{DATA};CRC:{crc(PORT+DATA)};\n"

  Serial.printf("PORT:%02X;DATA:", message->MessagePort);

  for (int i = 0; i < message->MessageSize; i++) {
    Serial.printf("%02X", message->Message[i]);
  }

  uint32_t crc = crc32_le(0, &(message->MessagePort), 1);
  crc = crc32_le(crc, message->Message, message->MessageSize);

  Serial.printf(";CRC:%08X;\n", crc);
}

void serial_transport_queuereset(void) {}

uint32_t serial_transport_queuewaiting(void) { return 0; }