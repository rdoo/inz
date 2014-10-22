#include "Main.h"
#include <string>
#include <sstream>

PhysicsEngine physxEngine(0.0000000000000000000000001L);
AlgorithmEngine algoEngine;

int width = 640;
int height = 640;

Camera camera(width, height);

int numberOfAtoms = 50;
Atom* atomTable = new Atom[numberOfAtoms];

double staticZoom = 200000000000;
double dynamicZoom = 1;
int m_programState = 0;

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

	glRasterPos2f(-1, 0.95); // center of screen. (-1,0) is center left.
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

int main(int argc, char** argv) {
	std::cout << "Hello inzynierko!" << std::endl;
	srand(time(NULL));

	generateAtoms(atomTable, numberOfAtoms, 6e-10L, 2e-26);

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
	glEnable(GL_NORMALIZE);

	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutReshapeFunc(reshape);
	glutTimerFunc(15, update, 0);
	glutMouseFunc(handleMouseButton); // process mouse button push/release

	glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Stop", 0);
	glutAddMenuEntry("Algorithm Engine", 1);
	glutAddMenuEntry("Physics Engine", 2);
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

	std::ostringstream strs;
	strs << "Current energy: " << (double) algoEngine.currentEnergy
			<< " J    Steps#: " << algoEngine.steps
			<< "   Last change at step#: " << algoEngine.lastChangeStep;
	std::string str = strs.str();
	writeString(str, -1., .95);

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

	switch (m_programState) {
	case 0:
		break;
	case 1:
		algoEngine.step(atomTable, numberOfAtoms);
		break;
	case 2:
		physxEngine.step(atomTable, numberOfAtoms);
		break;
	}

	std::cout << atomTable[0].position() << "\t\t" << atomTable[1].position()
			<< std::endl;
	glutPostRedisplay();
	glutTimerFunc(15, update, 0);
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
			std::cout << "zoom: " << staticZoom << std::endl;
		}
	} else if (button == 4) { // scroll down
		if (state == GLUT_DOWN) {
			dynamicZoom -= 0.1;
			std::cout << "zoom: " << staticZoom << std::endl;
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
	}
}

void processMenuEvents(int programState) {
	m_programState = programState;
}
