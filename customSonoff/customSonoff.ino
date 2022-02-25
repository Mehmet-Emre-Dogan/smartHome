#include <ESP8266WiFi.h>
#include "secrets.h"
#include "pinDefines.h"
#define DEBUG false

//ota
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void ICACHE_RAM_ATTR handleBtn();

byte relayState = 0;
// Variable to store the HTTP request
String header;

void enableInterrupts(){
  attachInterrupt(digitalPinToInterrupt(BTN), handleBtn, FALLING);
}

void disableInterrupts(){
  detachInterrupt(digitalPinToInterrupt(BTN) );
}

void handleBtn(){
  disableInterrupts();
  delay(10);
  
  while(!digitalRead(BTN)) // wait until the btn released
    delay(2);

  relayState = digitalRead(RELAY);
  relayState = !relayState; // toggle current state
  digitalWrite(RELAY, relayState);
  
  enableInterrupts();
}

void setup() {
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RELAY, relayState);
  enableInterrupts();

  if (DEBUG)  
    Serial.begin(9600);
  // Connect to Wi-Fi network with SSID and password
  WiFi.disconnect(); 
  WiFi.begin(ssid, password);
  WiFi.hostname(deviceName);
  WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(BLUE_LED, LOW);
    delay(400);
    digitalWrite(BLUE_LED, HIGH);                
    delay(100);                            
  }
  WiFi.config(staticIP, subnet, gateway, dns);
  server.begin();

  /////////////////////////////OTA////////////////////////////
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    //Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    //Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    //Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    //Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      //Serial.println("Auth Failed");
      ;
    } else if (error == OTA_BEGIN_ERROR) {
      //Serial.println("Begin Failed");
      ;
    } else if (error == OTA_CONNECT_ERROR) {
      //Serial.println("Connect Failed");
      ;
    } else if (error == OTA_RECEIVE_ERROR) {
      //Serial.println("Receive Failed");
      ;
    } else if (error == OTA_END_ERROR) {
      //Serial.println("End Failed");
      ;
    }
  });
  ArduinoOTA.begin();
  ///////////////////////////////////////////////////////////
  
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    if (DEBUG)  
      Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        if (DEBUG)  
          Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            bool isChanged = true;
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /pin1/on") >= 0){
              relayState = 1;
            }
            else if (header.indexOf("GET /pin1/off") >= 0){
              relayState = 0;
            }
            else{
              isChanged = false;
            }

            if(digitalRead(RELAY) != relayState){
              digitalWrite(RELAY, relayState);
           }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html>");
            client.println("<html><head>");
            client.println("<meta http-equiv='content-type' content='text/html; charset=UTF-8'><meta charset='utf-8' name='viewport' content='width=device-width, initial-scale=1'>");
            client.println("<style>html, body { font-family: Helvetica; display: block; margin: 0px auto; text-align: center; background-color: rgb(37, 37, 38);}");
            client.println(".button { background-color: #209e48; border: none; color: white; padding: 12px 24px;");
            client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #c20a0a; padding: 12px 28px;}");
            client.println(".textbox {width: 150px; border: 1px solid #333; padding: 16px 20px; background-image: linear-gradient(180deg, #fff, #ddd 40%, #ccc);}");
            client.println(".mytext {font-size: 16px; font-weight:bold; font-family:Arial ; text-align: center; color: black;}");
            client.println("#container {width: 100%; height: 100%; margin-left: 0px; margin-top: 20px; padding: 0px; display: -webkit-flex; -webkit-justify-content: center; display: flex; justify-content: center;} ");
            client.println("</style></head>");
            client.println("<body>");
            client.println("    <h1 style='color:white;'>Living room floor lamp</h1>");
            client.println("        <div id='container'>");
            client.println("            <p></p>");
            client.println();

            // If the relay1State is off, it displays the ON button
            if (relayState) {
              client.println("            <div class='textbox mytext'>Floor lamp is on</div> ");
              client.println("            <a href='/pin1/off'><button class='button'>TURN OFF</button></a> <p></p>");
            } else {
              client.println("            <div class='textbox mytext'>Floor lamp is off</div> ");
              client.println("            <a href='/pin1/on'><button class='button button2'>TURN ON</button></a> <p></p>");
            }
            client.println("</div>");

            if (isChanged){
              client.println("<meta http-equiv='refresh' content='0; URL=/'>"); // Return to root page to avoid accidental refresh toggles
            }

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
  }

  
  ArduinoOTA.handle();
}
