#include <cmath>
#include <iostream>
#include "PhysicsEngine.h"

void PhysicsEngine::timeStep(double dt){
	ts = dt;
}

void PhysicsEngine::step(Point* tab, int n){
	Force force(0,0,0);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			if (&tab[i] != &tab[j]){
				force.setX(gravity(tab[j], tab[i]).x());
				force.setY(gravity(tab[j], tab[i]).y());
				force.setZ(gravity(tab[j], tab[i]).z());
			}
		step(tab[i], force);
	}
}

void PhysicsEngine::step(Point& p, Force& f){
	totalTime += ts;

	p.position().setX(p.position().x() + p.velocity().x() * ts + f.x() / p.mass() * ts * ts / 2.); // x2 = x1 + Vx*t + Fx/m*t^2/2 (a = F/m)
	p.position().setY(p.position().y() + p.velocity().y() * ts + f.y() / p.mass() * ts * ts / 2.); // y2 = y1 + Vy*t + Fy/m*t^2/2 (a = F/m)
	p.position().setZ(p.position().z() + p.velocity().z() * ts + f.z() / p.mass() * ts * ts / 2.); // z2 = z1 + Vz*t + Fz/m*t^2/2 (a = F/m)
	p.velocity().setX(p.velocity().x() + f.x() / p.mass() * ts); // Vx2 = Vx1 + Fx/m*t (a = F/m)
	p.velocity().setY(p.velocity().y() + f.y() / p.mass() * ts); // Vy2 = Vy1 + Fy/m*t (a = F/m)
	p.velocity().setZ(p.velocity().z() + f.z() / p.mass() * ts); // Vz2 = Vz1 + Fz/m*t (a = F/m)
}

double PhysicsEngine::timeFromBeginning(){
	return totalTime;
}

Force PhysicsEngine::gravity(Point& p1, Point& p2){
	Vector grav;
	double r = sqrt(pow(p1.position().x() - p2.position().x(), 2) + pow(p1.position().y() - p2.position().y(), 2) + pow(p1.position().z() - p2.position().z(), 2)); // dlugosc wektora laczacego punkty

	grav.setX(G * p1.mass() * p2.mass() * (p1.position().x() - p2.position().x()) / r / r / r); // sila w polu grawitacyjnym
	grav.setY(G * p1.mass() * p2.mass() * (p1.position().y() - p2.position().y()) / r / r / r);
	grav.setZ(G * p1.mass() * p2.mass() * (p1.position().z() - p2.position().z()) / r / r / r);

	return grav;
}
