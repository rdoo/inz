#ifndef Vector_h
#define Vector_h

class Vector{
	double sklX; //!< skladowa x wektora
	double sklY; //!< skladowa y wektora

public:
/**
 * @brief Konstruktor tworzacy instancje klasy Vector z dwoma argumentami
 * @arg a, b to poczatkowe skladowe wektora
 */
	Vector(double a, double b);
/**
 * @brief Konstruktor tworzacy instancje klasy Vector ze skladowymi ustawianymi na 0.
 */
	Vector();
/**
 * @brief Funkcja ustawiajaca skladowa x wektora
 * @arg a to ustawiana skladowa x wektora
 */
	void setX(double a);
/**
 * @brief Funkcja ustawiajaca skladowa y wektora
 * @arg b to ustawiana skladowa y wektora
 */
	void setY(double b);
/**
 * @brief Funkcja zwracajaca skladowa x wektora
 * @return skladowa x wektora
 */
	double x();
/**
 * @brief Funkcja zwracajaca skladowa y wektora
 * @return skladowa y wektora
 */
	double y();
};

#endif
