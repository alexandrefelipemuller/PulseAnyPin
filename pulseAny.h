#ifndef PULSE_ANY_Hs
#define PULSE_ANY_H
#include <Arduino.h>
// Config pin to be used
void pinModePwm(int num, int pin);

// Output a value (num is not pin number, is the number provided on pinModePwm)
void analogWrite_(int num, int value);

void setupTimer1();

void initPWM(int num);

void setupFreq(int pinNum, int freq);

#endif
