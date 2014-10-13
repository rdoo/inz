#include "Vector.h"
#include <string>
#include <sstream>

Vector::Vector(long double a, long double b, long double c){
	sklX = a;
	sklY = b;
	sklZ = c;
}

Vector::Vector(){
	sklX = 0.;
	sklY = 0.;
	sklZ = 0.;
}

void Vector::setX(long double a){
	sklX = a;
}
void Vector::setY(long double b){
	sklY = b;
}
void Vector::setZ(long double c){
	sklZ = c;
}

long double Vector::x(){
	return sklX;
}

long double Vector::y(){
	return sklY;
}

long double Vector::z(){
	return sklZ;
}

std::string Vector::toString(){
	std::ostringstream strstream;
	strstream << "x: " << sklX << "\t y: " << sklY << "\t z: " << sklZ;

	return strstream.str();
}
