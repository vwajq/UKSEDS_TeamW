#ifndef RFMRECEIVER
#define RFMRECEIVER

#include <Arduino.h>
#include <RadioLib.h>

#define NSS 10
#define DIO0 41
#define DIO1 42
#define RESET 9

extern int receivedState;
extern volatile bool receivedFlag;
extern volatile bool interruptFlag;

extern RFM95 rfm;

void rfmReceiverSetup();

void setReceivedFlag();

void rfmRead();

#endif