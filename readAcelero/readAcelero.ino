/*
* Lê os dados do acelerômetro
*/
#include <ArduinoLog.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Logger.h>

Adafruit_MPU6050 mpu;

void setup() {

  // Log Configuration
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setShowLevel(true);    // Do not show loglevel, we will do this in the prefix
  
  Serial.begin(115200);
  Serial.print("Procurando pelo MPU6050");
  if (!mpu.begin()) {
    Serial.print("Nao achamos o MPU6050 :( ");
    while (1) {
      delay(10);
    }
  }
  Serial.print("MPU6050 achado");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.print("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.print("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.print("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.print("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.print("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.print("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.print("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.print("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.print("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.print("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.print("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.print("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.print("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.print("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.print("5 Hz");
    break;
  }

  Serial.print("");
  delay(100);

}

void loop() {
   /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.print(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.print(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.print(" degC");

  Serial.print("");
  delay(500);
}
