#include "rfmReceiver.h"

int receivedState = RADIOLIB_ERR_NONE;
volatile bool receivedFlag = false;
volatile bool interruptFlag = true;

RFM95 rfm = new Module(NSS, DIO0, RESET, DIO1);

void rfmReceiverSetup()
{
    int rfmState = rfm.begin(868.0);
    if (rfmState != RADIOLIB_ERR_NONE)
    {
        throw "Failed to initialise RFM95W Receiver";
    }

    rfm.setDio0Action(setReceivedFlag);

    receivedState = rfm.startReceive();
    if (receivedState != RADIOLIB_ERR_NONE)
    {
        throw "Failed to receive";
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

    if (receivedState == RADIOLIB_ERR_NONE) {
      // packet was successfully received
      Serial.println(F("[SX1278] Received packet!"));

      // print data of the packet
      Serial.print(F("[SX1278] Data:\t\t"));
      Serial.println(str);

      // print RSSI (Received Signal Strength Indicator)
      Serial.print(F("[SX1278] RSSI:\t\t"));
      Serial.print(rfm.getRSSI());
      Serial.println(F(" dBm"));

      // print SNR (Signal-to-Noise Ratio)
      Serial.print(F("[SX1278] SNR:\t\t"));
      Serial.print(rfm.getSNR());
      Serial.println(F(" dB"));

      // print frequency error
      Serial.print(F("[SX1278] Frequency error:\t"));
      Serial.print(rfm.getFrequencyError());
      Serial.println(F(" Hz"));

    } else if (receivedState == RADIOLIB_ERR_CRC_MISMATCH) {
      // packet was received, but is malformed
      Serial.println(F("[SX1278] CRC error!"));

    } else {
      // some other error occurred
      Serial.print(F("[SX1278] Failed, code "));
      Serial.println(receivedState);

    receivedState = rfm.startReceive();
    interruptFlag = true;

}

