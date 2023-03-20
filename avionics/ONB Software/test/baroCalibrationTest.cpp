#include "baro.h"

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    bmpSetup();
}

void loop()
{
    bmpGetData();
    // Serial.println("Barometer Data");
    // Serial.println(bmpData.temperature);
    // Serial.println(bmpData.pressure);
    Serial.println(bmpData.altitude);
}