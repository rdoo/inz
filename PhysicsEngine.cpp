#include <cmath>
#include <iostream>
#include <gmp.h>
#include "PhysicsEngine.h"

void PhysicsEngine::timeStep(long double dt){
	ts = dt;
}

void PhysicsEngine::step(Atom* tab, int n){
	Vector force;
	Vector len;
	for (int i = 0; i < n; i++){
		force.setX(0.);
		force.setY(0.);
		force.setZ(0.);
		for (int j = 0; j < n; j++)
			if (&tab[i] != &tab[j]){
				len = gravity(tab[j], tab[i]);
				force.setX(force.x() + len.x());
				force.setY(force.y() + len.y());
				force.setZ(force.z() + len.z());
				std::cout << "force: " << force.toString() << std::endl;
			}
		step(tab[i], force);
	}
}

void PhysicsEngine::step(Atom& p, Vector& f){
	totalTime += ts;

	p.position().setX(p.position().x() + p.velocity().x() * ts + f.x() / p.mass() * ts * ts / 2.); // x2 = x1 + Vx*t + Fx/m*t^2/2 (a = F/m)
	p.position().setY(p.position().y() + p.velocity().y() * ts + f.y() / p.mass() * ts * ts / 2.); // y2 = y1 + Vy*t + Fy/m*t^2/2 (a = F/m)
	p.position().setZ(p.position().z() + p.velocity().z() * ts + f.z() / p.mass() * ts * ts / 2.); // z2 = z1 + Vz*t + Fz/m*t^2/2 (a = F/m)
	p.velocity().setX(p.velocity().x() + f.x() / p.mass() * ts); // Vx2 = Vx1 + Fx/m*t (a = F/m)
	p.velocity().setY(p.velocity().y() + f.y() / p.mass() * ts); // Vy2 = Vy1 + Fy/m*t (a = F/m)
	p.velocity().setZ(p.velocity().z() + f.z() / p.mass() * ts); // Vz2 = Vz1 + Fz/m*t (a = F/m)
}

long double PhysicsEngine::timeFromBeginning(){
	return totalTime;
}

Vector PhysicsEngine::gravity(Atom& p1, Atom& p2){
	Vector grav;
	long double r = sqrt(pow(p1.position().x() - p2.position().x(), 2) + pow(p1.position().y() - p2.position().y(), 2) + pow(p1.position().z() - p2.position().z(), 2)); // dlugosc wektora laczacego punkty

	grav.setX(G * p1.mass() * p2.mass() * (p1.position().x() - p2.position().x()) / r / r / r); // sila w polu grawitacyjnym
	grav.setY(G * p1.mass() * p2.mass() * (p1.position().y() - p2.position().y()) / r / r / r);
	grav.setZ(G * p1.mass() * p2.mass() * (p1.position().z() - p2.position().z()) / r / r / r);

	return grav;
}

Vector PhysicsEngine::lennarda(Atom& p1, Atom& p2){
	Vector lenn;
	long double sigma = .1;
	long double r = sqrt(pow(p1.position().x() - p2.position().x(), 2) + pow(p1.position().y() - p2.position().y(), 2) + pow(p1.position().z() - p2.position().z(), 2)); // dlugosc wektora laczacego punkty

	std::cout << pow(p1.position().x() - p2.position().x(), 2) << std::endl;
	std::cout << pow(p1.position().y() - p2.position().y(), 2) << std::endl;
	std::cout << pow(p1.position().z() - p2.position().z(), 2) << std::endl;
	std::cout << r << std::endl;

	lenn.setX(4 * p1.mass() * sigma * sigma * (pow(sigma / r , 12) - pow(sigma / r , 6)) * (p1.position().x() - p2.position().x()) / r / r); // sila w polu grawitacyjnym
	lenn.setY(4 * p1.mass() * sigma * sigma * (pow(sigma / r , 12) - pow(sigma / r , 6)) * (p1.position().y() - p2.position().y()) / r / r);
	lenn.setZ(4 * p1.mass() * sigma * sigma * (pow(sigma / r , 12) - pow(sigma / r , 6)) * (p1.position().z() - p2.position().z()) / r / r);
	//grav.setY(G * p1.mass() * p2.mass() * (p1.position().y() - p2.position().y()) / r / r / r);
	//grav.setZ(G * p1.mass() * p2.mass() * (p1.position().z() - p2.position().z()) / r / r / r);

	return lenn;
}
