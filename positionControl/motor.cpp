#ifndef MOTOR
#define MOTOR
#include "motor.h"
#endif

int leftMotorPin[2] = { 10,11 };
int rightMotorPin[2] = { 9,8 };
void  motor_init()
{
  for (int i = 0; i < 2; i++) {
    pinMode(rightMotorPin[i], OUTPUT);
    pinMode(leftMotorPin[i], OUTPUT);   
  }
}
void setRightMotor(int power)
{
	if (power >= 0)
	{
		analogWrite(rightMotorPin[0], power);
		analogWrite(rightMotorPin[1], 0);
	}
	else
	{
		analogWrite(rightMotorPin[0], 0);
		analogWrite(rightMotorPin[1], abs(power));
	}
}

void setLeftMotor(int power)
{
	if (power >= 0)
	{
		analogWrite(leftMotorPin[1], 0);
		analogWrite(leftMotorPin[0], power);
	}
	else
	{
		analogWrite(leftMotorPin[0], 0);
		analogWrite(leftMotorPin[1], abs(power));
	}
}
