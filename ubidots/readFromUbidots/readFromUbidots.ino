/*
 * This script subscribe to UbiDots broker to receive data
 * Authors: Daniel Moraes and Vitor Jun
 */

/*
 * Include LIBRARIES
 */
#include "confidentialStuff.h"

#include "UbidotsEsp32Mqtt.h"

#include <ArduinoLog.h>

#include <Logger.h>

#include<Wire.h>

/***********************************
 * Define constants
***********************************/

Ubidots ubidots(UBIDOTS_TOKEN);

void callback(char * topic, byte * payload, unsigned int length) {
  Serial.print("Messagem recebida [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
  if ((char) payload[0] == '1') {
    digitalWrite(OnboardLED, HIGH);
    Serial.print("Aceso!");
  } else {
    digitalWrite(OnboardLED, LOW);
    Serial.print("Apagado!");
  }
}

void setup() {

  // WIFI
  Serial.println("Booting...");
  Serial.begin(115200);

  pinMode(OnboardLED, OUTPUT);

  // Ubidots Client Config.
  Serial.println("Configurando cliente do ubidots");
  //ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASSWORD);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  timer = millis();
  Serial.println("");
  ubidots.subscribeLastValue(SUB_DEVICE_LABEL, SUB_VARIABLE_LABEL);
  delay(100);
}

void loop() {
  if (!ubidots.connected()){
  Serial.println("<Wifi Status> - DISCONNECTED");
  Serial.println("Trying to connect.");
    while (!ubidots.connected()) {
      Serial.print(".");
      ubidots.subscribeLastValue(SUB_DEVICE_LABEL, SUB_VARIABLE_LABEL);
      ubidots.reconnect();
      delay(1000);
    }
  }
  else {
    Serial.println("<Wifi Status> - CONNECTED");
  }

  
  timer = millis();
  delay(1000);
  ubidots.loop();

}
