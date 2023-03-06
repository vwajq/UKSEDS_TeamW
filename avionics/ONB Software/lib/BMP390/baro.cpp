#include "baro.h"

Adafruit_BMP3XX bmp;

void bmp_setup()
{
    if (!bmp.begin_SPI(BMP_CS))
    {
        throw "Could not detect BMP390";
    }

    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}


void bmp_get_data(float *data)
{
    bmp_setup();

    if (!bmp.performReading())
    {
        throw "BMP390 failed to perform reading";
    }

    data[0] = bmp.temperature;
    data[1] = bmp.pressure;
    data[2] = bmp.readAltitude(SEALEVELPRESSURE_HPA);
}