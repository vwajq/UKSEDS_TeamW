#include "dataLog.h"

void setup()
{
    Serial.begin(9600);
    while (!Serial);

    sdSetup(0);
}

void loop()
{
    data.timeStamp = micros();

    unsigned long preLog = micros();

    sdLogData();

    unsigned long postLog = micros();

    Serial.printf("Log time (us): %d", postLog - preLog);
    delay(100);
}