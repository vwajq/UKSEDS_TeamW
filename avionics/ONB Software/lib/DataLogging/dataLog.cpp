#include "dataLog.h"

Adafruit_SPIFlash flash(&flashTransport);
FatVolume fatfs; 
File32 flashFile;

SdFat sd;
FsFile sdFile;

RingBuf<FsFile, RING_BUF_CAPACITY> rb;
loggedDataStruct data;

char sdFileName[20];
char flashFileName[20];

void flashSetup(unsigned long long timeStamp)
{
    sprintf(flashFileName, "SSQ_FLASH%llu.csv", timeStamp);
    
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

void flashLogData()
{
    File32 dataFile = fatfs.open(flashFileName, FILE_WRITE);
    
    // Check that the file opened successfully and write a line to it.
    if (dataFile) {
        // Take a new data reading from a sensor, etc.  For this example just
        // make up a random number.
        int reading = random(0,100);
        // Write a line to the file.  You can use all the same print functions
        // as if you're writing to the serial monitor.  For example to write
        // two CSV (commas separated) values:
        dataFile.print("Sensor #1");
        dataFile.print(",");
        dataFile.print(reading, DEC);
        dataFile.println();
        // Finally close the file when done writing.  This is smart to do to make
        // sure all the data is written to the file.
        dataFile.close();
        Serial.println("Wrote new measurement to data file!");
    }
    else {
        Serial.println("Failed to open data file for writing!");
    }

    Serial.println("Trying again in 60 seconds...");

    // Wait 60 seconds.
    delay(60000L);
}

void sdSetup(unsigned long long timeStamp)
{
    sprintf(sdFileName, "SSQ_SD%llu.csv", timeStamp);

    if (!sd.begin(SD_CONFIG))
    {
        sd.initErrorHalt(&Serial);
    }

    // Open or create file - truncate existing file.
    if (!sdFile.open(sdFileName, O_RDWR | O_CREAT | O_TRUNC)) {
        Serial.printf("%s open failed\n\n", sdFileName);
        while (true);
    }

    // File must be pre-allocated to avoid huge
    // delays searching for free clusters.
    if (!sdFile.preAllocate(LOG_FILE_SIZE)) {
        Serial.println("preAllocate failed\n");
        sdFile.close();
        while (true);
    }

    // initialize the RingBuf.
    rb.begin(&sdFile);
    Serial.printf("SD Card set up complete.\n");
}

void sdLogData()
{
    // Max RingBuf used bytes. Useful to understand RingBuf overrun.
    size_t maxUsed = 0;

    // Min spare micros in loop.
    int32_t minSpareMicros = INT32_MAX;

    // Start time.
    uint32_t logTime = micros();

    size_t sizeCurr = rb.bytesUsed();

    if ((sizeCurr + sdFile.curPosition()) > (LOG_FILE_SIZE - 20))
    {
        Serial.println("File full - quitting.");
        sdFile.close();
        while(1);
    }

    if (sizeCurr > maxUsed) {
        maxUsed = sizeCurr;
    }

    if (sizeCurr >= 512 && !sdFile.isBusy()) {
        // Not busy only allows one sector before possible busy wait.
        // Write one sector from RingBuf to file.

        if (512 != rb.writeOut(512)) {
            Serial.println("writeOut failed");
            while(1);
        }
    }

    // Time for next point.
    logTime += LOG_INTERVAL_USEC;
    int32_t spareMicros = logTime - micros();
    if (spareMicros < minSpareMicros) {
      minSpareMicros = spareMicros;
    }
    if (spareMicros <= 0) {
      Serial.print("Rate too fast ");
      Serial.println(spareMicros);
      while(1);
    }

    // Wait until time to log data.
    if (micros() >= logTime)
    {
        rb.printf("%X,%llu,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
            data.logCode,
            data.timeStamp,
            data.bmpTemperature, data.bmpPressure, data.bmpAltitude,
            data.imuAccelX, data.imuAccelY, data.imuAccelZ,
            data.imuGyroX, data.imuGyroY, data.imuGyroZ,
            data.gpsLatitude, data.gpsLongitude
        );
        rb.println();

        if (rb.getWriteError()) {
            // Error caused by too few free bytes in RingBuf.
            Serial.println("WriteError");
            while(1);
        }

        // The below is just to print out the data logging performance
        // rb.sync();
        // sdFile.truncate();
        // sdFile.rewind();
        // // Print first twenty lines of file.
        // for (uint8_t n = 0; n < 20 && sdFile.available();) {
        //     int c = sdFile.read();
        //     if (c < 0) {
        //     break;
        //     }
        //     Serial.write(c);
        //     if (c == '\n') n++;
        // }
        // Serial.print("fileSize: ");
        // Serial.println((uint32_t)sdFile.fileSize());
        // Serial.print("maxBytesUsed: ");
        // Serial.println(maxUsed);
        // Serial.print("minSpareMicros: ");
        // Serial.println(minSpareMicros);
    }

    sdFile.close();
}