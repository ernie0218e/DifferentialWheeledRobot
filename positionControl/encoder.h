#include <Arduino.h>
#include "Timer.h"
#include "position.h"
#include <math.h>
#define L_ENCODERA 2
#define L_ENCODERB 3
#define R_ENCODERA 21
#define R_ENCODERB 20

#define MODE 1

extern volatile long lPhase, rPhase;
extern double rightOmega,leftOmega;
extern double carX, carY, carTheta;

void encoder_init();
double getLeftRad(); //Return 0~2*pi Value of theta in rad
double getRightRad(); //Return 0~2*pi Value of theta in rad
void count();
void TimerUpdate();
