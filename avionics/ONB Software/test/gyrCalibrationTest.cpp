// The purpose of this test is to determine the appropriate calibration settings for the IMU

#include "imu.h"

// int settlingTime = 4;
// int calibrationTime = 60;
// int endTime;

// float gyrOffsetX;
// float gyrOffsetY;
// float gyrOffsetZ;
// int numPoints;

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    imuSetup();

    // gyrOffsetX = 0;
    // gyrOffsetY = 0;
    // gyrOffsetZ = 0;
    // numPoints = 0;

    // Serial.println("Settling LSM6DSO32...");
    // delay(1000*settlingTime);
    // Serial.println("Done Settling!");

    // endTime = millis() + calibrationTime*1000;
}

void loop()
{
    imuGetData();

    // if (millis() < endTime)
    // {
    //     numPoints++;
    //     gyrOffsetX += imuData.gyroX;
    //     gyrOffsetY += imuData.gyroY;
    //     gyrOffsetZ += imuData.gyroZ;

    //     if (numPoints % 100 == 0)
    //     {
    //         Serial.printf("Calibrating Gyro... %d points completed\n", numPoints);
    //     }
    // }
    // else
    // {
    //     Serial.printf("Calibration complete! %d points completed in total\n", numPoints);
    //     Serial.printf("Gyroscope Offsets (x, y, z): %f, %f, %f\n", gyrOffsetX/numPoints, gyrOffsetY/numPoints, gyrOffsetZ/numPoints);
    //     while (true);
    // }

    // Prints out the IMU values (Acceleration in m/s, Angular Rate in rad/s)
    Serial.println("IMU Data");
    // Serial.printf("Acceleration (x, y, z): %f %f %f\n", imuData.accelX, imuData.accelY, imuData.accelZ);
    Serial.printf("Angle (x, y, z): %f %f %f\n\n", imuData.gyroX - 0.004169, imuData.gyroY - 0.003486, imuData.gyroZ + 0.013477);
    delay(1000);
}