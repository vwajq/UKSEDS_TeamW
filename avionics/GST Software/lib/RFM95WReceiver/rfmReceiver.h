#ifndef RFMRECEIVER
#define RFMRECEIVER

#include <Arduino.h>
#include <RadioLib.h>

#define NSS 4
#define DIO0 5
#define DIO1 6
#define RESET 7

#define BYTES_TO_RECEIVE 23

extern int receivedState;
extern volatile bool receivedFlag;
extern volatile bool interruptFlag;

extern RFM95 rfm;

void rfmReceiverSetup();

void setReceivedFlag();

void rfmReceive();

#endif