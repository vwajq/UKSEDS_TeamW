#ifndef IMU
#define IMU

#include <Adafruit_LSM6DSOX.h>

#define LSM_CS 10
#define LSM_SCk 13
#define LSM_MISO 12
#define LSM_MOSI 11

extern Adafruit_LSM6DSOX lsm; 

void imu_setup();

void imu_get_data(float *data);

#endif