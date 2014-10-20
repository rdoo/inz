#include "Main.h"

PhysicsEngine physxEngine(0.0000000000000000000000001L);
AlgorithmEngine algoEngine;

int width = 640;
int height = 640;

Camera camera(width, height);

int numberOfAtoms = 50;
Atom* atomTable = new Atom[numberOfAtoms];

double powe = 100000000000;
int m_programState = 0;

int main(int argc, char** argv) {
	std::cout << "Hello inzynierko!" << std::endl;
	srand(time(NULL));

	generateAtoms(atomTable, numberOfAtoms, 6e-10L, 2e-26);

	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(width, height); // Set the window's initial width & height
	glutCreateWindow("Klaster atomowy"); // Create a window with the given title

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
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(powe, powe, powe);

	gluLookAt(camera.mPos.x(), camera.mPos.y(), camera.mPos.z(),
			camera.mView.x(), camera.mView.y(), camera.mView.z(),
			camera.mUp.x(), camera.mUp.y(), camera.mUp.z());

	for (int i = 0; i < numberOfAtoms; i++) {
		displayAtom(i);
	}

	glFlush();  // Render now
}

void displayAtom(int atomNumber) {
	//glLoadIdentity();
	glColor3f(224 / 255.0f, 224 / 255.0f, 200 / 255.0f);
	glPushMatrix();
	glTranslatef(atomTable[atomNumber].position().x(),
			atomTable[atomNumber].position().y(),
			atomTable[atomNumber].position().z());
	glutWireSphere(.0000000001 * 0.7, 10, 10);
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

	glOrtho(-100 * aspect, 100 * aspect, -100, 100, -100, 100);

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
	camera.mouseButton(button, state, x, y);
}

void handleKeyboard() {
	if ((GetKeyState(VK_UP) & 0x80) || (GetKeyState('W') & 0x80)) {
		camera.moveCamera(CAMERASPEED);
	}

	if ((GetKeyState(VK_DOWN) & 0x80) || (GetKeyState('S') & 0x80)) {
		camera.moveCamera(-CAMERASPEED);
	}

	if ((GetKeyState(VK_LEFT) & 0x80) || (GetKeyState('A') & 0x80)) {
		camera.strafeCamera(-CAMERASPEED);
	}

	if ((GetKeyState(VK_RIGHT) & 0x80) || (GetKeyState('D') & 0x80)) {
		camera.strafeCamera(CAMERASPEED);
	}
}

void processMenuEvents(int programState) {
	m_programState = programState;
}
