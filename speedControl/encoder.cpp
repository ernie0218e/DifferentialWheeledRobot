#ifndef ENCODER
#define ENCODER
#include "encoder.h"
#endif

volatile bool l_phaseA, l_phaseB;
volatile bool r_phaseA, r_phaseB;
volatile long lPhase, rPhase;
const double pi = 3.1415926;
const long upperLimit = 39200;
const long upperLimit2 = 19600;
const long upperLimit1 = 9800;

Timer t;
double period;
double rightOmega,leftOmega;
double prevrightOmega1, prevleftOmega1, prevrightOmega2, prevleftOmega2;
double prevRightTheta, prevLeftTheta;
int tickEvent;

double carX, carY, carTheta;
double radius, gap;

void lPhaseA();
void lPhaseB();
void rPhaseA();
void rPhaseB();
void phaseA_left();
void phaseA_right();

void encoder_init(){

  prevRightTheta = 0;
  prevLeftTheta = 0;
  prevrightOmega1 = prevleftOmega1 = 0;
  prevrightOmega2 = prevleftOmega2 = 0;

  period = 2;//millisecond
  tickEvent = t.every(period, count);

  lPhase = rPhase = 0;

  //Setting Initial Value
  carX = carY = 0;
  carTheta = 0;
  
  radius = 34;//mm
  gap = 340;

  pinMode(L_ENCODERA, INPUT);
  pinMode(L_ENCODERB, INPUT);
  pinMode(R_ENCODERA, INPUT);
  pinMode(R_ENCODERB, INPUT);

  #if (MODE == 4)
    attachInterrupt(digitalPinToInterrupt(L_ENCODERA), lPhaseA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(L_ENCODERB), lPhaseB, CHANGE);
    attachInterrupt(digitalPinToInterrupt(R_ENCODERA), rPhaseA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(R_ENCODERB), rPhaseB, CHANGE);
  #elif (MODE == 2)
    attachInterrupt(digitalPinToInterrupt(L_ENCODERA), phaseA_left, CHANGE);
    attachInterrupt(digitalPinToInterrupt(R_ENCODERA), phaseA_right, CHANGE);
  #elif(MODE == 1)
    attachInterrupt(digitalPinToInterrupt(L_ENCODERA), phaseA_left, RISING);
    attachInterrupt(digitalPinToInterrupt(R_ENCODERA), phaseA_right, RISING);
  #endif
}

void count()
{
  double right = getRightRad();
  double left = getLeftRad();
  double threshold = pi;

  leftOmega = (left - prevLeftTheta);
  rightOmega = (right - prevRightTheta);
  
  if(leftOmega > threshold)
    leftOmega -= 2*pi;
  if(leftOmega < -threshold)
    leftOmega += 2*pi;
  if(rightOmega > threshold)
    rightOmega -= 2*pi;
  if(rightOmega < -threshold)
    rightOmega += 2*pi;

  leftOmega = leftOmega*1000/period;
  rightOmega = rightOmega*1000/period;

  leftOmega = (leftOmega*0.6 + prevleftOmega1*0.3 + prevleftOmega2*0.1);
  rightOmega = (rightOmega*0.6 + prevrightOmega1*0.3 + prevrightOmega2*0.1);

  prevleftOmega1 = leftOmega;
  prevleftOmega2 = prevleftOmega1;
  prevrightOmega1 = rightOmega;
  prevrightOmega2 = prevrightOmega1;
  
  carX += radius*cos(carTheta)/2*(rightOmega+leftOmega);
  carY += radius*sin(carTheta)/2*(rightOmega+leftOmega);
  carTheta += radius/gap*(rightOmega-leftOmega);
  if(carTheta >= 2*pi)
    carTheta-=(2*pi);
  if(carTheta < 0)
    carTheta+=(2*pi);

  /*if(leftOmega < 7.5){
    Serial.print("prevRightTheta:");
    Serial.println(prevRightTheta);
    Serial.print("left:");
    Serial.println(left);
  }*/
  
  prevRightTheta = right;
  prevLeftTheta = left;

//  Serial.print("right:");
  Serial.println(rightOmega);
//  Serial.print("left:");
  
    Serial.println(leftOmega);
//  Serial.println(right*1000);
//  Serial.println(left*1000);
}
void TimerUpdate()
{
  t.update();
}

