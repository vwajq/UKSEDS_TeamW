#include "gps.h"

NMEAGPS gps;
gps_fix fix;

gpsDataStruct gpsData;

void gpsSetup()
{
    gpsPort.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
}

void gpsGetData()
{
    if (gps.available(gpsPort))
    {
        gpsFindFix(gps.read());   
    }
}

void gpsFindFix(const gps_fix &fix)
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
        gpsData.longitude = 0;
        gpsData.latitude = 0;
        gpsData.satellites = 0;
    }
}


