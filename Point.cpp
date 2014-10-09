#include "Point.h"

void Point::mass(double m){
	masa = m;
}
void Point::position(double x, double y){
	Vector a(x, y);
	pos = a;
}
void Point::velocity(double x, double y){
	Vector a(x, y);
	vel = a;
}

Vector& Point::position(){
	return pos;
}

Vector& Point::velocity(){
	return vel;
}

double Point::mass(){
	return masa;
}
