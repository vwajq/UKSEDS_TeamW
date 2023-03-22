// The purpose of this test is to determine the appropriate calibration settings for the IMU

#include "imu.h"

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    imuSetup();
}

void loop()
{
    imuGetData();
    Serial.println("IMU Data");
    Serial.printf("Temperature: %f\n", imuData.temperature);
    Serial.printf("Acceleration (x, y, z): %f %f %f\n", imuData.accelX, imuData.accelY, imuData.accelZ);
    Serial.printf("Angle (x, y, z): %f %f %f\n\n", imuData.gyroX, imuData.gyroY, imuData.gyroZ);
}