#include <Arduino.h>
#include "baro.h"
#include "imu.h"
#include "gps.h"

#include <SPI.h>
#include "SdFat.h"
#include "Adafruit_SPIFlash.h"
#include "flash_config.h"

Adafruit_SPIFlash flash(&flashTransport);

// file system object from SdFat
FatVolume fatfs; 
File32 baroFile;
File32 imuFile;
File32 gpsFile; 

int iterations = 0;

void setup() {  
  flash.begin();

  if (!fatfs.begin(&flash)) {
    if (Serial)
    {
      Serial.println("Error: filesystem doesn't exist. Please try SdFat_format example to make one.");
    }
    while(1)
    {
      yield();
      delay(1);
    }
  }
  bmpSetup();
  imuSetup();
  gpsSetup();
}

void loop() {
  // Add a delay???

  iterations++;

  baroFile = fatfs.open("baroData.txt", FILE_WRITE);
  imuFile = fatfs.open("imuData.txt", FILE_WRITE);
  gpsFile = fatfs.open("gpsData.txt", FILE_WRITE);

  bmpGetData();
  imuGetData();
  gpsGetData();

  // if the file opened okay, write to it:
  if (baroFile) 
  {
    if (iterations == 1) baroFile.println("Temperature, Pressure, Altitude");
    else baroFile.printf("%f, %f, %f\n", bmpData.temperature, bmpData.pressure, bmpData.altitude);
  } 
  else 
  {
    if (Serial)
    {
      Serial.println("Error opening baroData.txt");
    }
    while (true);
  }

  if (imuFile)
  {
    if (iterations == 1) imuFile.println("Temperature, AccelerationX, AccelerationY, AccelerationZ, AngleX, AngleY, AngleZ");
    else imuFile.printf("%f, %f, %f, %f, %f, %f, %f\n", imuData.temperature, imuData.accelX, imuData.accelY, imuData.accelZ, imuData.gyroX, imuData.gyroY, imuData.gyroZ);
  }
  else 
  {
    if (Serial)
    {
      Serial.println("Error opening imuData.txt");
    }
    while (true);
  }

  if (gpsFile)
  {
    if (iterations == 1) gpsFile.println("Longitude, Latitude, Satellites");
    else gpsFile.printf("%f, %f, %f\n", gpsData.longitude, gpsData.latitude, gpsData.satellites);
  }
  else 
  {
    if (Serial)
    {
      Serial.println("Error opening gpsData.txt");
    }
    while (true);
  }

  baroFile.close();
  imuFile.close();
  gpsFile.close();
}