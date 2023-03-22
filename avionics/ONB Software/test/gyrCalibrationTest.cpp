// The purpose of this test is to determine the appropriate calibration settings for the IMU

#include "imu.h"

int settlingTime = 4;
int calibrationTime = 60;
int endTime;

float gyrOffsetX = 0;
float gyrOffsetY = 0;
float gyrOffsetZ = 0;
int numPoints;

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    imuSetup();

    Serial.println("Settling LSM6DSO32...");
    delay(1000*settlingTime);
    Serial.println("Done Settling!");

    endTime = millis() + calibrationTime*1000;
    while (millis() < endTime)
    {
        imuGetData();
        numPoints++;

        gyrOffsetX += imuData.gyroX;
        gyrOffsetY += imuData.gyroY;
        gyrOffsetZ += imuData.gyroZ;

        if (numPoints % 100 == 0)
        {
            Serial.printf("Calibrating Gyro... %d points completed\n", numPoints);
        }
    }

    Serial.printf("Calibration complete! %d points completed in total\n", numPoints);
    Serial.printf("Gyroscope Offsets (x, y, z): %f, %f, %f\n", gyrOffsetX/numPoints, gyrOffsetY/numPoints, gyrOffsetZ/numPoints);
    while (true);
}

void loop()
{
    // Prints out the IMU values (Acceleration in m/s^2, Angular Rate in rad/s)

    // imuGetData();
    // Serial.println("IMU Data");
    // // Serial.printf("Acceleration (x, y, z): %f %f %f\n", imuData.accelX, imuData.accelY, imuData.accelZ);
    // Serial.printf("Angle (x, y, z): %f %f %f\n\n", imuData.gyroX - 0.004169, imuData.gyroY - 0.003486, imuData.gyroZ + 0.013477);
    // delay(1000);
}