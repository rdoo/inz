#include <cmath>
#include <iostream>
#include "PhysicsEngine.h"

void PhysicsEngine::timeStep(double dt){
	ts = dt;
}

void PhysicsEngine::step(Point* tab, int n){
	Force force;
	for (int i = 0; i < n; i++){
		force.setX(0.);
		force.setY(0.);
		for (int j = 0; j < n; j++)
			if (&tab[i] != &tab[j]){
				force.setX(force.x() + gravity(tab[j], tab[i]).x());
				force.setY(force.y() + gravity(tab[j], tab[i]).y());
			}
		step(tab[i], force);
	}
}

void PhysicsEngine::step(Point& p, Force& f){
	totalTime += ts;

	p.position().setX(p.position().x() + p.velocity().x() * ts + f.x() / p.mass() * ts * ts / 2.); // x2 = x1 + Vx*t + Fx/m*t^2/2 (a = F/m)
	p.position().setY(p.position().y() + p.velocity().y() * ts + f.y() / p.mass() * ts * ts / 2.); // y2 = y1 + Vy*t + Fy/m*t^2/2 (a = F/m)
	p.velocity().setX(p.velocity().x() + f.x() / p.mass() * ts); // Vx2 = Vx1 + Fx/m*t (a = F/m)
	p.velocity().setY(p.velocity().y() + f.y() / p.mass() * ts); // Vy2 = Vy1 + Fy/m*t (a = F/m)
}

double PhysicsEngine::timeFromBeginning(){
	return totalTime;
}

Force PhysicsEngine::gravity(Point& p1, Point& p2){
	Vector grav;
	double r = sqrt(pow(p1.position().x() - p2.position().x(), 2) + pow(p1.position().y() - p2.position().y(), 2)); // dlugosc wektora laczacego punkty

	grav.setX(G * p1.mass() * p2.mass() * (p1.position().x() - p2.position().x()) / r / r / r); // sila w polu grawitacyjnym
	grav.setY(G * p1.mass() * p2.mass() * (p1.position().y() - p2.position().y()) / r / r / r);
	
	return grav;
}