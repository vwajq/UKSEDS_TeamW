#include <Arduino.h>
#include "baro.h"
#include "imu.h"
#include "gps.h"

void setup() { 
    Serial.begin(115200);
    while (!Serial);

    bmpSetup();
    imuSetup();
}

void loop() {
    bmpGetData();

    Serial.println("Barometer Data");
    Serial.printf("Temperature: %f\n", bmpData.temperature);
    Serial.printf("Pressure: %f\n", bmpData.pressure);
    Serial.printf("Altitude: %f\n\n", bmpData.altitude);

    imuGetData();
    Serial.println("IMU Data");
    Serial.printf("Temperature: %f\n", imuData.temperature);
    Serial.printf("Acceleration (x, y, z): %f %f %f\n", imuData.accelX, imuData.accelY, imuData.accelZ);
    Serial.printf("Angle (x, y, z): %f %f %f\n\n", imuData.gyroX, imuData.gyroY, imuData.gyroZ);

    gpsGetData();
    Serial.println("GPS Data");
    Serial.printf("Longitude: %f\n", gpsData.longitude);
    Serial.printf("Latitude: %f\n", gpsData.latitude);
    Serial.printf("Altitude: %f\n\n", gpsData.altitude);

    Serial.println("");

    delay(1000);
}