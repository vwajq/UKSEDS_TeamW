#ifndef RFMRECEIVER
#define RFMRECEIVER

#include <Arduino.h>
#include <RadioLib.h>

#define CS 0
#define IRQ 2
#define CE 1

extern int receivedState;
extern volatile bool receivedFlag;

extern nRF24 rfm;

void rfmReceiverSetup();

void setReceivedFlag();

void rfmReceive();

#endif