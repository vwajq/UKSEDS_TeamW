#include "rfmReceiver.h"

int receivedState = RADIOLIB_ERR_NONE;
volatile bool receivedFlag = false;

nRF24 rfm = new Module(CS, IRQ, CE);

void rfmReceiverSetup()
{
    Serial.println("Initializing [nRF24] Receiver...");
    // int rfmState = rfm.begin(868.0, 125.0, 12, 6, RADIOLIB_SX127X_SYNC_WORD, 13, 12, 0); 
    int rfmState = rfm.begin();
    if(rfmState == RADIOLIB_ERR_NONE) {
        Serial.println(F("success!"));
    } else {
        Serial.print(F("failed, code "));
        Serial.println(rfmState);
        while(true);
    }

    Serial.print(F("[nRF24] Setting address for receive pipe 0 ... \n"));
    byte addr[] = {0x01, 0x23, 0x45, 0x67, 0x89};
    rfmState = rfm.setReceivePipe(0, addr);
    if(rfmState == RADIOLIB_ERR_NONE) {
        Serial.println(F("success!"));
    } else {
        Serial.print(F("failed, code "));
        Serial.println(rfmState);
    while(true);
    }

    rfm.setIrqAction(setReceivedFlag);

    Serial.print(F("[nRF24] Starting to listen ... "));
    rfmState = rfm.startReceive();
    if (rfmState == RADIOLIB_ERR_NONE) {
        Serial.println(F("success!"));
    } else {
        Serial.print(F("failed, code "));
        Serial.println(rfmState);
        while (true);
    }

    #if defined(ESP8266) || defined(ESP32)
        ICACHE_RAM_ATTR
    #endif
}

void setReceivedFlag()
{
    receivedFlag = true;
}

void rfmReceive()
{
    if (receivedFlag)
    {
        receivedFlag = false;
    }

    String str;
    receivedState = rfm.readData(str);

    if (receivedState == RADIOLIB_ERR_NONE) {
        // packet was successfully received
        Serial.println(F("[nRF24] Received packet!"));

        // print data of the packet
        Serial.print(F("[nRF24] Data:\t\t\n"));
        Serial.println(str);

        // print RSSI (Received Signal Strength Indicator)
        Serial.print(F("[nRF24] RSSI:\t\t"));
        Serial.print(rfm.getRSSI());
        Serial.println(F(" dBm"));

        // print SNR (Signal-to-Noise Ratio)
        Serial.print(F("[nRF24] SNR:\t\t"));
        Serial.print(rfm.getSNR());
        Serial.println(F(" dB"));
    } else if (receivedState == RADIOLIB_ERR_CRC_MISMATCH) {
    // packet was received, but is malformed
    Serial.println(F("[nRF24] CRC error!"));

    } else {
    // some other error occurred
    Serial.print("Failed to receive data, code: ");
    Serial.println(receivedState);
    
    receivedState = rfm.startReceive();
    }
}

