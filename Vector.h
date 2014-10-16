#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector {
	long double m_x; //!< skladowa x wektora
	long double m_y; //!< skladowa y wektora
	long double m_z; //!< skladowa z wektora

public:
	/**
	 * @brief Konstruktor tworzacy instancje klasy Vector z dwoma argumentami
	 * @arg a, b to poczatkowe skladowe wektora
	 */
	Vector(long double x, long double y, long double z);
	/**
	 * @brief Konstruktor tworzacy instancje klasy Vector ze skladowymi ustawianymi na 0.
	 */
	Vector();
	/**
	 * @brief Funkcja ustawiajaca skladowa x wektora
	 * @arg a to ustawiana skladowa x wektora
	 */
	void setX(long double x);
	/**
	 * @brief Funkcja ustawiajaca skladowa y wektora
	 * @arg b to ustawiana skladowa y wektora
	 */
	void setY(long double y);
	/**
	 * @brief Funkcja ustawiajaca skladowa z wektora
	 * @arg b to ustawiana skladowa z wektora
	 */
	void setZ(long double z);
	/**
	 * @brief Funkcja zwracajaca skladowa x wektora
	 * @return skladowa x wektora
	 */
	long double x();
	/**
	 * @brief Funkcja zwracajaca skladowa y wektora
	 * @return skladowa y wektora
	 */
	long double y();
	/**
	 * @brief Funkcja zwracajaca skladowa z wektora
	 * @return skladowa z wektora
	 */
	long double z();

	long double distanceFromVector(Vector v);

	// overload + operator
	Vector operator+(Vector v);
	// overload - operator
	Vector operator-(Vector v);
	// overload * operator
	Vector operator*(long double number);
	// overload / operator
	Vector operator/(long double number);

	friend std::ostream& operator<<(std::ostream& os, const Vector& dt);
};

#endif
