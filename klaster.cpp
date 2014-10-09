#include <iostream>
#include "Point.h"
#include "PhysicsEngine.h"

int main() {
	std::cout << "Hello inzynierko!" << std::endl;

	PhysicsEngine engine2;
	engine2.timeStep(60 * 60 * 24);

	Point ziemia;
	ziemia.mass(5.97e24);
	ziemia.position(1.5e11, 0.);
	ziemia.velocity(0., 2.978e4);

	Point slonce;
	slonce.mass(1.99e30);
	slonce.position(0., 0.);
	slonce.velocity(0., 0.);

	int liczbaPunktow = 2;

	Point* tabela = new Point[liczbaPunktow];
	tabela[0] = ziemia;
	tabela[1] = slonce;

	for (int i = 0; i < 365; i++) {
		engine2.step(tabela, liczbaPunktow);
		std::cout << tabela[0].position().x() << " " << tabela[0].position().y()
				<< " " << tabela[1].position().x() << " "
				<< tabela[1].position().y() << std::endl;
	}
}
