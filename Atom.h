#ifndef Atom_h
#define Atom_h

#include "Vector.h"

class Atom{
	long double masa;
	Vector pos; //!< wektor polozenia
	Vector vel; //!< wektor predkosci
	
public:
/**
 * @brief Funkcja ustawiajaca mase
 * @arg m to ustawiana masa
 */
	void mass(long double m);
/**
 * @brief Funkcja ustawiajace skladowe wektora polozenia
 * @arg x, y to ustawiane skladowe polozenia
 */
	void position(long double x, long double y, long double z);
/**
 * @brief Funkcja ustawiajace skladowe wektora predkosci
 * @arg x, y to ustawiane skladowe predkosci
 */
	void velocity(long double x, long double y, long double z);
/**
 * @brief Funkcja zwracajaca wektor polozenia
 * @return zwraca referencje do wektora polozenia w klasie Point
 */
	Vector& position();
/**
 * @brief Funkcja zwracajaca wektor predkosci
 * @return zwraca referencje do wektora predkosci w klasie Point
 */
	Vector& velocity();
/**
 * @brief Funkcja zwracajaca mase
 * @return zwraca wartosc masy w klasie Point
 */
	long double mass();
};


#endif
