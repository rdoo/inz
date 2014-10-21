#ifndef ALGORITHMENGINE_H
#define ALGORITHMENGINE_H

#include "Atom.h"

const long double boltzmannConstant = 1.3806488e-23;

class AlgorithmEngine {
	long double m_temperature = 10.; //!< temperatura
	long double m_delta = 1.e-10; //!< krawedz szescianu nowego polozenia
public:
	long double currentEnergy;
	int steps = 0;
	int lastChangeStep = 0;
	long double configurationEnergy(Atom* tab, int n);
	void step(Atom* tab, int n);
};

#endif
