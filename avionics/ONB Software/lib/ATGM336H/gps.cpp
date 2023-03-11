#include "gps.h"

gpsDataStruct gpsData;

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

void gpsSetup()
{
    gpsPort.begin(9600);
}

void gpsGetData()
{
    if (!gps.available(gpsPort))
    {
        if (Serial)
        {
            Serial.println("Failed to connect to GPS");
        }
        while (true);
    }

    fix = gps.read();
        
    if (fix.valid.location) 
    {
        gpsData.longitude = fix.longitude();
        gpsData.latitude = fix.latitude();
    }

    if (fix.valid.altitude)
    {
        gpsData.altitude = fix.altitude();
    }
}