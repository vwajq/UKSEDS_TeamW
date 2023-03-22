#include "gps.h"

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    gpsSetup();
}

void loop()
{
    gpsGetData();
    Serial.println("GPS Data");
    Serial.printf("Longitude: %" PRId32 "\n", gpsData.longitude);
    Serial.printf("Latitude: %" PRId32 "\n", gpsData.latitude);
    Serial.printf("Satellites Detected: %" PRIu8 "\n\n", gpsData.satellites);

    // Prints out the TTFF and stops program execution
    if (gpsData.satellites > 0)
    {
        Serial.print(millis() / 1000);
        Serial.println(" seconds");
        while(true);
    }
}