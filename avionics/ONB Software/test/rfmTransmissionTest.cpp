#include "rfmTransmitter.h"

void setup()
{
    Serial.begin(9600);
    while (!Serial);

    rfmTransmitterSetup();

    for (int i = 0; i < BYTES_TO_TRANSMIT; i++)
    {
        byteArrTransmit[i] = i;
        unsigned long preTransmit = micros();

        while (!transmittedFlag);
        rfmTransmit(byteArrTransmit);
        
        unsigned long postTransmit = micros();

        Serial.printf("Transmission time (us): %d", postTransmit - preTransmit);
    }
}

void loop()
{

}