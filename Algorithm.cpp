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
				long double dx = powl(
						tab[i].position().x() - tab[j].position().x(), 2);
				long double dy = powl(
						tab[i].position().y() - tab[j].position().y(), 2);
				long double dz = powl(
						tab[i].position().z() - tab[j].position().z(), 2);
				long double r = sqrtl(dx + dy + dz); // dlugosc wektora laczacego punkty

				energy += 4 * slow * tab[i].mass() * sigma * sigma
						* (powl(sigma / r, 12) - powl(sigma / r, 6));
			}

		}
	return energy;
}
void Algorithm::step(Atom* tab, int n) {
	long double currentEnergy = configurationEnergy(tab, n);
	int i = rand() % n;
	long double dx = (rand() % 10001 / 10000. - 0.5) * delta;
	std::cout << "old nergy: " << currentEnergy << std::endl;
	//std::cout << "rand: " << (rand() % 10000 / 10000. - 0.5) << std::endl;
	long double dy = (rand() % 10001 / 10000. - 0.5) * delta;
	long double dz = (rand() % 10001 / 10000. - 0.5) * delta;
	tab[i].position() = tab[i].position() + Vector(dx, dy, dz);
	//tab[i].position() = newx;
	/*tab[i].position().setX(tab[i].position().x() + dx);
	tab[i].position().setY(tab[i].position().y() + dy);
	tab[i].position().setZ(tab[i].position().z() + dz);*/
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
			/*tab[i].position().setX(tab[i].position().x() - dx);
			tab[i].position().setY(tab[i].position().y() - dy);
			tab[i].position().setZ(tab[i].position().z() - dz);*/
		}
	}
}
