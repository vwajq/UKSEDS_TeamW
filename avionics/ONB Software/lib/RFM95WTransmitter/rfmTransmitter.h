#ifndef RFMTRANSMITTER
#define RFMTRANSMITTER

#include <Arduino.h>
#include <RadioLib.h>

#define NSS 4
#define DIO0 5
#define DIO1 6
#define RESET 7

#define BYTES_TO_TRANSMIT 32

extern int transmissionState;
extern volatile bool transmittedFlag;
extern volatile bool interruptFlag;

extern RFM95 rfm;

void rfmTransmitterSetup();

void setTransmittedFlag();

void rfmTransmit();

#endif