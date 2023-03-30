// The purpose of this test is to determine the appropriate calibration settings for the IMU

#include "imu.h"

int settlingTime = 4;
int calibrationTime = 60;
int endTime;

float accelOffsetX = 0;
float accelOffsetY = 0;
float accelOffsetZ = 0;
int numPoints = 0;

float xSum = 0;
float ySum = 0;
float xSqSum = 0;
float xySum = 0;

int flag;

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    imuSetup();

    Serial.println("Settling LSM6DSO32...");
    delay(1000*settlingTime);
    Serial.println("Done Settling!");

    Serial.println("\nOrient the axis upwards against gravity - Click 1 When Ready");

    do 
    {
        flag = Serial.parseInt();
    }while (flag != 1);
    flag = 0;
    

    Serial.println("Beginning to calibrate acceleration in x-axis");
    endTime = millis() + calibrationTime*1000;
    while (millis() < endTime)
    {
        imuGetData();
        numPoints++;

        // accelOffsetX = 9.81 - imuData.accelX;
        // accelOffsetY = 9.81 - imuData.accelY;
        accelOffsetZ = 9.81 - imuData.accelZ;

        xSum += 9.81;

        // ySum += accelOffsetX;
        // ySum += accelOffsetY;
        ySum += accelOffsetZ;

        xSqSum += 9.81;
        
        // xySum += 9.81 * accelOffsetX;
        // xySum += 9.81 * accelOffsetY;
        xySum += 9.81 * accelOffsetZ;

        if (numPoints % 100 == 0)
        {
            Serial.printf("Calibrating acceleration (9.81 m/s^2) pt. 1... %d points completed\n", numPoints);
        }
    }

    Serial.println("\nOrient the axis downwards against gravity - Click 1 When Ready");

    do 
    {
        flag = Serial.parseInt();
    }while (flag != 1);
    flag = 0;

    Serial.println("Beginning to calibrate acceleration pt. 2");
    endTime = millis() + calibrationTime*1000;
    while (millis() < endTime)
    {
        imuGetData();
        numPoints++;

        // accelOffsetX = -9.81 - imuData.accelX;
        // accelOffsetY = -9.81 - imuData.accelY;
        accelOffsetZ = -9.81 - imuData.accelZ;

        xSum += -9.81;

        // ySum += accelOffsetX;
        // ySum += accelOffsetY;
        ySum += accelOffsetZ;

        xSqSum += (-9.81) * (-9.81);

        // xySum += -9.81 * accelOffsetX;
        // xySum += -9.81 * accelOffsetY;
        xySum += -9.81 * accelOffsetZ;

        if (numPoints % 100 == 0)
        {
            Serial.printf("Calibrating acceleration (-9.81 m/s^2) pt. 2... %d points completed\n", numPoints);
        }
    }


    Serial.println("\nOrient the axis perpendicular against gravity - Click 1 When Ready");

    do 
    {
        flag = Serial.parseInt();
    }while (flag != 1);
    flag = 0;
    
    Serial.println("Beginning to calibrate acceleration (0 m/s^2) pt. 3");
    endTime = millis() + calibrationTime*1000; 
    while (millis() < endTime)
    {
        imuGetData();
        numPoints++;

        // accelOffsetX = imuData.accelX;
        // accelOffsetY = imuData.accelY;
        accelOffsetZ = imuData.accelZ;

        xSum += 0;

        // ySum += accelOffsetX;
        // ySum += accelOffsetY;
        ySum += accelOffsetZ;

        xSqSum += 0 * 0;

        // xySum += 0 * accelOffsetX;
        // xySum += 0 * accelOffsetY;
        xySum += 0 * accelOffsetZ;

        if (numPoints % 100 == 0)
        {
            Serial.printf("Calibrating acceleration (0 m/s^2) pt. 3... %d points completed\n", numPoints);
        }
    }

    Serial.printf("Calibration complete! %d points completed in total\n", numPoints);

    float m = (numPoints * xySum - (xSum * ySum)) / ((numPoints * xSqSum) - (xSum) * (xSum));
    float c = (ySum - (m * xSum)) / numPoints;
    Serial.printf("m: %f\n", m);
    Serial.printf("c: %f\n", c);
    while (true);
}

void loop()
{
    // Prints out the IMU values (Acceleration in m/s^2, Angular Rate in rad/s)
    // Serial.println("IMU Data");
    // // Serial.printf("Acceleration (x, y, z): %f %f %f\n", imuData.accelX, imuData.accelY, imuData.accelZ);
    // Serial.printf("Angle (x, y, z): %f %f %f\n\n", imuData.gyroX - 0.004169, imuData.gyroY - 0.003486, imuData.gyroZ + 0.013477);
    // delay(1000);
}