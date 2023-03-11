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
}