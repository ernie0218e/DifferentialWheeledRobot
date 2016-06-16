#ifndef POSITION
#define POSITION
#include <Arduino.h>
#include <math.h>



//const double PI = 3.1415926;
extern double TOMEGA[2];
double principleValue(double a);

class Position
{
	public:	
		
		Position(){};
		Position(double,double,double); // x, y, theta
		void printPosition();		
		double distance(double a, double b);// x,y
		double distance(Position a);
		double deltaAngle(double a, double b);// x,y
		double deltaAngle(Position a);
		void setX(double a){x = a;};
		void setY(double a){y = a;};
    void setIsPenup(bool a){isPenup=a;};
		void setTheta(double a){theta = a;};
		double getX(){return x;};
		double getY(){return y;};		
		double getTheta(){return theta;};
    double getIsPenup(){return isPenup;};
		
	private:
		double x;
		double y;
		double theta;// rad unit		
		bool isPenup;
};

bool calculateWheelSpeed(Position a, Position b);// current position , desire Position
bool calculateWheelSpeed(Position a, Position b,double Vmax);

#endif
