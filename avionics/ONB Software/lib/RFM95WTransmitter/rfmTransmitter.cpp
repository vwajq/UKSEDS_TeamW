#include "rfmTransmitter.h"


int transmissionState = RADIOLIB_ERR_NONE;
volatile bool transmittedFlag = false;
volatile bool interruptFlag = true;

byte byteArrTransmit[BYTES_TO_TRANSMIT];

RFM95 rfm = new Module(NSS, DIO0, RESET, DIO1);

void rfmTransmitterSetup()
{
    // int rfmState = rfm.begin(868.0, 125.0, 12, 6, RADIOLIB_SX127X_SYNC_WORD, 13, 12, 0); 
    int rfmState = rfm.begin(868.0);
    if (rfmState != RADIOLIB_ERR_NONE)
    {
        if (Serial)
        {
            Serial.println("Failed to initialise RFM95W Transmitter");
        }
        while (true);
    }

    rfm.setDio0Action(setTransmittedFlag);
    transmissionState = rfm.startTransmit("Beginning Transmission...");

    if (transmissionState != RADIOLIB_ERR_NONE)
    {
        if (Serial)
        {
            Serial.print("Failed to transmit data, code: ");
            Serial.println(transmissionState);
        }
        while (true);
    }
    #if defined(ESP8266) || defined(ESP32)
        ICACHE_RAM_ATTR
    #endif
}

void setTransmittedFlag()
{
    if (!interruptFlag)
    {
        return;
    }
    transmittedFlag = true;
}

void rfmTransmit(byte arr[])
{
    if (transmittedFlag)
    {
        interruptFlag = false;
        transmittedFlag = false;

        if (transmissionState != RADIOLIB_ERR_NONE)
        {
            if (Serial)
            {
                Serial.print("Failed to transmit data, code: ");
                Serial.println(transmissionState);
            }
            while (true);
        }

        rfm.finishTransmit();
        
        transmissionState = rfm.startTransmit(byteArrTransmit, BYTES_TO_TRANSMIT);
        interruptFlag = true;
    }
}