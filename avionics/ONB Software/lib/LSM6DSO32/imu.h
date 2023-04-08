#ifndef IMU
#define IMU

#include <Adafruit_LSM6DSOX.h>

#define LSM_CS 9
#define LSM_MISO 40
#define LSM_SCK 41
#define LSM_MOSI 42

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