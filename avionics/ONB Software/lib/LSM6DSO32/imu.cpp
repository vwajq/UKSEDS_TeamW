#include "imu.h"

Adafruit_LSM6DSOX lsm; 

void imuSetup()
{
    if (!lsm.begin_SPI(LSM_CS))
    {
        throw "Could not detect LSM6DSO32";
    }

    lsm.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
    lsm.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS );

    lsm.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
    lsm.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
}

void imuGetData()
{
    imuSetup();

    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
    lsm.getEvent(&accel, &gyro, &temp);

    imuData.temperature = temp.temperature;
    imuData.accelX = accel.acceleration.x;
    imuData.accelY = accel.acceleration.y;
    imuData.accelZ = accel.acceleration.z;
    imuData.gyroX = gyro.gyro.x;
    imuData.gyroY = gyro.gyro.y;
    imuData.gyroZ = gyro.gyro.z;
}