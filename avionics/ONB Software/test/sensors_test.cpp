#include <Arduino.h>
#include "baro.h"
#include "imu.h"

void setup() {  
  bmpSetup();
  imuSetup();
}

void loop() {
  bmpGetData();
  imuGetData();

  Serial.println("Barometer Data");
  Serial.printf("Temperature: %f\n", bmpData.temperature);
  Serial.printf("Pressure: %f\n", bmpData.pressure);
  Serial.printf("Altitude: %f\n\n", bmpData.altitude);

  Serial.println("IMU Data");
  Serial.printf("Temperature: %f\n", imuData.temperature);
  Serial.printf("Acceleration (x, y, z): %f %f %f\n", imuData.accelX, imuData.accelY, imuData.accelZ);
  Serial.printf("Angle (x, y, z): %f %f %f\n\n", imuData.gyroX, imuData.gyroY, imuData.gyroZ);

  Serial.println("");

  delay(1000);
}