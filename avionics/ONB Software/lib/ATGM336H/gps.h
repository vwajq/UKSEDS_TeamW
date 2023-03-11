#ifndef GPS
#define GPS

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

#define rxPin 44
#define txPin 43
#define gpsBaud 115200

struct gpsDataStruct {
    double satellites;
    double longitude;
    double latitude;
    double altitude;
    double hour;
    double minute;
    double second;
};

extern gpsDataStruct gpsData;
extern TinyGPSPlus gps;


void gpsSetup();

void gpsGetData();

#endif