#include "Main.h"

PhysicsEngine physxEngine(0.00000000000000001L);
AlgorithmEngine algoEngine;

int width = 640;
int height = 640;

Camera camera(width, height);

int numberOfSteps = 100;
int numberOfAtoms = 5;
Atom* atomTable = new Atom[numberOfAtoms];
long double diameter = 6e-10L;
long double atomMass = 2e-26; // Al TODO: poprawic

double staticZoom = 200000000000;
double dynamicZoom = 1;

enum programState {
	pause,
	algorithm,
	physics,
	reset,
	a2 = 20,
	a4,
	a10,
	a20,
	a50,
	a100,
	s1 = 30,
	s5,
	s10,
	s30,
	s50,
	s100,
	s1000
};

programState state = pause;

int main(int argc, char** argv) {
	std::cout << "Hello inzynierko!" << std::endl;
	srand(time(NULL));

	generateAtoms(atomTable, numberOfAtoms, diameter, atomMass);

	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(width, height); // Set the window's initial width & height
	glutCreateWindow("Klaster atomowy"); // Create a window with the given title

	float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float mat_shininess[] = { 50.0 };
	float light_position[] = { 1., 1., 1., 0.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutReshapeFunc(reshape);
	glutTimerFunc(1, update, 0);
	glutMouseFunc(handleMouseButton); // process mouse button push/release

	int atomMenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("2", 20);
	glutAddMenuEntry("4", 21);
	glutAddMenuEntry("10", 22);
	glutAddMenuEntry("20", 23);
	glutAddMenuEntry("50", 24);
	glutAddMenuEntry("100", 25);

	int stepMenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("1", 30);
	glutAddMenuEntry("5", 31);
	glutAddMenuEntry("10", 32);
	glutAddMenuEntry("30", 33);
	glutAddMenuEntry("50", 34);
	glutAddMenuEntry("100", 35);
	glutAddMenuEntry("1000", 36);

	glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Pause (Space Bar)", 0);
	glutAddMenuEntry("Algorithm Engine (Enter)", 1);
	glutAddMenuEntry("Physics Engine", 2);
	glutAddMenuEntry("Reset", 3);
	glutAddSubMenu("Number of atoms", atomMenu);
	glutAddSubMenu("Number of steps per frame", stepMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();           // Enter the infinitely event-processing loop
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glScalef(dynamicZoom, dynamicZoom, dynamicZoom);

	gluLookAt(camera.mPos.x(), camera.mPos.y(), camera.mPos.z(),
			camera.mView.x(), camera.mView.y(), camera.mView.z(),
			camera.mUp.x(), camera.mUp.y(), camera.mUp.z());

	for (int i = 0; i < numberOfAtoms; i++) {
		displayAtom(i);
	}

	std::ostringstream energyStr, stepStr, lastStr;
	energyStr << "Total energy: " << (double) algoEngine.currentEnergy
			<< " J = " << (double) algoEngine.currentEnergy / elementaryCharge
			<< " eV";
	stepStr << "Step number: " << algoEngine.steps;
	lastStr << "Last change at step: " << algoEngine.lastChangeStep;

	writeString(energyStr.str(), -1., .95);
	writeString(stepStr.str(), -1., .90);
	writeString(lastStr.str(), -1., .85);

	glFlush();  // Render now

}

void displayAtom(int atomNumber) {
	glColor3f(224 / 255.0f, 224 / 255.0f, 200 / 255.0f);
	glPushMatrix();
	glTranslatef(atomTable[atomNumber].position().x(),
			atomTable[atomNumber].position().y(),
			atomTable[atomNumber].position().z());
	glutSolidSphere(.0000000001 * 0.5, 10, 10);
	glPopMatrix();
}

void reshape(int width, int height) {
	// Compute aspect ratio of the new window
	if (height == 0)
		height = 1;                // To prevent divide by 0

	float aspect = (float) width / (float) height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	glOrtho(-100 * aspect, 100 * aspect, -100, 100, -400, 400);
	glScalef(staticZoom, staticZoom, staticZoom);

	camera.setScreenSize(width, height);
}

void update(int value) {
	handleKeyboard();
	camera.mouseMove();

	switch (state) {
	case pause:
		break;
	case algorithm:
		for (int i = 0; i < numberOfSteps; i++) { // TODO: dodac reset velocities
			algoEngine.step(atomTable, numberOfAtoms);
		}
		break;
	case physics:
		for (int i = 0; i < numberOfSteps; i++) {
			physxEngine.step(atomTable, numberOfAtoms);
		}
		break;
	case reset:
		generateAtoms(atomTable, numberOfAtoms, diameter, atomMass);
		algoEngine.currentEnergy = 0.;
		algoEngine.steps = 0;
		algoEngine.lastChangeStep = 0;
		state = pause;
		break;
	case a2:
		numberOfAtoms = 2;
		atomTable = new Atom[numberOfAtoms];
		state = reset;
		break;
	case a4:
		numberOfAtoms = 4;
		atomTable = new Atom[numberOfAtoms];
		state = reset;
		break;
	case a10:
		numberOfAtoms = 10;
		atomTable = new Atom[numberOfAtoms];
		state = reset;
		break;
	case a20:
		numberOfAtoms = 20;
		atomTable = new Atom[numberOfAtoms];
		state = reset;
		break;
	case a50:
		numberOfAtoms = 50;
		atomTable = new Atom[numberOfAtoms];
		state = reset;
		break;
	case a100:
		numberOfAtoms = 100;
		atomTable = new Atom[numberOfAtoms];
		state = reset;
		break;
	case s1:
		numberOfSteps = 1;
		state = pause;
		break;
	case s5:
		numberOfSteps = 5;
		state = pause;
		break;
	case s10:
		numberOfSteps = 10;
		state = pause;
		break;
	case s30:
		numberOfSteps = 30;
		state = pause;
		break;
	case s50:
		numberOfSteps = 50;
		state = pause;
		break;
	case s100:
		numberOfSteps = 100;
		state = pause;
		break;
	case s1000:
		numberOfSteps = 1000;
		state = pause;
		break;
	}

	//std::cout << atomTable[0].position() << "\t\t" << atomTable[1].position()
	//		<< std::endl;
	glutPostRedisplay();
	glutTimerFunc(1, update, 0);
}

void handleMouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			glutSetCursor(GLUT_CURSOR_NONE);
			SetCursorPos(camera.getMidX(), camera.getMidY());
			camera.isDragging = 1; // start dragging
		} else { /* (state = GLUT_UP) */
			glutSetCursor(GLUT_CURSOR_INHERIT);
			camera.isDragging = 0; // no longer dragging
		}
	} else if (button == 3) { // scroll up
		if (state == GLUT_DOWN) {
			dynamicZoom += 0.1;
		}
	} else if (button == 4) { // scroll down
		if (state == GLUT_DOWN) {
			dynamicZoom -= 0.1;
		}
	}
}