void lPhaseA(){

  l_phaseA = PINE & _BV(4);
  l_phaseB = PINE & _BV(5);
 
  if(l_phaseA){
    if(l_phaseB ){
      lPhase += 1;
    }else{
      lPhase -= 1;
    }
  }else{
    if(l_phaseB==false){
      lPhase += 1;
    }else{
      lPhase -= 1;
    }
  }
  
  if(lPhase >= upperLimit)
    lPhase -= upperLimit;
  else if(lPhase < 0)
    lPhase = upperLimit - 1;
}

void lPhaseB(){

  l_phaseA = PINE & _BV(4);
  l_phaseB = PINE & _BV(5);
  
  if(l_phaseB ){
    if(l_phaseA==false){
      lPhase += 1;
    }else{
      lPhase -= 1;
    }
  }else{
    if(l_phaseA ){
      lPhase += 1;
    }else{
      lPhase -= 1;
    }
  }
  
  if(lPhase >= upperLimit)
    lPhase -= upperLimit;
  else if(lPhase < 0)
    lPhase = upperLimit - 1;
}

void rPhaseA(){
  
  r_phaseA = PIND & _BV(0);
  r_phaseB = PIND & _BV(1);
  
  if(r_phaseA){
    if(r_phaseB){
      rPhase += 1;
    }else{
      rPhase -= 1;
    }
  }else{
    if(r_phaseB == false){
      rPhase += 1;
    }else{
      rPhase -= 1;
    }
  }
  
  if(rPhase >= upperLimit)
    rPhase -= upperLimit;
  else if(rPhase < 0)
    rPhase = upperLimit - 1;
}

void rPhaseB(){

  r_phaseA = PIND & _BV(0);
  r_phaseB = PIND & _BV(1);
  if(r_phaseB ){
    if(r_phaseA == false){
      rPhase += 1;
    }else{
      rPhase -= 1;
    }
  }else{
    if(r_phaseA){
      rPhase += 1;
    }else{
      rPhase -= 1;
    }
  }
  
  if(rPhase >= upperLimit)
    rPhase -= upperLimit;
  else if(rPhase < 0)
    rPhase = upperLimit - 1;
}
double getLeftRad()
{ 
  #if MODE == 4
    return ((double)lPhase)*2*pi/(39200.0);
  #elif MODE == 2
    return ((double)lPhase)*2*pi/(upperLimit2);
  #elif MODE == 1
    return ((double)lPhase)*2*pi/(upperLimit1);
  #endif
}

double getRightRad()
{  
  #if MODE == 4
    return ((double)rPhase)*2*pi/(39200.0);
  #elif MODE == 2
    return ((double)rPhase)*2*pi/(upperLimit2);
  #elif MODE == 1
    return ((double)rPhase)*2*pi/(upperLimit1);
  #endif
}

void phaseA_left(){

#if MODE == 2
  l_phaseA = PINE & _BV(4);
  l_phaseB = PINE & _BV(5);
 
  if(l_phaseA){
    if(l_phaseB ){
      lPhase += 1;
    }else{
      lPhase -= 1;
    }
  }else{
    if(l_phaseB==false){
      lPhase += 1;
    }else{
      lPhase -= 1;
    }
  }
  
  if(lPhase >= upperLimit2)
    lPhase -= upperLimit2;
  else if(lPhase < 0)
    lPhase = upperLimit2 - 1;

#elif MODE == 1
  l_phaseB = PINE & _BV(5);
 
  if(l_phaseB ){
    lPhase += 1;
  }else{
    lPhase -= 1;
  }
  
  if(lPhase >= upperLimit1)
    lPhase -= upperLimit1;
  else if(lPhase < 0)
    lPhase = upperLimit1 - 1;
#endif

}

void phaseA_right(){

#if MODE == 2
  r_phaseA = PIND & _BV(0);
  r_phaseB = PIND & _BV(1);
  
  if(r_phaseA){
    if(r_phaseB){
      rPhase += 1;
    }else{
      rPhase -= 1;
    }
  }else{
    if(r_phaseB == false){
      rPhase += 1;
    }else{
      rPhase -= 1;
    }
  }
  
  if(rPhase >= upperLimit2)
    rPhase -= upperLimit2;
  else if(rPhase < 0)
    rPhase = upperLimit2 - 1;

#elif MODE == 1
  r_phaseB = PIND & _BV(1);
  
  if(r_phaseB){
    rPhase += 1;
  }else{
    rPhase -= 1;
  }
  
  if(rPhase >= upperLimit1)
    rPhase -= upperLimit1;
  else if(rPhase < 0)
    rPhase = upperLimit1 - 1;

#endif
}
