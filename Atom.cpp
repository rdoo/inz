#include "Atom.h"

void Atom::mass(double m){
	masa = m;
}
void Atom::position(double x, double y, double z){
	Vector a(x, y, z);
	pos = a;
}
void Atom::velocity(double x, double y, double z){
	Vector a(x, y, z);
	vel = a;
}

Vector& Atom::position(){
	return pos;
}

Vector& Atom::velocity(){
	return vel;
}

double Atom::mass(){
	return masa;
}
