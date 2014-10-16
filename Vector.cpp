#include "Vector.h"
#include <math.h>
#include <string>
#include <sstream>

Vector::Vector(long double x, long double y, long double z) {
	m_x = x;
	m_y = y;
	m_z = z;
}

Vector::Vector() {
	m_x = 0.;
	m_y = 0.;
	m_z = 0.;
}

void Vector::setX(long double x) {
	m_x = x;
}

void Vector::setY(long double y) {
	m_y = y;
}

void Vector::setZ(long double z) {
	m_z = z;
}

long double Vector::x() {
	return m_x;
}

long double Vector::y() {
	return m_y;
}

long double Vector::z() {
	return m_z;
}

long double Vector::distanceFromVector(Vector v) {
	return sqrtl(
			powl(m_x - v.m_x, 2) + powl(m_y - v.m_y, 2) + powl(m_z - v.m_z, 2));
}

std::string Vector::toString() {
	std::ostringstream strstream;
	strstream << "x: " << (double) m_x << "\t y: " << (double) m_y << "\t z: "
			<< (double) m_z;

	return strstream.str();
}

Vector Vector::operator+(Vector v) {
	return Vector(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
}

Vector Vector::operator-(Vector v) {
	return Vector(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z);
}

Vector Vector::operator*(long double number) {
	return Vector(m_x * number, m_y * number, m_z * number);
}

Vector Vector::operator/(long double number) {
	return Vector(m_x / number, m_y / number, m_z / number);
}
