#include "rfmReceiver.h"

int receivedState = RADIOLIB_ERR_NONE;
volatile bool receivedFlag = false;
volatile bool interruptFlag = true;

byte byteArrReceive[BYTES_TO_RECEIVE];

RFM95 rfm = new Module(NSS, DIO0, RESET, DIO1);

void rfmReceiverSetup()
{
    // int rfmState = rfm.begin(868.0, 125.0, 12, 6, RADIOLIB_SX127X_SYNC_WORD, 13, 12, 0); 
    int rfmState = rfm.begin(868.0);
    if (rfmState != RADIOLIB_ERR_NONE)
    {
        if (Serial)
        {
            Serial.println("Failed to initialise RFM95W Receiver");
        }
        while (true);
    }

    rfm.setDio0Action(setReceivedFlag);

    receivedState = rfm.startReceive();
    if (receivedState != RADIOLIB_ERR_NONE)
    {
        if (Serial)
        {
            Serial.print("Failed to receive data, code: ");
            Serial.println(receivedState);
        }
        while (true);
    }

    #if defined(ESP8266) || defined(ESP32)
        ICACHE_RAM_ATTR
    #endif
}

void setReceivedFlag()
{
    if (!interruptFlag)
    {
        return;
    }
    receivedFlag = true;
}

void rfmReceive()
{
    if (receivedFlag)
    {
        interruptFlag = false;
        receivedFlag = false;
    }

    String str;
    receivedState = rfm.readData(str);
    // receivedState = rfm.readData(byteArrReceive, BYTES_TO_RECEIVE);

    if (receivedState == RADIOLIB_ERR_NONE) {
      // packet was successfully received
      Serial.println(F("RFM95W Received packet!"));

      // print data of the packet
      Serial.print(F("RFM95W Data:\t\t"));
      Serial.println(str);

      // print RSSI (Received Signal Strength Indicator)
      Serial.print(F("RFM95W RSSI:\t\t"));
      Serial.print(rfm.getRSSI());
      Serial.println(F(" dBm"));

      // print SNR (Signal-to-Noise Ratio)
      Serial.print(F("RFM95W SNR:\t\t"));
      Serial.print(rfm.getSNR());
      Serial.println(F(" dB"));

      // print frequency error
      Serial.print(F("RFM95W Frequency error:\t"));
      Serial.print(rfm.getFrequencyError());
      Serial.println(F(" Hz"));

    } else if (receivedState == RADIOLIB_ERR_CRC_MISMATCH) {
      // packet was received, but is malformed
      Serial.println(F("RFM95W CRC error!"));

    } else {
      // some other error occurred
      Serial.print("Failed to receive data, code: ");
      Serial.println(receivedState);
      while (true);

    receivedState = rfm.startReceive();
    interruptFlag = true;
    }
}

