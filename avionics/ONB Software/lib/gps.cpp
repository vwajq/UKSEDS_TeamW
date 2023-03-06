#include "gps.h"

float * gps_get_data()
{
    float data[3];

    if (gps.available(gpsPort))
    {
        fix = gps.read();
        
        if (fix.valid.location) 
        {
            data[0] = fix.longitude();
            data[1] = fix.latitude();
        }

        if (fix.valid.altitude)
        {
            data[2] = fix.altitude();
        }
    }

    return data;
}