#include <Arduino.h>

#include "config.h"

void theairboard_init() {
  pinMode(RED, OUTPUT);         // initialize the RED LED pin as an output
  pinMode(GREEN, OUTPUT);       // initialize the GREEN LED pin as an output
  pinMode(BLUE, OUTPUT);        // initialize the BLUE LED pin as an output
  analogWrite(GREEN, 1);        // switch ON indicator at low power
  Serial.begin(BAUD_RATE);
}

void theairboard_set_led_red() {
  digitalWrite(RED, 1); digitalWrite(GREEN, 0); digitalWrite(BLUE, 0);
  publish_led_colour(1);
}

void theairboard_set_led_green() {
  digitalWrite(RED, 0); digitalWrite(GREEN, 1); digitalWrite(BLUE, 0);
  publish_led_colour(2);
}

void theairboard_set_led_blue() {
  digitalWrite(RED, 0); digitalWrite(GREEN, 0); digitalWrite(BLUE, 1);
  publish_led_colour(3);
}

void theairboard_set_led_colour(byte colour_idx) {
  switch(colour_idx) {
    case 1 : // red
      theairboard_set_led_red();
      break;
    case 2 : // green
      theairboard_set_led_green();
      break;
    case 3 : // blue
      theairboard_set_led_blue();
      break;
    default:
      break;
  }
}

void callback(char *topic, uint8_t *payload, unsigned int length) {
  // handle message arrived
  /* topic = part of the variable header:has topic name of the topic where the
     publish received
       NOTE: variable header does not contain the 2 bytes with the
            publish msg ID
      payload = pointer to the first item of the buffer array that
                contains the message tha was published
               EXAMPLE of payload: lights,1
      length = the length of the payload, until which index of payload
  */

  // Copy the payload to the new buffer
  char *message =
      (char *)malloc((sizeof(char) * length) +
                     1); // get the size of the bytes and store in memory
  memcpy(message, payload, length * sizeof(char)); // copy the memory
  message[length * sizeof(char)] = '\0'; // add terminating character

  byte topicIdx = 0;
  boolean controlTopicFound = false;

  // find if topic is matched
  for (byte i = 0; i < ARRAY_SIZE(CONTROL_TOPICS); i++) {
    topicBuffer[0] = '\0';
    strcpy_P(topicBuffer, (PGM_P)pgm_read_word(&(CONTROL_TOPICS[i])));
    if (strcmp(topic, topicBuffer) == 0) {
      topicIdx = i;
      controlTopicFound = true;
      break;
    }
  }

  if (controlTopicFound) {
    // switch to case statements
    if (topicIdx == THEAIRBOARD_LED_CONTROL_IDX) { // topic is RELAY_CONTROL
      // message is expected to be an integer
      byte led_colour_idx = atoi(message);
      if (led_colour_idx > 0) {
        theairboard_set_led_colour(led_colour_idx);
      }
    }
  }

  // free memory assigned to message
  free(message);
}

/*--------------------------------------------------------------------------------------
  setup()
  Called by the Arduino framework once, before the main loop begins
  --------------------------------------------------------------------------------------*/
void setup()
{
  theairboard_init();
  wifly_configure();
  mqtt_connect();
}


/*--------------------------------------------------------------------------------------
  loop()
  Arduino main loop
  --------------------------------------------------------------------------------------*/
void loop()
{
  unsigned long now = millis();

  if (!mqttClient.connected()) {
//    mqttClientConnected = false;
    if (now - lastReconnectAttempt >= RECONNECTION_ATTEMPT_INTERVAL) {
      lastReconnectAttempt = now;
      if (mqtt_connect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
    mqttClient.loop();
  }

  if (now - statusPreviousMillis >= STATUS_UPDATE_INTERVAL) {
    if (mqttClient.connected()) {
      statusPreviousMillis = now;
      publish_status();
    }
  }
}
