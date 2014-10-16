#include "Algorithm.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <iomanip>

long double Algorithm::configurationEnergy(Atom* tab, int n) {
	long double energy = 0.;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) { //TODO: wazne zeby poprawic
			if (&tab[i] != &tab[j]) {
				long double slow = 1.e21;
				long double sigma = 3e-10L;

				long double r = tab[i].position().distanceFromVector(
						tab[j].position()); // dlugosc wektora laczacego punkty

				energy += 4 * slow * tab[i].mass() * sigma * sigma
						* (powl(sigma / r, 12) - powl(sigma / r, 6));
			}

		}
	return energy;
}
void Algorithm::step(Atom* tab, int n) {
	long double currentEnergy = configurationEnergy(tab, n);
	std::cout << "old energy: " << currentEnergy << std::endl;
	int i = rand() % n;
	long double dx = (rand() % 10001 / 10000. - 0.5) * delta;
	long double dy = (rand() % 10001 / 10000. - 0.5) * delta;
	long double dz = (rand() % 10001 / 10000. - 0.5) * delta;
	tab[i].position() = tab[i].position() + Vector(dx, dy, dz);

	long double newEnergy = configurationEnergy(tab, n);
	std::cout << "newEnergy: " << newEnergy << std::endl;
	if (newEnergy > currentEnergy) {
		long double boltzmann = expl(
				-(newEnergy - currentEnergy) / boltzmannConstant / temp);
		std::cout << std::setprecision(12) << "boltz " << (double) boltzmann
				<< std::endl;
		if (rand() % 10001 / 10000. > 0./*boltzmann*/) {
			std::cout << "cofamy" << std::endl;
			tab[i].position() = tab[i].position() - Vector(dx, dy, dz);
		}
	}
}
