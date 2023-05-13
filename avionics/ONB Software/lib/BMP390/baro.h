#ifndef BARO
#define BARO

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

#define BMP_CS 13
#define BMP_MISO 11
#define BMP_SCK 10
#define BMP_MOSI 12

struct bmpDataStruct {
    double temperature;
    double pressure;
    double altitude;
};

extern bmpDataStruct bmpData;

extern Adafruit_BMP3XX bmp;

void bmpSetup();

void bmpGetData(double SEALEVELPRESSURE_HPA);

#endif 