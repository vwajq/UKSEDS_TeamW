#include "imu.h"

Adafruit_LSM6DSOX lsm; 
imuDataStruct imuData;

float gyrOffsetX = 0.004169;
float gyrOffsetY = 0.003486;
float gyrOffsetZ = -0.013477;

float accOffsetX;
float accOffsetY;
float accOffsetZ;

float accelX;
float accelY;
float accelZ;

void imuSetup()
{
    if (!lsm.begin_SPI(LSM_CS))
    {
        if (Serial)
        {
            Serial.println("Failed to connect to IMU");
        }
        while (true);
    }

    lsm.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
    lsm.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS );

    lsm.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
    lsm.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
}

void imuGetData()
{
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
    lsm.getEvent(&accel, &gyro, &temp);

    imuData.temperature = temp.temperature;

    // Some of the offset values were tweaked via trial & error from the calibration results in order to improve accuracy
    // This tweaking is needed due to the limited capability of the simple calibration test employed
    accelX = accel.acceleration.x;
    accOffsetX = -0.990351*accelX + (0.213184);
    imuData.accelX = accelX - accOffsetX;

    accelY = accel.acceleration.y;
    accOffsetY = -0.986842*accelY + (-0.359139);
    imuData.accelY = accelY - accOffsetY;

    accelZ = accel.acceleration.z;
    accOffsetZ = -0.975009*accelZ + (-0.045458);
    imuData.accelZ = accelZ - accOffsetZ;

    imuData.gyroX = gyro.gyro.x - gyrOffsetX;
    imuData.gyroY = gyro.gyro.y - gyrOffsetY;
    imuData.gyroZ = gyro.gyro.z - gyrOffsetZ;
}