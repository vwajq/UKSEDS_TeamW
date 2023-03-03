#include <Arduino.h>
#include "baro.h"
#include "imu.h"

#include <SPI.h>
#include "SdFat.h"
#include "Adafruit_SPIFlash.h"
#include "flash_config.h"

Adafruit_SPIFlash flash(&flashTransport);

// file system object from SdFat
FatVolume fatfs; 
File32 my_file;

int iterations = 0;

void setup() {  
  flash.begin();

  if ( !fatfs.begin(&flash) ) {
    throw "Error: filesystem is not existed. Please try SdFat_format example to make one.";
    while(1)
    {
      yield();
      delay(1);
    }
  }
}

void loop() {
  // Add a delay???

  iterations++;

  my_file = fatfs.open("baro_data.txt", FILE_WRITE);
  float *bmp_data = bmp_get_data();

  // if the file opened okay, write to it:
  if (my_file) {
    if (iterations == 1) my_file.printf("Temperature, Pressure, Altitude");
    else my_file.printf("%f, %f, %f\n", bmp_data[0], bmp_data[1], bmp_data[2]);   
  } else {
    throw "Error opening baro_data.txt";
  }

  my_file.close();
}