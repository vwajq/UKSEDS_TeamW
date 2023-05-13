#ifndef RFMTRANSMITTER
#define RFMTRANSMITTER

#include <Arduino.h>
#include <RadioLib.h>

#define CS 0
#define IRQ 2
#define CE 1

extern int transmissionState;
extern volatile bool transmittedFlag;

extern nRF24 rfm;

void rfmTransmitterSetup();

void setTransmittedFlag();

void rfmTransmit();

#endif