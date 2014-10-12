#include "Spin.h"

void flip(Spin& spin){
	spin.orientation = spin.orientation == UP ? DOWN : UP;
}

void up(Spin& spin){
	spin.orientation = UP;
}

void down(Spin& spin){
	spin.orientation = DOWN;
}

Spin makeSpin(orientation_t o, position_t x, position_t y){
	Spin spin;

	spin.orientation = o;
	spin.x = x;
	spin.y = y;
	spin.sasiednie = new Spin*[4];

	return spin;
}

