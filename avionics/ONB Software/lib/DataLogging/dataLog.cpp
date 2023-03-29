#include "dataLog.h"

Adafruit_SPIFlash flash(&flashTransport);
FatVolume fatfs; 
File32 my_file;

int iterations = 0;

void flashSetup()
{
    flash.begin();

    if (!fatfs.begin(&flash)) 
    {
        if (Serial)
        {
            Serial.println("Error: filesystem doesn't exist. Please try SdFat_format example to make one.");
        }
        while(true);
    }
}

void sdSetup()
{

}

void flashLogData()
{

}

void sdLogData()
{
    
}