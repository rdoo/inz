#include <iostream>
#include "PhysicsEngine.h"
#include <windows.h>
#include <GL/glut.h>
#include "Atom.h"

PhysicsEngine engine;

int numberOfAtoms = 3;
Atom* atomTable = new Atom[numberOfAtoms];

void displayAtom(int atomNumber){
	glLoadIdentity();
	glTranslatef(atomTable[atomNumber].position().x(), atomTable[atomNumber].position().y(), atomTable[atomNumber].position().z());
	glColor3f(224 / 255.0f, 224 / 255.0f, 224 / 255.0f);
	glutWireSphere(50, 10, 10);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (int i = 0; i < numberOfAtoms; i++){
		displayAtom(i);
	}

	glFlush();  // Render now
}

void update(int value) {
	engine.step(atomTable, numberOfAtoms);
	std::cout << atomTable[0].position().toString() << "\t\t" << atomTable[1].position().toString() << std::endl;
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

void reshape(GLsizei width, GLsizei height) { // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	if (height == 0)
		height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat) width / (GLfloat) height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 10000.0f);
}

int main(int argc, char** argv) {
	std::cout << "Hello inzynierko!" << std::endl;
/*
	Atom atom1;
	atom1.mass(10);
	atom1.position(1e2, 1e2, -1700);
	atom1.velocity(-0.000005, 0.000005, 0.);

	Atom atom2;
	atom2.mass(2e3);
	atom2.position(-1e2, -1e2, -2000);
	atom2.velocity(0., 0., 0.);

	Atom atom3;
	atom3.mass(10);
	atom3.position(-1e2, -1e2, -2300);
	atom3.velocity(-0.000005, -0.000005, 0.);
*/

	Atom atom1;
	atom1.mass(1e-30);
	atom1.position(0, 0, -1);
	atom1.velocity(0.0, 0.0, 0.);

	Atom atom2;
	atom2.mass(1e-30);
	atom2.position(1, 1, -1.1);
	atom2.velocity(0., 0., 0.);

	atomTable[0] = atom1;
	atomTable[1] = atom2;
	//atomTable[2] = atom3;

	glutInit(&argc, argv);                 // Initialize GLUT

	//glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(640, 640);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner

	glutCreateWindow("Klaster atomowy"); // Create a window with the given title
	//engine.timeStep(60 * 60 * 24*10);
	engine.timeStep(0.0001);
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutReshapeFunc(reshape);
	glutTimerFunc(25, update, 0);

	glutMainLoop();           // Enter the infinitely event-processing loop

}
