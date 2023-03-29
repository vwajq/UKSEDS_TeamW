#include "imu.h"

Adafruit_LSM6DSOX lsm; 
imuDataStruct imuData;

float gyrOffsetX = 0.004169;
float gyrOffsetY = 0.003486;
float gyrOffsetZ = -0.013477;

void imuSetup()
{
    if (!lsm.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI))
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
    imuData.accelX = accel.acceleration.x;
    imuData.accelY = accel.acceleration.y;
    imuData.accelZ = accel.acceleration.z;
    imuData.gyroX = gyro.gyro.x - gyrOffsetX;
    imuData.gyroY = gyro.gyro.y - gyrOffsetY;
    imuData.gyroZ = gyro.gyro.z - gyrOffsetZ;
}