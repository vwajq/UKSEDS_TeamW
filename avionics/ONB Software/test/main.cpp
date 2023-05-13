#include <Arduino.h>
#include "baro.h"
#include "imu.h"
#include "gps.h"
#include "dataLog.h"
#include "rfmTransmitter.h"

// This value will change from day to day
#define SEALEVELPRESSURE_HPA (1013.25)

#define TEST_CODE 0xAA 
#define RTC_SYNC_CODE 0xBB
#define DATA_CODE 0xCC

bool isLaunched = false;
byte statusCode = 0b00000000;

void systemsTest();
void rtcSync();
void testController();

void setup() {  
  Serial.begin(115200);
  testController();

  Serial.printf("---------- INITIALISING SYSTEMS ----------\n\n");

  bmpSetup();
  imuSetup();
  gpsSetup();

  unsigned long long timeStamp = (unsigned long long)time(NULL);
  sdSetup(timeStamp);
  flashSetup(timeStamp);
  rfmTransmitterSetup();

  Serial.printf("---------- SYSTEMS INITIALISED ----------\n\n");
  testController();

  Serial.printf("---------- RTC SYNCING ----------\n\n");
  rtcSync();
  Serial.printf("---------- RTC SYNCED ----------\n\n");
  testController();

  systemsTest();
}

void loop() {
  unsigned long start = micros();

  unsigned long long timeStamp = (unsigned long long)time(NULL);

  bmpGetData(SEALEVELPRESSURE_HPA);
  data.bmpAltitude = bmpData.altitude;
  data.bmpPressure = bmpData.pressure;
  data.bmpTemperature = bmpData.temperature;

  imuGetData();
  data.imuAccelX = imuData.accelX;
  data.imuAccelY = imuData.accelY;
  data.imuAccelZ = imuData.accelZ;
  data.imuGyroX = imuData.gyroX;
  data.imuGyroY = imuData.gyroY;
  data.imuGyroZ = imuData.gyroZ;

  gpsGetData();
  data.gpsLatitude = gpsData.latitude;
  data.gpsLongitude = gpsData.longitude;

  data.logCode = statusCode;
  data.timeStamp = timeStamp;
}

void systemsTest(){
  Serial.printf("---------- STARTING SYSTEMS TEST ----------\n\n");

  Serial.println("Timestamp Test (1 Second): ");
  for (int i = 0; i < 10; i++)
  {
    unsigned long long timeStamp = (unsigned long long)time(NULL);
    Serial.printf("UNIX Time: %llu", timeStamp);
    delay(100);
  }
  Serial.println("Timestamp Test Complete!");
  testController();

  Serial.println("BMP390 Test (10 Seconds): ");
  for (int i = 0; i < 100; i++)
  {
    bmpGetData(SEALEVELPRESSURE_HPA);
    Serial.println("BMP390 Data: ");
    Serial.printf("Temperature - %f   Pressure - %f   Altitude - %f", 
                  bmpData.temperature, bmpData.pressure, bmpData.altitude);
    delay(100);
  }
  Serial.println("BMP390 Test Complete!");
  testController();

  Serial.println("LSM6DSO32 Test (10 Seconds): ");
  for (int i = 0; i < 100; i++)
  {
    imuGetData();
    Serial.println("LSM6DSO32 Data: ");
    Serial.printf("Temperature - %f   Accel (x, y, z) - %f, %f, %f   Gyro (x, y, z) - %f, %f %f",
                  imuData.temperature, imuData.accelX, imuData.accelY, imuData.accelZ, imuData.gyroX, imuData.gyroY, imuData.gyroZ);
    delay(100);
  }
  Serial.println("LSM6DSO32 Test Complete!");
  testController(); 

  Serial.println("ATGM336H Test (Until First Fix): ");
  while(!fix.valid.location){
    gpsGetData();
    Serial.println("ATGM336H Data: ");
    Serial.printf("Longitude - %d   Latitude - %d   Satellites - %d",
                  gpsData.longitude, gpsData.latitude, gpsData.satellites);
  }
  Serial.println("ATGM336H Test Complete!");
  testController();

  Serial.println("RFM95W Transmission Test (15 seconds): ");
  for (int i=0; i<500; i++) {
      byte data[23] = {};
      data[0] = TEST_CODE;
      while(!transmittedFlag);
      rfmTransmit(data);
      Serial.printf("Successfully transmitted data.\n");
      delay(30);
  }
  Serial.println("RFM95W Transmission Test Complete!\n\n");

  Serial.println("---------- SYSTEMS TEST COMPLETE ----------\n");
}

void rtcSync(){
  unsigned long long timeStamp = (unsigned long long)time(NULL);
  Serial.printf("UNIX Time: %llu\n", timeStamp);
  byte arr[BYTES_TO_TRANSMIT] = {RTC_SYNC_CODE};
  for (int i=0; i<8; i++) {
      arr[i+1] = (timeStamp >> (7 * 8 - (i * 8))) & 0xFF; 
  }
  while(!transmittedFlag); 
  rfmTransmit(arr);
  Serial.printf("\nSuccessfully transmitted UNIX TIME to ground station.\n");

}

void testController(){
  Serial.printf("\nPress Enter to continue");
  while (!Serial.available());
  Serial.println();
}