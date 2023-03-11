#include "gps.h"

gpsDataStruct gpsData;
TinyGPSPlus gps;

SoftwareSerial softSerial(rxPin, txPin);

void gpsSetup()
{
    softSerial.begin(gpsBaud);
}

void gpsGetData()
{
    gpsData.satellites = gps.satellites.value();

    if (gps.location.isValid())
    {
        gpsData.longitude = gps.location.lng();
        gpsData.latitude = gps.location.lat();
        gpsData.altitude = gps.altitude.meters();
        
    }
    else
    {
        gpsData.longitude = -1;
        gpsData.latitude = -1;
        gpsData.altitude = -1;
    }

    if (gps.time.isValid())
    {
        gpsData.hour = gps.time.hour();
        gpsData.minute = gps.time.minute();
        gpsData.second = gps.time.second();
    }
    else
    {
        gpsData.hour = 0;
        gpsData.minute = 0;
        gpsData.second = 0;
    }
}