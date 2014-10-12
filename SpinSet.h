#ifndef SpinSet_h
#define SpinSet_h

//#include "Spin.h"

/**
 * tab to tablica spinow
 * current to obecna ilosc spinow w tablicy
 * max to maksymalna ilosc spinow jaka moze byc przechowana w tablicy
 * J okresla czy oddzialywanie w tym zestawie spinow ma byc ferromagnetyczne (J>0) lub antyferromagnetyczne (J<0)
 * T to temperatura w jakiej utrzymywany jest ten uklad spinow
 */
struct SpinSet {  
	Spin *tab;
	
	int current = 0;
	int max;

	double J = 1;
	double T = 0;
};

/**
 * @brief funkcja alokujaca odpowiednia ilosc pamieci do tablicy spinow przechowywanej w strukturze spins
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow oraz informacje na temat jej rozmiaru otrzymane z drugiego parametru funkcji
 */
void prepareSet(SpinSet& spins, int rozmiar);

/**
 * @brief funkcja zwracajaca ilosc spinow przechowywanej w strukturze spins
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow
 * @return zwraca ilosc spinow przechowywanej w strukturze spins
 */
int nSpins(SpinSet& spins);

/**
 * @brief funkcja dodajaca spin do tablicy w strukturze spins
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow, a spin to dodawany spin
 */
void add(SpinSet& spins, Spin spin);

/**
 * @brief funkcja zwracajaca referencje do spinu w tablicy o numerze komorki s
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow, a s to numer komorki w tej tablicy
 * @return zwraca referencje do spinu o numerze s
 */
Spin& nthSpin(SpinSet& spins, int s);

/**
 * @brief funkcja dealokujaca pamiec po tablicy spinow w strukturze spins
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow
 */
void cleanSet(SpinSet& spins);

/**
 * @brief funkcja zwracajaca srednia wartosc spinu z tablicy spinow w strukturze spins
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow
 * @return zwraca srednia wartosc spinu z tablicy spinow
 */
double meanField(SpinSet& spins);

/**
 * @brief funkcja ktora znajduje spiny sasiednie dla kazdego spinu ze struktury spins i dodaje ich wskazniki do tablicy sasiednie
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow
 */
void dodajSasiednie(SpinSet& spins);

/**
 * @brief funkcja obliczajaca wartosc hamiltonianu dla zestawu spinow spins
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow
 * @return zwraca wartosc hamiltonianu dla zestawu spinow spins
 */
int hamiltonian(SpinSet& spins);

/**
 * @brief funkcja ustawia oddzialywanie ferromagnetyczne (J=1) dla struktury spins
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow
 */
void ferro(SpinSet& spins);

/**
 * @brief funkcja ustawia oddzialywanie antyferromagnetyczne (J=-1) dla struktury spins
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow
 */
void antyferro(SpinSet& spins);

/**
 * @brief funkcja ustawia temperature dla struktury spins
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow, a temp to ustawiana temperatura
 */
void setTemp(SpinSet& spins, double temp);

/**
 * @brief funkcja przeprowadzajaca symulacje czyli zmienianie spinow i akceptacja tej zmiany
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow, a NIteracji to liczba iteracji
 */
void ustawSpinyPoNIteracjach(SpinSet& spins, int NIteracji);

/**
 * @brief funkcja wyswietlajaca spiny na ekran ze struktury spins
 * @arg spins to struktura w ktorej przechowywana jest tablica spinow
 */
void wyswietlSpiny(SpinSet& spins);

#endif
