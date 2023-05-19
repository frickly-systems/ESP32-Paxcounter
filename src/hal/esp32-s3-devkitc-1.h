// clang-format off
// upload_speed 1500000
// board esp32-s3-devkitc-1

#ifndef _ESP32_S3_DEVKITC_1_H
#define _ESP32_S3_DEVKITC_1_H

#include <stdint.h>

#define HAS_LED NOT_A_PIN
#define RGB_LED_COUNT 1
#define HAS_RGB_LED FastLED.addLeds<WS2812, GPIO_NUM_48, GRB>(leds, RGB_LED_COUNT);

#define HAS_BUTTON NOT_A_PIN

#endif