#include "rfmReceiver.h"

void setup()
{
    Serial.begin(9600);
    while (!Serial);

    rfmReceiverSetup();
}

void loop()
{
    rfmReceive();
}