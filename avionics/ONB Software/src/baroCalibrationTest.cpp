#include "baro.h"

#define SEALEVELPRESSURE_HPA (1013.25)

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    bmpSetup();
}

void loop()
{
    bmpGetData(SEALEVELPRESSURE_HPA);
    // Serial.println("Barometer Data");
    // Serial.println(bmpData.temperature);
    // Serial.println(bmpData.pressure);
    Serial.println(bmpData.altitude);
}