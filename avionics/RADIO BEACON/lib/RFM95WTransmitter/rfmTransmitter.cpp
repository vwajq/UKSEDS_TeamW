#include "rfmTransmitter.h"


int transmissionState = RADIOLIB_ERR_NONE;
volatile bool transmittedFlag = false;

nRF24 rfm = new Module(CS, IRQ, CE);

void rfmTransmitterSetup()
{
    Serial.println("Initializing [nRF24] Transmitter...");
    // int rfmState = rfm.begin(868.0, 125.0, 12, 6, RADIOLIB_SX127X_SYNC_WORD, 13, 12, 0); 
    int rfmState = rfm.begin();
    if(rfmState == RADIOLIB_ERR_NONE) {
        Serial.println(F("success!"));
    } else {
        Serial.print(F("failed, code "));
        Serial.println(rfmState);
        while(true);
    }

    byte addr[] = {0x01, 0x23, 0x45, 0x67, 0x89};
    Serial.print(F("[nRF24] Setting address for transmit pipe ... \n"));
    rfmState = rfm.setTransmitPipe(addr);
    if(rfmState == RADIOLIB_ERR_NONE) {
        Serial.println(F("success!"));
    } else {
        Serial.print(F("failed, code "));
        Serial.println(rfmState);
        while(true);
    }

    rfm.setIrqAction(setTransmittedFlag);
    Serial.println(F("[nRF24] Starting transmission ... "));
    transmissionState = rfm.startTransmit("Beginning Transmission...");

    if (transmissionState == RADIOLIB_ERR_NONE){
        Serial.println("Transmission successful!");
    } else {
        Serial.print("Failed to transmit data, code: ");
        Serial.println(transmissionState);
        while (true);
    }

    transmittedFlag = false;

    #if defined(ESP8266) || defined(ESP32)
        ICACHE_RAM_ATTR
    #endif
}

void setTransmittedFlag()
{
    transmittedFlag = true;
}

void rfmTransmit()
{
    if (transmittedFlag)
    {
        transmittedFlag = false;

        if (transmissionState == RADIOLIB_ERR_NONE) {
        Serial.println(F("transmission finished!"));
        } else {
        Serial.print(F("failed, code "));
        Serial.println(transmissionState);
        }

        rfm.finishTransmit();

        delay(1000);
        
        Serial.print(F("[nRF24] Sending next packet ... "));
        transmissionState = rfm.startTransmit("Test");
    }
}