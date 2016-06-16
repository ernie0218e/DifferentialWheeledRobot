#include <Arduino.h>
#include "Timer.h"
#include "motor.h"
#include "encoder.h"
/*
#define lki -6
#define rki -4
#define lkp -3
#define rkp -2
*/
#define lki -8.1146
#define rki -7.0625
#define lkp -6.1042
#define rkp -5.0289

#define upperLimit 255
#define lowerLimit -255

void speedControl_init();
void speedTimerUpdate();
void checkSpeed();

void setRightOmega(double omega);
void setLeftOmega(double omega);
