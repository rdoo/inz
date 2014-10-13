#ifndef Vector_h
#define Vector_h

#include <string>

class Vector {
	long double sklX; //!< skladowa x wektora
	long double sklY; //!< skladowa y wektora
	long double sklZ; //!< skladowa z wektora

public:
	/**
	 * @brief Konstruktor tworzacy instancje klasy Vector z dwoma argumentami
	 * @arg a, b to poczatkowe skladowe wektora
	 */
	Vector(long double a, long double b, long double c);
	/**
	 * @brief Konstruktor tworzacy instancje klasy Vector ze skladowymi ustawianymi na 0.
	 */
	Vector();
	/**
	 * @brief Funkcja ustawiajaca skladowa x wektora
	 * @arg a to ustawiana skladowa x wektora
	 */
	void setX(long double a);
	/**
	 * @brief Funkcja ustawiajaca skladowa y wektora
	 * @arg b to ustawiana skladowa y wektora
	 */
	void setY(long double b);
	/**
	 * @brief Funkcja ustawiajaca skladowa z wektora
	 * @arg b to ustawiana skladowa z wektora
	 */
	void setZ(long double c);
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

	std::string toString();
};

#endif
