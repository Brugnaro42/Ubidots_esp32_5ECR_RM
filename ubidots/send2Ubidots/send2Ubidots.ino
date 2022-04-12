/*
 * This script send to UbiDots dashboard the value of the data readed
 * Authors: Daniel Moraes and Vitor Jun
 */

/*
 * Include LIBRARIES
 */
#include "confidentialStuff.h"

#include "UbidotsEsp32Mqtt.h"

#include <ArduinoLog.h>

#include <Adafruit_MPU6050.h>

#include <Adafruit_Sensor.h>

#include <Logger.h>

#include<Wire.h>

/*
 * Define constants
 */
unsigned long timer;

const int OnboardLED = 2;

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
double x, y, z;
int minVal = 265;
int maxVal = 402;

Ubidots ubidots(UBIDOTS_TOKEN);
Adafruit_MPU6050 mpu;

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

  // Log Configuration
  Log.begin(LOG_LEVEL_VERBOSE, & Serial);
  Log.setShowLevel(true);
  Serial.print("Procurando pelo MPU6050");

  if (!mpu.begin()) {
    Serial.print("Nao achamos o MPU6050 :( ");
    while (1) {
      delay(100);
    }
  }

  Serial.println("MPU6050 achado :)");
  Serial.println("Configurando sensor MPU");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

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
      ubidots.reconnect();
      ubidots.subscribeLastValue(SUB_DEVICE_LABEL, SUB_VARIABLE_LABEL);
      delay(1000);
    }
  }
  else {
    Serial.println("<Wifi Status> - CONNECTED");
  }
  /* Get new sensor events with the readings */
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  Serial.print("AngleX= ");
  Serial.println(x);

  Serial.print("AngleY= ");
  Serial.println(y);

  Serial.print("AngleZ= ");
  Serial.println(z);
  Serial.println("-----------------------------------------");

  ubidots.add("Giro x", x);
  ubidots.add("Giro y", y);
  ubidots.add("Giro z", z);
  ubidots.publish("esp32");
  ubidots.loop();
  timer = millis();
  delay(1000);

}
