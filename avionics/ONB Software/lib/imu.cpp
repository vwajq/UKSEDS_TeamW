#include "imu.h"

void imu_setup()
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

void imu_get_data(float *data)
{
    imu_setup();

    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
    lsm.getEvent(&accel, &gyro, &temp);

    data[0] = temp.temperature;
    data[1] = accel.acceleration.x;
    data[2] = accel.acceleration.y;
    data[3] = accel.acceleration.z;
    data[4] = gyro.gyro.x;
    data[5] = gyro.gyro.y;
    data[6] = gyro.gyro.z;
}