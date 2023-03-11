#ifndef GPS
#define GPS

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

#define rxPin 44
#define txPin 43
#define gpsBaud 9600

struct gpsDataStruct {
    double longitude;
    double latitude;
    double altitude;
};

extern gpsDataStruct gpsData;
extern TinyGPSPlus gps;


void gpsSetup();

void gpsGetData();

#endif