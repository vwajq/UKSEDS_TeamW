#ifndef RFMTRANSMITTER
#define RFMTRANSMITTER

#include <Arduino.h>
#include <RadioLib.h>

#define NSS 10
#define DIO0 41
#define DIO1 42
#define RESET 9

extern int transmissionState;
extern volatile bool transmittedFlag;
extern volatile bool interruptFlag;

extern RFM95 rfm;

void rfmTransmitterSetup();

void setTransmittedFlag();

void rfmTransmit();

#endif