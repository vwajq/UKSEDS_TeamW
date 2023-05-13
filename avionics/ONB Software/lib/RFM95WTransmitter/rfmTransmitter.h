#ifndef RFMTRANSMITTER
#define RFMTRANSMITTER

#include <Arduino.h>
#include <RadioLib.h>
#include <SPI.h>

#define NSS 4
#define DIO0 5
#define DIO1 6
#define RESET 7

#define BYTES_TO_TRANSMIT 32 // Subject to change once data structure is finalised

extern int transmissionState;
extern volatile bool transmittedFlag;
extern volatile bool interruptFlag;

extern RFM95 rfm;
extern byte byteArrTransmit[BYTES_TO_TRANSMIT];

void rfmTransmitterSetup();

void setTransmittedFlag();

void rfmTransmit(byte arr[]);

#endif