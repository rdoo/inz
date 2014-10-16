#include "Atom.h"

void Atom::mass(long double m) {
	m_mass = m;
}
void Atom::position(long double x, long double y, long double z) {
	m_position = Vector(x, y, z);
}
void Atom::velocity(long double x, long double y, long double z) {
	m_velocity = Vector(x, y, z);
}

Vector& Atom::position() {
	return m_position;
}

Vector& Atom::velocity() {
	return m_velocity;
}

long double Atom::mass() {
	return m_mass;
}
