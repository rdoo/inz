#include "AlgorithmEngine.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>

long double AlgorithmEngine::configurationEnergy(Atom* tab, int n) {
	long double energy = 0.;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			long double r = tab[i].position().distanceFromVector(
					tab[j].position()); // dlugosc wektora laczacego punkty

			energy += 4 * epsilon * (powl(sigma / r, 12) - powl(sigma / r, 6));
		}
	return energy;
}

long double AlgorithmEngine::configurationEnergy2(Atom* tab, int n) {
	long double energy = 0.;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			long double r = tab[i].position().distanceFromVector(
					tab[j].position()); // dlugosc wektora laczacego punkty

			energy += powl(a / r / 1e10, b) + c / powl(r * 1e10, d) * cosl(e * r * 1e10 + f);
			std::cout << (double) powl(a / r / 1e10, b) << " "
					<< (double) (c / powl(r * 1e10, d)) << " "
					<< (double) cosl(e * r * 1e10 + f) << std::endl;
			//std::cout << (double)(c / powl( r, d)) << std::endl;
		}
	return energy * elementaryCharge;
}
void AlgorithmEngine::step(Atom* tab, int n) {
	currentEnergy = configurationEnergy2(tab, n);

	int i = rand() % n;
	long double dx = (rand() % 10001 / 10000. - 0.5) * m_delta;
	long double dy = (rand() % 10001 / 10000. - 0.5) * m_delta;
	long double dz = (rand() % 10001 / 10000. - 0.5) * m_delta;
	tab[i].position() = tab[i].position() + Vector(dx, dy, dz);

	long double newEnergy = configurationEnergy2(tab, n);
	steps++;

	if (newEnergy > currentEnergy) {
		/*long double boltzmann = expl(
		 -(newEnergy - currentEnergy) / boltzmannConstant / temp);
		 if ((rand() % 10001 / 10000. > boltzmann) || temp < 1)*/
		tab[i].position() = tab[i].position() - Vector(dx, dy, dz);
	} else
		lastChangeStep = steps;
	if (temp >= 1)
		temp = temp * expl(-0.02);

}
