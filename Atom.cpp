#include "Atom.h"
#include <cstdlib>

Atom::Atom() {
	m_mass = 0.;
	m_position = Vector(0., 0., 0.);
	m_velocity = Vector(0., 0., 0.);
}

Atom::Atom(long double mass, Vector position, Vector velocity) {
	m_mass = mass;
	m_position = position;
	m_velocity = velocity;
}

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

void generateAtoms(Atom* tab, int numberOfAtoms, long double diameter,
		long double mass) {
	Atom atom;
	Vector position;
	for (int i = 0; i < numberOfAtoms; i++) {
		position = Vector((rand() % 10001 / 10000. - 0.5) * diameter,
				(rand() % 10001 / 10000. - 0.5) * diameter,
				(rand() % 10001 / 10000. - 0.5) * diameter);
		atom = Atom(mass, position, Vector(0., 0., 0.));
		tab[i] = atom;
	}
}

void resetAtomsVelocities(Atom* tab, int numberOfAtoms) {
	for (int i = 0; i < numberOfAtoms; i++) {
		tab[i].velocity(0, 0, 0);
	}
}

