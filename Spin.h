#ifndef Spin_h
#define Spin_h

typedef float position_t;
typedef bool orientation_t;

static const orientation_t UP = true; 
static const orientation_t DOWN = !UP; 



struct Spin {  
  orientation_t orientation;
  position_t x;
  position_t y;
  Spin **sasiednie; // jest to tablica wskaznikow to spinow sasiadujacych z tym spinem
};

/**
 * @brief funkcja odwracajaca orientacje spinu
 * @arg spin to struktura zawierajaca informacje o danym spinie
 */
void flip(Spin& spin);

/**
 * @brief funkcja ustawiajaca orientacje spinu na UP
 * @arg spin to struktura zawierajaca informacje o danym spinie
 */
void up(Spin& spin);

/**
 * @brief funkcja ustawiajaca orientacje spinu na DOWN
 * @arg spin to struktura zawierajaca informacje o danym spinie
 */
void down(Spin& spin);

/**
 * @brief funkcja tworzaca spin
 * @arg orientation_t to orientacja spinu, a x i y to wspolrzedne jego polozenia
 * @return zwraca stworzony spin
 */
Spin makeSpin(orientation_t o, position_t x, position_t y);

#endif
