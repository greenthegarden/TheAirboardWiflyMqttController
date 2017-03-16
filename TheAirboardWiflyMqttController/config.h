#ifndef THEAIRBOARDWIFLYMQTTCONTROLLER_CONFIG_H_
#define THEAIRBOARDWIFLYMQTTCONTROLLER_CONFIG_H_


/****  GLobal Constants ****/

const int AFTER_ERROR_DELAY       = 1000;
const int BAUD_RATE               = 9600;
const byte FLOAT_DECIMAL_PLACES   = 1;
const unsigned long STATUS_UPDATE_INTERVAL = 1UL * 60UL * 1000UL;    // x minutes = x * 60 * 1000 miliiseconds


/**** External library imports ****/


// MemoryFree (https://github.com/maniacbug/MemoryFree)
#include <EEPROM.h>
#include <MemoryFree.h>


/**** global variable definitions ****/
#ifndef LED_STATE_EEPROM_ADDRESS
#define LED_STATE_EEPROM_ADDRESS 0; // eeprom address to store LED value
#endif

unsigned long statusPreviousMillis = 0UL;

// Macros
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))



/**** Internal imports ****/

#include "networkConfig.h"  // Network configuration
#include "wiflyConfig.h"   // WiFly configuration
#include "mqttConfig.h"    // MQTT configuration
#include "theairboardConfig.h"


#endif  /* THEAIRBOARDWIFLYMQTTCONTROLLER_CONFIG_H_ */
