#ifndef RFMRECEIVER
#define RFMRECEIVER

#include <Arduino.h>
#include <RadioLib.h>

#define NSS 4
#define DIO0 5
#define DIO1 6
#define RESET 7

#define BYTES_TO_RECEIVE 32 // Subject to change once data structure is finalised

extern int receivedState;
extern volatile bool receivedFlag;
extern volatile bool interruptFlag;

extern RFM95 rfm;
extern byte byteArrReceive[BYTES_TO_RECEIVE];

void rfmReceiverSetup();

void setReceivedFlag();

void rfmReceive();

#endif