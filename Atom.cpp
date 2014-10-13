#include "Atom.h"

void Atom::mass(long double m){
	masa = m;
}
void Atom::position(long double x, long double y, long double z){
	Vector a(x, y, z);
	pos = a;
}
void Atom::velocity(long double x, long double y, long double z){
	Vector a(x, y, z);
	vel = a;
}

Vector& Atom::position(){
	return pos;
}

Vector& Atom::velocity(){
	return vel;
}

long double Atom::mass(){
	return masa;
}
