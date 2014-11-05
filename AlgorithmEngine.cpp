#include "AlgorithmEngine.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>

long double AlgorithmEngine::configurationEnergy(Atom* tab, int n) {
	long double energy = 0.;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) { //TODO: wazne zeby poprawic
			if (&tab[i] != &tab[j]) {
				long double r = tab[i].position().distanceFromVector(
						tab[j].position()); // dlugosc wektora laczacego punkty

				energy += 4 * epsilon
						* (powl(sigma / r, 12) - powl(sigma / r, 6));
			}

		}
	return energy;
}

long double AlgorithmEngine::configurationEnergy2(Atom* tab, int n) {
	long double energy = 0.;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) { //TODO: wazne zeby poprawic
			if (&tab[i] != &tab[j]) {
				long double r = tab[i].position().distanceFromVector(
						tab[j].position()); // dlugosc wektora laczacego punkty

			energy += powl(a / r, b) + c / powl( r, d) * cosl(e * r + f);
			//std::cout << (double)(c / powl( r, d)) << std::endl;
				}

			}
		return energy;
	}
	void AlgorithmEngine::step(Atom* tab, int n) {
		currentEnergy = configurationEnergy(tab, n);
		//std::cout << "old energy: " << currentEnergy << std::endl;
		int i = rand() % n;
		long double dx = (rand() % 10001 / 10000. - 0.5) * m_delta;
		long double dy = (rand() % 10001 / 10000. - 0.5) * m_delta;
		long double dz =0;// (rand() % 10001 / 10000. - 0.5) * m_delta;
		tab[i].position() = tab[i].position() + Vector(dx, dy, dz);

		long double newEnergy = configurationEnergy(tab, n);
		//std::cout << "newEnergy: " << newEnergy << std::endl;

		steps++;

		if (newEnergy > currentEnergy) {
			long double boltzmann = expl(
					-(newEnergy - currentEnergy) / boltzmannConstant
							/ m_temperature);
			//std::cout << std::setprecision(12) << "boltz " << (double) boltzmann
			//		<< std::endl;
			//if (rand() % 10001 / 10000. > 0./*boltzmann*/) {
			//std::cout << "cofamy" << std::endl;
			tab[i].position() = tab[i].position() - Vector(dx, dy, dz);
			//}
		} else
			lastChangeStep = steps; //TODO: do zmiany
	}
