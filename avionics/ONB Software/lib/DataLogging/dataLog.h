#ifndef DATALOG
#define DATALOG

#include <SPI.h>
#include "SdFat.h"
#include "Adafruit_SPIFlash.h"

#include "flash_config.h"
#include <RingBuf.h>

#define SD_CONFIG SdioConfig(FIFO_SDIO)

// Logging at a rate of 1 kHz
#define LOG_INTERVAL_USEC 1000000

// NEED TO EDIT TO REFLECT ACTUAL FILE SIZE
#define LOG_FILE_SIZE 256*100*60*40 

// NEED TO EDIT TO REFLECT ACTUAL NUMBER OF BYTES PER LOG (IDEALLY NEEDS TO ACCOMMODATE FOR 800 MS OF DATA)
#define RING_BUF_CAPACITY 400*512 

extern Adafruit_SPIFlash flash;
extern FatVolume fatfs; 
extern File32 flashFile;

extern SdFat sd;
extern FsFile sdFile;

extern RingBuf<FsFile, RING_BUF_CAPACITY> rb;

struct loggedDataStruct{
    byte logCode;
    u_int64_t timeStamp;
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

extern loggedDataStruct data;

void flashSetup(unsigned long long timeStamp);

void sdSetup(unsigned long long timeStamp);

void flashLogData();

void sdLogData();

#endif

