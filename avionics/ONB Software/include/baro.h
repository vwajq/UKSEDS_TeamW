#ifndef BARO
#define BARO

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;

void bmp_setup()
{
    if (!bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI))
    {
        throw "Could not detect BMP390";
    }

    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}


float * bmp_data()
{
    bmp_setup();

    if (!bmp.performReading())
    {
        throw "BMP390 failed to perform reading";
    }

    float data[3];

    data[0] = bmp.temperature;
    data[1] = bmp.pressure;
    data[2] = bmp.readAltitude(SEALEVELPRESSURE_HPA);

    return data;
}

#endif 