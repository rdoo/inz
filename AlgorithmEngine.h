#ifndef ALGORITHMENGINE_H
#define ALGORITHMENGINE_H

#include "Atom.h"
#include <cmath>

const long double boltzmannConstant = 1.3806488e-23;

class AlgorithmEngine {
	long double m_temperature = 10.; //!< temperatura
	long double m_delta = 1.e-10; //!< krawedz szescianu nowego polozenia
	//long double sigma = 2.85e-10L;
	//long double epsilon = 8.01088e-20; // dla Al

	long double sigma = 2.2808e-10L;
	long double epsilon = 8.31468e-20; // dla Ni

	const double elementaryCharge = 1.602176565e-19;
	// Mihalkovic dla al:
	/*long double a = 2.230762e-10 * elementaryCharge;
	long double b = 7.903999;
	long double c = 18.244497e-10 * elementaryCharge;
	long double d = 5.314587;
	long double e = -3.315572;
	long double f = -6.826925;*/
	//dla ni
	long double b = 10.115240;
	long double a = 2.312051*powl(1.e-10 * elementaryCharge, 1/b);
	long double d = 2.633777;
	long double c = -3.708160*powl(1.e-10 * elementaryCharge, d);

	long double e = 3.144080;
	long double f = -1.212423;

public:
	long double currentEnergy;
	int steps = 0;
	int lastChangeStep = 0;
	long double configurationEnergy(Atom* tab, int n);
	long double configurationEnergy2(Atom* tab, int n);
	void step(Atom* tab, int n);
};

#endif
