#include "Vector.h"

Vector::Vector(double a, double b, double c){
	sklX = a;
	sklY = b;
	sklZ = c;
}

Vector::Vector(){
	sklX = 0.;
	sklY = 0.;
	sklZ = 0.;
}

void Vector::setX(double a){
	sklX = a;
}
void Vector::setY(double b){
	sklY = b;
}
void Vector::setZ(double c){
	sklZ = c;
}

double Vector::x(){
	return sklX;
}

double Vector::y(){
	return sklY;
}

double Vector::z(){
	return sklZ;
}
