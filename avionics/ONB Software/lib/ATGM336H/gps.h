#ifndef GPS
#define GPS

#include <NMEAGPS.h>
#include <GPSport.h>

extern NMEAGPS gps;
extern gps_fix fix;

struct gpsDataStruct {
    uint8_t satellites;
    int32_t longitude;
    int32_t latitude;
};

extern gpsDataStruct gpsData;


void gpsSetup();

void gpsGetData();

void doSomeWork(const gps_fix & fix);

#endif