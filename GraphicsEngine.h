#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "Camera.h"
#include <GL/glut.h>

class GraphicsEngine {
	Camera camera;
	int m_enablePhysx = 0;

public:
	void initialize(int argc, char** argv, int width, int height);
	void createMenu();
	void display();
	void displayAtom(int atomNumber);
	void reshape(int width, int height);
	void update(int value);
	void processMenuEvents(int enablePhysx);
	void keyboardInput();
};

#endif
