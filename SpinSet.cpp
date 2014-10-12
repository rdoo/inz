#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "Spin.h"
#include "SpinSet.h"

void prepareSet(SpinSet& spins, int rozmiar){
	spins.tab = new Spin[rozmiar];
	spins.max = rozmiar;
}

int nSpins(SpinSet& spins){
	return spins.current;
}

void add(SpinSet& spins, Spin spin){
	if (spins.current == spins.max)
		std::cout << "nie mozna dodac wiecej spinow" << std::endl;
	else {
		spins.tab[spins.current] = spin;
		spins.current += 1;
	}
}

Spin& nthSpin(SpinSet& spins, int s){
	return spins.tab[s];
}

double meanField(SpinSet& spins){
	int suma = 0;
	double srednia;
	for (int i = 0; i < spins.current; i++){
		if (spins.tab[i].orientation == UP)
			suma++;
		else
			suma--;
	}

	return (double)suma / spins.current;
}

void cleanSet(SpinSet& spins){
	for ( unsigned  s = 0, smax = nSpins(spins); s < smax; ++s ) {
    		Spin& spin = nthSpin(spins, s);
		delete[] spin.sasiednie;
	}

	delete[] spins.tab;
	spins.current = 0;
}

void dodajSasiednie(SpinSet& spins){
	for ( unsigned  s = 0, smax = nSpins(spins); s < smax; ++s ) {
    		Spin& spin1 = nthSpin(spins, s);
		int i = 0;

			for ( unsigned  t = 0, tmax = nSpins(spins); t < tmax; ++t ) {
    				Spin& spin2 = nthSpin(spins, t);

					if ((spin1.x == spin2.x && abs(spin1.y - spin2.y) == 1) ||
					(spin1.y == spin2.y && abs(spin1.x - spin2.x) == 1)){
						spin1.sasiednie[i] = &spin2;
						i++;
					}
			}
	}
}

int hamiltonian(SpinSet& spins){
	int ham = 0;

	int wartoscSpinu, sumaSasiednich;

	for ( unsigned  s = 0, smax = nSpins(spins); s < smax; ++s ) {
    		Spin& spin1 = nthSpin(spins, s);
		wartoscSpinu = spin1.orientation == UP ? 1: -1;
		sumaSasiednich = 0;

			for (int i = 0; i < 4; i++)
				if (Spin *spin2 = spin1.sasiednie[i])
					sumaSasiednich += spin2->orientation == UP ? 1: -1;

		ham += -spins.J*wartoscSpinu*sumaSasiednich;
	}

	return ham;
}

void ferro(SpinSet& spins){
	spins.J = 1;
}

void antyferro(SpinSet& spins){
	spins.J = -1;
}

void setTemp(SpinSet& spins, double temp){
	spins.T = temp;
}

void ustawSpinyPoNIteracjach(SpinSet& spins, int NIteracji){
	srand(time(NULL));
	int ham1, ham2;
	double boltzmann, losowa;

	for (int i = 0; i < NIteracji; i++){
		ham1 = hamiltonian(spins);

		Spin *spin = &spins.tab[rand()%spins.current];
		flip(*spin);

		ham2 = hamiltonian(spins);
		boltzmann = exp((ham1 - ham2) / spins.T);
		losowa = rand() % 10001 / (double)10000;

		if (ham2 > ham1 && losowa > boltzmann) // losujemy liczbe i sprawdzamy z rozkladem Boltzmanna
			flip(*spin); // wracamy do polozenia poczatkowego
	}
}

void wyswietlSpiny(SpinSet& spins){
	Spin ***tablica = new Spin**[100];
	for (int i = 0; i < 100; i++)
		tablica[i] = new Spin*[100];

	for ( unsigned  s = 0, smax = nSpins(spins); s < smax; ++s ) {
    		Spin& spin = nthSpin(spins, s);
		tablica[(int)spin.x][(int)spin.y] = &spin;
	}

	int flagSpin = 0;
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 100; j++)
			if (Spin *spin = tablica[j][i]){
				flagSpin = 1;

				if (spin->orientation == UP)
					std::cout << '+';
				else
					std::cout << '-';
			}
		if (flagSpin){
			std::cout << std::endl;
			flagSpin = 0;
		}
	}

	for (int i = 0; i < 100; i++)
		delete[] tablica[i];
	delete[] tablica;
}
