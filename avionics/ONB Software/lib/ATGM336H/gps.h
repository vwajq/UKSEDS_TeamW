#ifndef GPS
#define GPS

#include <NMEAGPS.h>
#include <GPSport.h>

struct gpsDataStruct {
    double longitude;
    double latitude;
    double altitude;
};

extern gpsDataStruct gpsData;

extern NMEAGPS  gps; // This parses the GPS characters
extern gps_fix  fix; // This holds on to the latest values

void gpsSetup();

void gpsGetData();

#endif