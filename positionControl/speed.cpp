#ifndef SPEED
#define SPEED
#include "speed.h"
#endif

Timer timer_s;
double ldesiredSpeed;
double rdesiredSpeed;

double lerror_p, rerror_p;
double lgain, rgain;

void speedControl_init(){
	lerror_p = 0;
	rerror_p = 0;
	rgain = 0;
	lgain = 0;
	timer_s.every(5, checkSpeed);
}

void speedTimerUpdate(){
	timer_s.update();
}

void checkSpeed() {
  double rerror = rightOmega - rdesiredSpeed;
  double lerror = leftOmega - ldesiredSpeed;

  rerror_p += rki * rerror;
  lerror_p += lki * lerror;

  if (rerror_p > upperLimit) {
    rerror_p = upperLimit;
  } else if (rerror_p < lowerLimit) {
    rerror_p = lowerLimit;
  }

  if (lerror_p > upperLimit) {
    lerror_p = upperLimit;
  } else if (lerror_p < lowerLimit) {
    lerror_p = lowerLimit;
  }
  
  rgain = rerror_p + rkp * rerror;
  lgain = lerror_p + lkp * lerror;

  if (rgain > upperLimit) {
    rgain = upperLimit;
  } else if (rgain < lowerLimit) {
    rgain = lowerLimit;
  }

  if (lgain > upperLimit) {
    lgain = upperLimit;
  } else if (lgain < lowerLimit) {
    lgain = lowerLimit;
  }

  setRightMotor(rgain);
  setLeftMotor(lgain);
}

void setRightOmega(double omega){
	//if(abs(omega) > 1)
	  rdesiredSpeed = omega;
  //else
    //rdesiredSpeed = omega > 0 ? 1:-1;
}

void setLeftOmega(double omega){
	//if(abs(omega) > 1)
	  ldesiredSpeed = omega;
 // else
    //ldesiredSpeed = omega > 0 ? 1:-1;
}
