# smartHome
Control of the home appliances via local network and any smart device

# Setup
Lorem ipsum dolor sit amet consectetur adipisicing elit. Rem animi alias, amet iste porro molestias deserunt, velit iusto mollitia ab fugiat qui dolore excepturi similique recusandae earum officiis quam ut sed quod doloribus ex maxime! Perferendis veritatis quas a sed laudantium iste recusandae ipsam eius voluptatibus consequuntur nulla repudiandae, perspiciatis magni fugiat.  

# System Details
## HTML to INO & INO to HTML
These python scripts convert HTML files to Arduino IDE compatible strings or vice versa.

## Custom Sonoff (customSonoff)
Custom firmware for sonoff basic r2 (v1.4) for better integration with the home automation system. My sonoff includes the ESP8285 module, which is the same as ESP8266, except the ESP8285's flash memory is 1 MB. Hence, an ESP8266 can be used as debugging device.

### Schematic

![debugSchematic.png](./customSonoff/debugSchematic.png)

### Webpage

![debugSetup1.jpeg](.customSonoff/debugSetup1.jpeg)

![debugSetup2.jpeg](.customSonoff/debugSetup2.jpeg)

### Setup

![customSonoffWebpage.png](./customSonoff/customSonoffWebpage.png)

## Lamp Controller (lampController)
The system consists of two sub-units: The control box and the relay boxes. The system is designed in two subunits to increase safety by eliminating the need for long power (230V AC) cords. The long wires installed all across the room only carry a 5V DC signal, which is safe.

### Schematic

![schematic.png](./lampController/schematic.png)

### Webpage

![lampControllerWebpage.png](./lampController/lampControllerWebpage.png)

### Control Box
The control box contains an ESP8266 as a processor and a 4-way relay module to generate signals for the relay boxes. In addition, there exists a green LED as a power indicator.

<p align="center">Top</p>

![controlBoxTop.jpeg](./lampController/images/controlBoxTop.jpeg)

<p align="center">Left</p>

![controlBoxLeft.jpeg](./lampController/images/controlBoxLeft.jpeg)

<p align="center">Right</p>

![controlBoxRight.jpeg](./lampController/images/controlBoxRight.jpeg)


### Relay Box
- The phase cable coming from the wall socket is connected to the common pin of the relay, and the output phase cable is connected to the normally open pin, i.e., turned off when not excited, of the relay. The neutral cable directly goes from the wall plug to the output receptacle.
- The +5V of the signal cable is connected to the VCC on the relay module, and both the signal and GND of the relay are connected to the ground of the signal wire. 
By doing so, the output receptacle is energized when a 5V supply is connected to the signal plug.
 
<p align="center">Explanation</p>

![relayBoxAnnotated.jpeg](./lampController/images/relayBoxAnnotated.jpeg)

<p align="center">Inside</p>

![relayBoxInside.jpeg](./lampController/images/relayBoxInside.jpeg)

<p align="center">Off</p>

![relayBoxOff.jpeg](./lampController/images/relayBoxOff.jpeg)

<p align="center">On</p>

![relayBoxOn.jpeg](./lampController/images/relayBoxOn.jpeg)

### Images from the setup

<p align="center">Bookcase Lamp</p>

![controlBoxAndRelayBox.jpeg](./lampController/images/controlBoxAndRelayBox.jpeg)

<p align="center">Floor Lamp</p>

![floorLampRelayBox.jpeg](./lampController/images/floorLampRelayBox.jpeg)

<p align="center">Lampshade</p>

![lampshadeRelayBoxInPlace.jpeg](./lampController/images/lampshadeRelayBoxInPlace.jpeg)


# References
 - https://mytectutor.com/esp8266-nodemcu-relay-control-from-web-page-over-wifi/
 - https://randomnerdtutorials.com/esp8266-ota-updates-with-arduino-ide-over-the-air/
 - https://randomnerdtutorials.com/reprogram-sonoff-smart-switch-with-web-server/
 - https://esphome.io/devices/sonoff_basic.html
