#include "gps.h"

NMEAGPS gps;
gps_fix fix;

gpsDataStruct gpsData;

void gpsSetup()
{
    gpsPort.begin(9600, SERIAL_8N1, 18, 17);
}

void gpsGetData()
{
    if (gps.available(gpsPort))
    {
        doSomeWork(gps.read());   
    }
}

void doSomeWork(const gps_fix & fix)
{
    if (fix.valid.location)
    {
        gpsData.longitude = fix.longitudeL();
        gpsData.latitude = fix.latitudeL();
        if (fix.valid.satellites)
        {
            gpsData.satellites = fix.satellites;
        }
    }
    else
    {
        gpsData.longitude = -1;
        gpsData.latitude = -1;
        gpsData.satellites = -1;
    }
}


