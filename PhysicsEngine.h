#ifndef PhysicsEngine_h
#define PhysicsEngine_h

#include "Atom.h"

const double G = 1e-11;

class PhysicsEngine{
	double ts; //!< krok czasowy
	double totalTime = 0.; //!< calkowity czas symulacji

public:
/**
 * @brief Funkcja ustawiajaca krok czasowy
 * @arg dt to krok czasowy
 */
	void timeStep(double dt);
/**
 * @brief Funkcja symulujaca zmiany wektora polozenia i predkosci
 * @arg p to punkt, ktorego polozenie i predkosc sa symulowane; f to sila jaka dziala na ten punkt
 */
	void step(Atom& p, Vector& f);
/**
 * @brief Funkcja symulujaca zmiany wektora polozenia i predkosci danych punktów oddzialujacych grawitacyjnie
 * @arg tab to tablica punktow, ktorych polozenie i predkosc sa symulowane; n to liczba tych punktow
 */
	void step(Atom* tab, int n);
/**
 * @brief Funkcja zwracajaca calkowity czas trwania symulacji
 * @return zwraca calkowity czas trwania symulacji
 */
	double timeFromBeginning();
/**
 * @brief Funkcja zwracajaca wektor sily grawitacyjnej pomiedzy dwoma punktami
 * @arg p1, p2 to punkty, dla ktorych sila jest liczona
 * @return zwraca wektor sily grawitacyjnej pomiedzy dwoma punktami
 */
	Vector gravity(Atom& p1, Atom& p2);

	Vector lennarda(Atom& p1, Atom& p2);
};


#endif
