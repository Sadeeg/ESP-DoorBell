#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <tr064.h>
#include "secret.h"


TR064 tr064_connection(FRITZBOX_PORT, FRITZBOX_IP, USER, PASSWORD);
int bellPin = D1;
const char DEVICE_NAME[] = "ESP-Klingel";


void setup() {
  tr064_connection.debug_level = 4;
  pinMode(bellPin,INPUT);
  Serial.begin(115200);
  while(!Serial) { delay(100); }
   Serial.println("Hello!");
  WiFi.hostname(DEVICE_NAME);
  /**
   * Connet to Wifi
   */
  //WiFi.config(STATIC_IP, SUBNET, GATEWAY, DNS);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(WLANSSID, WLANPASSWORD);
  uint32_t notConnectedCounter = 0;
  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.println("Wifi connecting...");
      notConnectedCounter++;
      if(notConnectedCounter > 150) { // Reset board if not connected after 5s
          Serial.println("Resetting due to Wifi not connecting...");
          ESP.restart();
      }
  }
  //tr064_connection.init();
  Serial.print("Wifi connected, IP address: ");
  Serial.println(WiFi.localIP());
  /**
   * Enable OTA update
   */

  ArduinoOTA.setPassword(OTAPASSWORD);
    Serial.println("1!");
  ArduinoOTA.begin();
    Serial.println("2!");

    Serial.println("3!");
}
void loop() {
  // Check for over the air update request and (if present) flash it
  ArduinoOTA.handle();
  Serial.println("loop!");
  if(digitalRead(bellPin) == LOW){
      String tr064_service = "X_VoIP:1";

	//if(tr064_connection.state()<0){
	//tr064_connection.init();
	//}
  // Die Telefonnummer **9 ist der Fritzbox-Rundruf.
  String call_params[][2] = {{"NewX_AVM-DE_PhoneNumber", "**9"}};
  //tr064_connection.action(tr064_service, "X_AVM-DE_DialNumber", call_params, 1,"/upnp/control/x_voip");

   //tr064_connection.action(tr064_service, "X_AVM-DE_DialNumber", call_params, 1);

  // Warte vier Sekunden bis zum auflegen
  delay(60000);
  //tr064_connection.action(tr064_service, "X_AVM-DE_DialHangup");

    
  }
}



