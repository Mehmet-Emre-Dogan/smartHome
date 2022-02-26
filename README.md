# smartHome
Control of the home appliances via local network and any smart device

# Setup
## Custom Sonoff (customSonoff)
- Buy a USB to TTL converter board (such as [FT232RL](https://www.google.com/search?q=ft232rl+usb+to+ttl)
- If it does not have a 3.3 V regulator embedded, buy an external regulator (such as [LM2596 adjustable buck converter](https://www.google.com/search?q=lm2596+module)to supply 3.3 V.
- Adjust the regulator to 3.3V (if it is not a fixed 3.3V regulator).
- Solder headers to sonoff (see picture below)
- Made the connections as follows:
 | sonoff | pc |
 | --- | --- |
 | GND | FTDI GND|
 | TX | FTDI RX |
 | RX | FTDI TX |
 | 3V3 | Regulator Vout Positive |



# System Details
## HTML to INO & INO to HTML
These python scripts convert HTML files to Arduino IDE compatible strings or vice versa.

## Custom Sonoff (customSonoff)
Custom firmware for sonoff basic r2 (v1.4) for better integration with the home automation system. My sonoff includes the ESP8285 module, which is the same as ESP8266, except the ESP8285's flash memory is 1 MB. Hence, an ESP8266 can be used as debugging device.

### Schematic

![debugSchematic.png](./customSonoff/debugSchematic.png)

### Webpage

![customSonoffWebpage.png](./customSonoff/customSonoffWebpage.png)


### Debug Setup
![debugSetup1.jpeg](./customSonoff/debugSetup1.jpeg)

![debugSetup2.jpeg](./customSonoff/debugSetup2.jpeg)

## Lamp Controller (lampController)
The system consists of two sub-units: The control box and the relay boxes. The system is designed in two subunits to increase safety by eliminating the need for long power (230V AC) cords. The long wires installed all across the room only carry a 5V DC signal, which is safe.

### Schematic

![schematic.png](./lampController/schematic.png)

### Webpage

![lampControllerWebpage.png](./lampController/lampControllerWebpage.png)

### Control Box
The control box contains an ESP8266 as a processor and a 4-way relay module to generate signals for the relay boxes. In addition, there exists a green LED as a power indicator.

### Images of the device

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
 
### Images of the device

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

## DC Powerbox (dcPowerbox)
The system handles the low-voltage peripherals in the room. It has 4 outlets for the Music Visualizer, the Ambiance Light, the Fans, and the Laptop Cooler. The system has an external IC2 EEPROM to store the relay states. The python scripts in the AUTOMATION folder are adjusted to run at startup, shutdown, sleep and wake events of the PC. Moreover, for manual control, either the scripts in the MANUAL folder or the web pages may be used.

### Schematic

![schematicPowerbox.png](./dcPowerbox/schematicPowerbox.png)

### Webpage

![powerboxWebpage.png](./dcPowerbox/powerboxWebpage.png)

### Images of the device

<p align="center">Top</p>

![top](./dcPowerbox/images/top.jpeg)

<p align="center">In</p>

![in](./dcPowerbox/images/in.jpeg)

<p align="center">Front</p>

![front](./dcPowerbox/images/front.jpeg)

<p align="center">Left</p>

![left](./dcPowerbox/images/left.jpeg)

<p align="center">Right</p>

![right](./dcPowerbox/images/right.jpeg)

<p align="center">Back</p>

![back](./dcPowerbox/images/back.jpeg)


### Images from the setup

![installed](./dcPowerbox/images/powerboxInstalled.jpeg)

![fans and ambiance](./dcPowerbox/images/fansAndAmbiance.jpeg)

<div align="center">
<p align="center">Music Visualizer</p>

![music visualizer](./dcPowerbox/images/musicVisualizer.jpeg)
</div>

![adapters](./dcPowerbox/images/adapters.jpeg)

# References
 - https://mytectutor.com/esp8266-nodemcu-relay-control-from-web-page-over-wifi/
 - https://randomnerdtutorials.com/esp8266-ota-updates-with-arduino-ide-over-the-air/
 - https://randomnerdtutorials.com/reprogram-sonoff-smart-switch-with-web-server/
 - https://esphome.io/devices/sonoff_basic.html

 --> External EEPROM reading-writing functions are adopted from the link below:
 - https://dronebotworkshop.com/eeprom-arduino/
 - https://arduino-projects4u.com/arduino-24c16/
