// The mother of all embedded development...
#include <Arduino.h>

// std::set for unified array functions
#include <set>
#include <array>
#include <algorithm>

// OLED Display
#ifdef HAS_DISPLAY
    #include <U8x8lib.h>
#endif

//GPS
#ifdef HAS_GPS
    #include <TinyGPS++.h>
#endif

// LMIC-Arduino LoRaWAN Stack
#include <lmic.h>
#include <hal/hal.h>

// LED controls
#ifdef HAS_RGB_LED
    #include <SmartLeds.h>
#endif

#include "rgb_led.h"
#include "macsniff.h"
#include "main.h"

// Struct holding devices's runtime configuration
typedef struct {
  uint8_t lorasf;                       // 7-12, lora spreadfactor
  uint8_t txpower;                      // 2-15, lora tx power
  uint8_t adrmode;                      // 0=disabled, 1=enabled
  uint8_t screensaver;                  // 0=disabled, 1=enabled
  uint8_t screenon;                     // 0=disabled, 1=enabled
  uint8_t countermode;                  // 0=cyclic unconfirmed, 1=cumulative, 2=cyclic confirmed
  int16_t rssilimit;                    // threshold for rssilimiter, negative value!
  uint8_t sendcycle;                    // payload send cycle [seconds/2]
  uint8_t wifichancycle;                // wifi channel switch cycle [seconds/100]
  uint8_t blescantime;                  // BLE scan cycle duration [seconds]
  uint8_t blescan;                      // 0=disabled, 1=enabled
  uint8_t wifiant;                      // 0=internal, 1=external (for LoPy/LoPy4)
  uint8_t vendorfilter;                 // 0=disabled, 1=enabled
  uint8_t rgblum;                       // RGB Led luminosity (0..100%)
  uint8_t gpsmode;                      // 0=disabled, 1=enabled
  char version[10];                     // Firmware version
  } configData_t;

#ifdef HAS_GPS
  typedef struct {
    uint32_t latitude;
    uint32_t longitude;
    uint8_t hdop;
    uint32_t satellites;
    uint16_t altitude;
    } gpsStatus_t;
  extern gpsStatus_t gps_status;        // struct for storing gps data
  extern TinyGPSPlus gps;            // Make TinyGPS++ instance globally availabe
#endif

extern configData_t cfg;
extern uint64_t uptimecounter;
extern osjob_t sendjob, rcmdjob;
extern char display_lora[], display_lmic[];
extern int countermode, screensaver, adrmode, lorasf, txpower, rlim;
extern uint16_t macs_total, macs_wifi, macs_ble; // MAC counters
extern std::set<uint16_t> macs;
extern hw_timer_t * channelSwitch; // hardware timer used for wifi channel switching
extern xref2u1_t rcmd_data;        // buffer for rcommand results size
extern u1_t rcmd_data_size;        // buffer for rcommand results size
