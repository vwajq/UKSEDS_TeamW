#ifndef GPS
#define GPS

#include <NMEAGPS.h>
#include <GPSport.h>

extern NMEAGPS  gps; // This parses the GPS characters
extern gps_fix  fix; // This holds on to the latest values

float * gps_get_data();

#endif