# smartHome
Control of the home appliances via local network using any smart device<br/>

:warning: **CAUTION:** In this project, some parts require AC mains power. If you are not an electrician, do not get involved in these parts yourself and make an electrician do them for you.<br/>
:warning: **DİKKAT:** Bu projede, bazı bölümler AC şebeke gücü içerir. Elektrikçi değilseniz bu bölümleri kendi başınıza yapmaya çalışmayın ve bir elektrikçiye yaptırın.

# Setup
## Custom Sonoff (customSonoff)
- :warning: **CAUTION:** Before breaking apart the sonoff, make sure it is disconnected from AC mains. Never energize the sonoff when it is disassembled.
- Buy a USB to UART converter board (such as [FT232RL](https://www.google.com/search?q=ft232rl+usb+to+ttl))
- If it does not have a 3.3 V regulator embedded, buy an external regulator (such as [LM2596 adjustable buck converter](https://www.google.com/search?q=lm2596+module)) to supply 3.3 V.
- Adjust the regulator to 3.3V (if it is not a fixed 3.3V regulator).
- Solder headers to sonoff (see picture below)
- Make sure the FTDI module is adjusted to 3.3V
- Connect the FTDI module to the PC alone, i.e., without sonoff.
- If the PC could not find its driver automatically, install its drivers manually.
- After the board is recognized by the PC, disconnect the FTDI from the PC.
- Make the connections as follows:

<div align="center">

| sonoff | pc |
| --- | --- |
| GND | FTDI GND|
| TX | FTDI RX |
| RX | FTDI TX |
| 3V3 | 3.3V (Regulator Vout Positive) |

</div>

- Make sure the regulator and PC grounds are connected (If you are using the PC to power the regulator also, it is OK too since the grounds meet at the PC motherboard)
- Plug back FTDI in to PC
- Press the button on sonoff
- While keeping pressed, plug the regulator.
- Release the button after 2-3 seconds.
- Open Arduino IDE
- Select board "Generic ESP8266 Module" (even if your sonoff have ESP8285 chip or you see ITEAD Sonoff on the menu; do not select them)
- Make sure the flash mode is selected as "DOUT"
- Select erase flash "All Flash Contents"
- Select your COM port
- Upload the sketch
- After uploading the first version of the firmware via cable, thanks to the Arduino OTA, now you can upload new firmware wirelessly by selecting the corresponding network port from Arduino IDE.


### Images
<p align="center">FT23RL close-up</p>

![FT232RL.jpeg](./customSonoff/images/FT232RL.jpeg)

<p align="center">LM2596 Buck Converter</p>

![buckConverter.jpeg](./customSonoff/images/buckConverter.jpeg)

<p align="center">FT232RL</p>

![uploadSetup.jpeg](./customSonoff/images/uploadSetup.jpeg)

<p align="center">Inside Sonoff</p>

![sonoffInside.jpeg](./customSonoff/images/sonoffInside.jpeg)

<p align="center">Headers</p>

![sonoffHeaders.jpeg](./customSonoff/images/sonoffHeaders.jpeg)

## Lamp Controller (lampController) & DC Powerbox (dcPowerbox)
- Regular ESP8266 code uploading procedure. Just select the CPU frequency 160 MHz for speed.

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

# Mobile Side

## Webpage Seen on Android Chrome

<div align="center">

![chromeAndroid](./lampController/mobileWebpage.jpeg)

</div>

## Mobile Control App for Android

<div align="center">

<a id="raw-url" href="https://raw.githubusercontent.com/Mehmet-Emre-Dogan/smartHome/main/APP/ControllerEng.apk">--> Download Controller App <--</a>

![ss](./APP/appSs.jpeg)

</div>

## Control with Voice on Android

- Install the on and off apps.
- <a id="raw-url" href="https://raw.githubusercontent.com/Mehmet-Emre-Dogan/smartHome/main/AUTOMATION/mobile/on/lamp_on.apk">Download On App</a>
- <a id="raw-url" href="https://raw.githubusercontent.com/Mehmet-Emre-Dogan/smartHome/main/AUTOMATION/mobile/off/lamp_off.apk">Download Off App</a>
- Create custom routines with your mobile assistant app to start on and off apps when you say "turn on" and "turn off" respectively.

<div align="center">

![ss](./AUTOMATION/mobile/off/bixbyOff.jpeg)

![ss](./AUTOMATION/mobile/on/bixbyOn.jpeg)

</div>



# References
 - https://mytectutor.com/esp8266-nodemcu-relay-control-from-web-page-over-wifi/
 - https://randomnerdtutorials.com/esp8266-ota-updates-with-arduino-ide-over-the-air/
 - https://randomnerdtutorials.com/reprogram-sonoff-smart-switch-with-web-server/
 - https://esphome.io/devices/sonoff_basic.html

 --> External EEPROM reading-writing functions are adopted from the link below:
 - https://dronebotworkshop.com/eeprom-arduino/
 - https://arduino-projects4u.com/arduino-24c16/

 --> Mobile app is inspired from here:
 - https://resultuzen.com.tr/blog/index.php/2019/02/09/nodemcu-8/
