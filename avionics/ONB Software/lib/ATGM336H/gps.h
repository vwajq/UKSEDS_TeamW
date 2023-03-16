#ifndef GPS
#define GPS

#include <NMEAGPS.h>
#include <GPSport.h>

#define GPS_RX 18
#define GPS_TX 17

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

void gpsFindFix(const gps_fix &fix);

#endif