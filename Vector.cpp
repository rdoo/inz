#include "Vector.h"

Vector::Vector(double a, double b){
	sklX = a;
	sklY = b;
}

Vector::Vector(){
	sklX = 0.;
	sklY = 0.;
}

void Vector::setX(double a){
	sklX = a;
}
void Vector::setY(double b){
	sklY = b;
}

double Vector::x(){
	return sklX;
}

double Vector::y(){
	return sklY;
}
