#ifndef Algorithm_h
#define Algorithm_h

#include "Atom.h"

const long double boltzmannConstant = 1.3806488e-23;

class Algorithm {
	long double temp = 10.; //!< temperatura
	long double delta = 1.e-11; //!< krawedz szescianu nowego polozenia
public:
	long double configurationEnergy(Atom* tab, int n);
	void step(Atom* tab, int n);
};

#endif
