#include "motor.h"
#include "encoder.h"
#include "speed.h"
#include "position.h"

Position target[8];
int index=0;
Timer tm;
void calculate()
{
  //Serial.println("START");
  Position cur = Position(carX,carY,carTheta);
  bool isArrived = calculateWheelSpeed(cur,target[index]);
//Serial.println(TOMEGA[0]);
 //Serial.println(TOMEGA[1]);
  setLeftOmega(TOMEGA[0]);
  setRightOmega(TOMEGA[1]);
 //Serial.println(index);
  if(isArrived)
  {   
    index++;
    index%=8;
  }
  //Serial.println("END");
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  encoder_init();
  motor_init();
  speedControl_init();
  setLeftMotor(0);
  setRightMotor(0);
  int tickEvent = tm.every(10,calculate);
//  setLeftOmega(3);
//  setRightOmega(3);
  target[0] = Position(-60,0,0);
  target[1] = Position(540,0,0);
  target[2] = Position(600,-60,PI/2);
  target[3] = Position(600,540,PI/2);
  target[4] = Position(660,600,PI);
  target[5] = Position(60,600,PI);
  target[6] = Position(0,660,-PI/2);
  target[7] = Position(0,60,-PI/2);

  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

  
  TimerUpdate();
  speedTimerUpdate();  
  tm.update();
  
}

