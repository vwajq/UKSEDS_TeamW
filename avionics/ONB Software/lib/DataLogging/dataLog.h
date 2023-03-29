#ifndef DATALOG
#define DATALOG

#include <SPI.h>
#include "SdFat.h"
#include "Adafruit_SPIFlash.h"
#include "flash_config.h"
#include <string.h>

extern Adafruit_SPIFlash flash;
extern FatVolume fatfs; 
extern File32 my_file;

struct loggedDataStruct{
    double bmpTemperature;
    double bmpPressure;
    double bmpAltitude;
    double imuAccelX;
    double imuAccelY;
    double imuAccelZ;
    double imuGyroX;
    double imuGyroY;
    double imuGyroZ;
    double gpsLongitude;
    double gpsLatitude;
};

void flashSetup();

void sdSetup();

void flashLogData();

void sdLogData();

#endif

