#ifndef MAIN_H
#define MAIN_H

#include "Atom.h"
#include "Camera.h"
#include "PhysicsEngine.h"
#include "AlgorithmEngine.h"
#include <iostream>
#include <GL/glut.h>
#include <gmp.h>
#include <ctime>
#include <sstream>

const double elementaryCharge = 1.602176565e-19;

void display();
void displayAtom(int atomNumber);
void reshape(int width, int height);
void update(int value);
void handleMouseButton(int button, int state, int x, int y);
void handleKeyboard();
void processMenuEvents(int programState);
void writeString(std::string str, double x, double y);

#endif
