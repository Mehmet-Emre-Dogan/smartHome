#include <ESP8266WiFi.h>
#include "secrets.h"
#define DEBUG false
#define NUM_RELAYS 4

//ota
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void ICACHE_RAM_ATTR handleBtn();

String title = "Lamp Controller";

byte relayStates[NUM_RELAYS] = {1, 1, 1, 1};
const int relays[NUM_RELAYS] = {D5, D6, D7, D2};

String states[2] = {"on", "off"};
String commands[2] = {"TURN OFF", "TURN ON"};
String hrefs[2] = {"/off", "/on"};
String buttons[2] = {" ", " button2"}; // green button, red button
String deviceNames[NUM_RELAYS] = {"Floor Lamp", "Bookcase Lamp", "Lampshade", "Dehumidifier"};

// Variable to store the HTTP request
String header;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  for(int i = 0; i < NUM_RELAYS; i++){
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], relayStates[i]);
  }

  if (DEBUG)  
    Serial.begin(9600);
  // Connect to Wi-Fi network with SSID and password
  WiFi.disconnect(); 
  WiFi.begin(ssid, password);
  WiFi.hostname(deviceName);
  WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(400);
    digitalWrite(LED_BUILTIN, HIGH);                
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
            if (header.indexOf("GET /pin1/on") >= 0)
            {
              relayStates[0] = 0;
            }
            else if (header.indexOf("GET /pin1/off") >= 0)
            {
              relayStates[0] = 1;
            }
            else if (header.indexOf("GET /pin2/on") >= 0) {
              relayStates[1] = 0;
            }
            else if (header.indexOf("GET /pin2/off") >= 0) {             
              relayStates[1] = 1;
            }
            else if (header.indexOf("GET /pin3/on") >= 0)
            { 
             relayStates[2] = 0;
            }
            else if (header.indexOf("GET /pin3/off") >= 0)
            {
             relayStates[2] = 1;
            }
            else if (header.indexOf("GET /pin4/on") >= 0) {
             relayStates[3] = 0;
            }
            else if (header.indexOf("GET /pin4/off") >= 0) {
              relayStates[3] = 1;
            }
            else{
              isChanged = false;
            }
            
           for(int j = 0; j < NUM_RELAYS; j++){
              if(digitalRead(relays[j]) != relayStates[j]){
                digitalWrite(relays[j], relayStates[j]);
              } 
           }

            // Display the HTML web page
            client.println("<!DOCTYPE html>");
            client.println("<html><head>");
            client.println("<meta http-equiv='content-type' content='text/html; charset=UTF-8'><meta charset='utf-8' name='viewport' content='width=device-width, initial-scale=1'>");
            client.println("<style>html, body { font-family: Helvetica; display: block; margin: 0px auto; text-align: center; background-color: rgb(37, 37, 38);}");
            client.println(".button { font-weight: bold; background-color: #209e48; width: 100px; border: none; color: white; padding: 5px 24px;");
            client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #c20a0a;}");
            client.println(".textbox {width: 200px; margin-top: auto; margin-bottom: auto; border: 1px solid #333; padding: 16px 20px; background-image: linear-gradient(180deg, #fff, #ddd 40%, #ccc);}");
            client.println(".mytext {font-size: 18px; font-weight:bold; font-family:Arial ; text-align: center; color: black;}");
            client.println("#container {width: 100%; height: 100%;  margin-left: 0px; margin-top: 10px; margin-bottom: 10px; padding: 0px; display: -webkit-flex; -webkit-justify-content: center; display: flex; justify-content: center;} ");
            client.println("</style></head>");
            client.println("<body>");
            client.println("    <h1 style='color:white;'>" + title + "</h1>");
            
            for (int j = 0; j < NUM_RELAYS; j++){
              client.println("<div id='container'>");
              client.println("<p></p>");
              client.println();
              
              client.println("<div class='textbox mytext'>" + (String) deviceNames[j] + " is " +  (String) states[relayStates[j]] + "</div>");
              client.println("<a href='/pin" +  (String) (j + 1) + hrefs[relayStates[j]] + "'><button class='button" + buttons[relayStates[j]] + "'>" + commands[relayStates[j]] + "</button></a> <p></p>");

              client.println("</div>");
            }
            
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
