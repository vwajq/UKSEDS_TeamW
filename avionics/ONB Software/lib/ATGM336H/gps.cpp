#include "gps.h"

gpsDataStruct gpsData;

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

void gpsGetData()
{
    if (gps.available(gpsPort))
    {
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
}