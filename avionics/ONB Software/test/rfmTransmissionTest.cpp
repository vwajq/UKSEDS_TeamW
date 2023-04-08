#include "rfmTransmitter.h"

void setup()
{
    Serial.begin(9600);
    while (!Serial);

    rfmTransmitterSetup();
}

void loop()
{
    rfmTransmit();
}