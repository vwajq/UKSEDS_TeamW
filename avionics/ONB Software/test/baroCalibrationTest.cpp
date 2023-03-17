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
    // Serial.printf("Temperature: %f\n", bmpData.temperature);
    Serial.printf("Pressure: %f\n", bmpData.pressure);
    // Serial.printf("Altitude: %f\n\n", bmpData.altitude);
}