void handleKeyboard() {
	if ((GetKeyState(VK_UP) & 0x80) || (GetKeyState('W') & 0x80)) {
		camera.moveCamera(CAMERASPEED);
	} else if ((GetKeyState(VK_DOWN) & 0x80) || (GetKeyState('S') & 0x80)) {
		camera.moveCamera(-CAMERASPEED);
	} else if ((GetKeyState(VK_LEFT) & 0x80) || (GetKeyState('A') & 0x80)) {
		camera.strafeCamera(-CAMERASPEED);
	} else if ((GetKeyState(VK_RIGHT) & 0x80) || (GetKeyState('D') & 0x80)) {
		camera.strafeCamera(CAMERASPEED);
	} else if ((GetKeyState(VK_SPACE) & 0x80)) {
		state = pause;
	} else if ((GetKeyState(VK_RETURN) & 0x80)) {
		state = algorithm;
	}
}

void processMenuEvents(int progState) {
	state = static_cast<programState>(progState);
}

void writeString(std::string str, double x, double y) {
	//TEXT
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // save
	glLoadIdentity(); // and clear
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST); // also disable the depth test so renders on top
	glDisable(GL_LIGHTING);

	glRasterPos2f(x, y); // center of screen. (-1,0) is center left.
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	const char * p = str.c_str();
	do
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
	while (*(++p));

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST); // Turn depth testing back on

	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); // revert back to the matrix I had before.
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
