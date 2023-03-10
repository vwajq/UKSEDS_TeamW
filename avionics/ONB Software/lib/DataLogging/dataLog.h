#ifndef DATALOG
#define DATALOG

#include <SPI.h>
#include "SdFat.h"
#include "Adafruit_SPIFlash.h"
#include "flash_config.h"
#include <string.h>

extern Adafruit_SPIFlash flash();
extern FatVolume fatfs; 
extern File32 my_file;

void flashSetup();

void flashLogData();

#endif

