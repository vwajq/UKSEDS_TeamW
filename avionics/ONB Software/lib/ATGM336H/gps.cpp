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
        
    }
    else
    {
        gpsData.longitude = -1;
        gpsData.latitude = -1;
    }

    if (gps.altitude.isValid()) gpsData.altitude = gps.altitude.meters();
    else gpsData.altitude = -1;
}