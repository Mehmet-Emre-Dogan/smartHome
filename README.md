# smartHome
Control of the home appliances via local network and any smart device
## HTML to INO & INO to HTML
These are the python scripts to convert HTML files to Arduino IDE compatible strings or vice versa.
## Custom Sonoff (customSonoff)
Custom firmware for sonoff basic r2 (v1.4) for better integration with the home automation system. My sonoff includes the ESP8285 module, which is the same as ESP8266, except the ESP8285's flash memory is 1 MB. Hence, an ESP8266 can be used as debugging device.
![debugSchematic.png](./customSonoff/debugSchematic.png)

## Lamp Controller (lampController)
The system consists of two sub-units: The control box and the relay boxes. The system is designed in two subunits to increase safety by eliminating the need for long power (230V AC) cords. The long wires installed all across the room only carry a 5V DC signal, which is safe.

## Control Box
![controlBoxTop.jpeg](./lampController/images/controlBoxTop.jpeg)
![controlBoxLeft.jpeg](./lampController/images/controlBoxLeft.jpeg)
![controlBoxRight.jpeg](./lampController/images/controlBoxRight.jpeg)

## References
 - https://mytectutor.com/esp8266-nodemcu-relay-control-from-web-page-over-wifi/
 - https://randomnerdtutorials.com/esp8266-ota-updates-with-arduino-ide-over-the-air/
 - https://randomnerdtutorials.com/reprogram-sonoff-smart-switch-with-web-server/
 - https://esphome.io/devices/sonoff_basic.html
