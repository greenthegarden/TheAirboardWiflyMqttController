#ifndef THEAIRBOARDWIFLYMQTTCONTROLLER_CONFIG_H_
#define THEAIRBOARDWIFLYMQTTCONTROLLER_CONFIG_H_


/****  GLobal Constants ****/

const int AFTER_ERROR_DELAY       = 1000;
const int BAUD_RATE               = 9600;
const byte FLOAT_DECIMAL_PLACES   = 1;
const unsigned long STATUS_UPDATE_INTERVAL = 1UL * 60UL * 1000UL;    // x minutes = x * 60 * 1000 miliiseconds


/**** Exernal library imports ****/

// The Airboard ()
#include <TheAirBoard.h>

// MemoryFree (https://github.com/maniacbug/MemoryFree)
#include <MemoryFree.h>


/**** global variable definitions ****/

TheAirBoard board;

unsigned long statusPreviousMillis = 0UL;

void theairboard_init() {
  pinMode(RED, OUTPUT);         // initialize the RED LED pin as an output
  pinMode(GREEN, OUTPUT);       // initialize the GREEN LED pin as an output
  pinMode(BLUE, OUTPUT);        // initialize the BLUE LED pin as an output
  analogWrite(GREEN, 1);        // switch ON indicator at low power
  Serial.begin(BAUD_RATE);
}

char led_colour = '0';

// Macros
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))



/**** Internal imports ****/

#include "networkConfig.h"  // Network configuration
#include "wiflyConfig.h"   // WiFly configuration
#include "mqttConfig.h"    // MQTT configuration


#endif  /* THEAIRBOARDWIFLYMQTTCONTROLLER_CONFIG_H_ */
