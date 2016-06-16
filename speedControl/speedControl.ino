#include "motor.h"
#include "encoder.h"
#include "Timer.h"
#define speed 0
double ldesiredSpeed;
double rdesiredSpeed;

/*
#define lki -6
#define rki -4
#define lkp -3
#define rkp -2*/
#define lki -8.1146
#define rki -7.0625
#define lkp -6.1042
#define rkp -5.0289

#define upperLimit 255
#define lowerLimit -255

Timer t1;
Timer timer;

double lerror_p, rerror_p;
double lgain, rgain;

void checkSpeed();
void changeSpeed();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  encoder_init();
  motor_init();
  setLeftMotor(speed);
  setRightMotor(speed);
  lerror_p = 0;
  rerror_p = 0;
  rgain = 0;
  lgain = 0;
  ldesiredSpeed = 3;
  rdesiredSpeed = 3;
  t1.every(5, checkSpeed);
  timer.every(3000, changeSpeed);
}

void loop() {
  // put your main code here, to run repeatedly:
  TimerUpdate();
  t1.update();
  //timer.update();
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

void changeSpeed(){
  ldesiredSpeed++;
  rdesiredSpeed++;
  if(ldesiredSpeed > 4){
    ldesiredSpeed = -ldesiredSpeed;
  }
  if(rdesiredSpeed > 4){
    rdesiredSpeed = -rdesiredSpeed;
  }
}

