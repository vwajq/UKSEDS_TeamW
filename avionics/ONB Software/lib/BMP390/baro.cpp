#include "baro.h"

bmpDataStruct bmpData;

Adafruit_BMP3XX bmp;

void bmpSetup()
{
    if (!bmp.begin_SPI(BMP_CS))
    {
        if (Serial)
        {
            Serial.println("Could not detect BMP390");
        }
        while (true);
    }

    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}


void bmpGetData()
{
    bmpSetup();

    if (!bmp.performReading())
    {
        if (Serial)
        {
            Serial.println("BMP390 failed to perform reading");
        }
        while (true);
    }

    bmpData.temperature = bmp.temperature;
    bmpData.pressure = bmp.pressure;
    bmpData.altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
}