#ifndef IMU
#define IMU

#include <Adafruit_LSM6DSOX.h>

#define LSM_CS 9
#define LSM_MISO 11
#define LSM_SCK 12
#define LSM_MOSI 13

// Replace the accel and gyro doubles with Vector objects!!
struct imuDataStruct {
    double temperature;
    double accelX;
    double accelY;
    double accelZ;
    double gyroX;
    double gyroY;
    double gyroZ;
};

extern imuDataStruct imuData;

extern Adafruit_LSM6DSOX lsm; 

void imuSetup();

void imuGetData();

#endif