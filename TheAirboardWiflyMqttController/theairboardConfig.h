#ifndef THEAIRBOARDWIFLYMQTTCONTROLLER_THEAIRBOARD_CONFIG_H_
#define THEAIRBOARDWIFLYMQTTCONTROLLER_THEAIRBOARD_CONFIG_H_


// The Airboard (https://github.com/theairboard/TheAirBoard)
#include <TheAirBoard.h>

TheAirBoard board;

void theairboard_init() {
  pinMode(RED, OUTPUT);         // initialize the RED LED pin as an output
  pinMode(GREEN, OUTPUT);       // initialize the GREEN LED pin as an output
  pinMode(BLUE, OUTPUT);        // initialize the BLUE LED pin as an output
  analogWrite(GREEN, 1);        // switch ON indicator at low power
  Serial.begin(BAUD_RATE);
}

void publish_battery() {
  topicBuffer[0] = '\0';
  strcpy_P(topicBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[BATTERY_STATUS_IDX])));
  payloadBuffer[0] = '\0';
  dtostrf(board.batteryChk(), 1, FLOAT_DECIMAL_PLACES, payloadBuffer);
  mqttClient.publish(topicBuffer, payloadBuffer);
}

void publish_led_colour(byte colour_idx) {
  topicBuffer[0] = '\0';
  strcpy_P(topicBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[LED_COLOUR_STATUS_IDX])));
  payloadBuffer[0] = '\0';
  mqttClient.publish(topicBuffer, itoa(colour_idx, payloadBuffer, 10));
}

void publish_temperature() {
  topicBuffer[0] = '\0';
  strcpy_P(topicBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[TEMPERATURE_STATUS_IDX])));
  payloadBuffer[0] = '\0';
  dtostrf(board.getTemp(), 1, FLOAT_DECIMAL_PLACES, payloadBuffer);
  mqttClient.publish(topicBuffer, payloadBuffer);
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


#endif /* THEAIRBOARDWIFLYMQTTCONTROLLER_THEAIRBOARD_CONFIG_H_ */
