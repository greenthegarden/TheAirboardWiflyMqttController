# The AirBoard WiFly Mqtt Controller

MQTT controller to change the LED colour on a [The AirBoard](http://theairboard.cc) via a [RN-XV WiFly Module] (https://www.sparkfun.com/products/10822).

Requires the following libraries:
*   [TheAirBoard](https://github.com/theairboard/TheAirBoard)
*   [WiFly](https://github.com/greenthegarden/WiFly)
*   [MQTT](https://github.com/knolleary/pubsubclient)

To change colour of LED, publish an integer between 1 and 3 to the topic `theairboard/control/led'. A value of 1 will change colour to red, 2 to green and 3 to blue. When colour is changed a message with the colour index is published to the topic `theairboard/status/led_colour'.
