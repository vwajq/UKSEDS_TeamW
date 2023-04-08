#ifndef BARO
#define BARO

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

#define BMP_CS 10
#define BMP_MISO 40
#define BMP_SCK 41
#define BMP_MOSI 42

// This value will change form day to day
#define SEALEVELPRESSURE_HPA (1013.25)

struct bmpDataStruct {
    double temperature;
    double pressure;
    double altitude;
};

extern bmpDataStruct bmpData;

extern Adafruit_BMP3XX bmp;

void bmpSetup();

void bmpGetData();

#endif 