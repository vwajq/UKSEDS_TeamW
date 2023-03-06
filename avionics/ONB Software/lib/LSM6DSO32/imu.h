#ifndef IMU
#define IMU

#include <Adafruit_LSM6DSOX.h>

#define LSM_CS 10
#define LSM_SCk 13
#define LSM_MISO 12
#define LSM_MOSI 11

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