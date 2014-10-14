#include <iostream>
#include "PhysicsEngine.h"
#include <windows.h>
#include <GL/glut.h>
#include "Atom.h"
#include <gmp.h>
#include <math.h>

PhysicsEngine engine;

int numberOfAtoms = 5;
Atom* atomTable = new Atom[numberOfAtoms];


// Camera position
float x = 0.0, y = -5.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move

// Camera direction
float lx = 0.0, ly = 1.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts



void displayAtom(int atomNumber){
	//glLoadIdentity();
	glTranslatef(atomTable[atomNumber].position().x(), atomTable[atomNumber].position().y(), atomTable[atomNumber].position().z());
	glColor3f(224 / 255.0f, 224 / 255.0f, 100 * atomNumber / 255.0f);
	glutWireSphere(.0000000001*100000000, 10, 10);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
			x,      y,      1.0,
			x + lx, y + ly, 1.0,
			0.0,    0.0,    1.0);

	for (int i = 0; i < numberOfAtoms; i++){
		//glPushMatrix();
		displayAtom(i);
		//glPopMatrix();
	}

	glFlush();  // Render now
}

void update(int value) {
	if (deltaMove) { // update camera position
		x += deltaMove * lx * 0.1*10;
		y += deltaMove * ly * 0.1*10;
	}
	engine.step(atomTable, numberOfAtoms);
	//std::cout << atomTable[0].position().toString() << "\t\t" << atomTable[1].position().toString() << std::endl;
	std::cout << isDragging << "\t\t" << lx << std::endl;
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

void reshape(GLsizei width, GLsizei height) { // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	if (height == 0)
		height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat) width / (GLfloat) height;

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.0f, 1e-8f);
	glMatrixMode(GL_MODELVIEW);
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

}

void mouseMove(int x, int y)
{
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (x - xDragStart) * 0.005;

		// camera's direction is set to angle + deltaAngle
		lx = -sin(angle + deltaAngle);
		ly = cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = 1; // start dragging
			xDragStart = x; // save x where button first pressed
		}
		else  { /* (state = GLUT_UP) */
			angle += deltaAngle; // update camera turning angle
			isDragging = 0; // no longer dragging
		}
	}
}


void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == 27 || key == 'q' || key == 'Q') exit(0);
}

void pressSpecialKey(int key, int xx, int yy)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 1.0; break;
		case GLUT_KEY_DOWN : deltaMove = -1.0; break;
	}
}

void releaseSpecialKey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.0; break;
		case GLUT_KEY_DOWN : deltaMove = 0.0; break;
	}
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
	atom1.mass(2e-26);
	atom1.position(-2e-10L*0.5, 0, -1e-9);
	atom1.velocity(0.0, 0.0, 0.);

	Atom atom2;
	atom2.mass(2e-26);
	atom2.position(2e-10L*0.5, 0, -1e-9);
	atom2.velocity(0., 0., 0.);

	Atom atom3;
	atom3.mass(2e-26);
	atom3.position(0., -3e-10L, -1e-9);
	atom3.velocity(0.0, 0.0, 0.);

	Atom atom4;
	atom4.mass(2e-26);
	atom4.position(-3e-10L, -3e-10L, -1e-9);
	atom4.velocity(0.0, 0.0, 0.);

	Atom atom5;
	atom5.mass(2e-26);
	atom5.position(2e-10L, 2e-10L, -1e-9);
	atom5.velocity(0.0, 0.0, 0.);

	atomTable[0] = atom1;
	atomTable[1] = atom2;
	atomTable[2] = atom3;
	atomTable[3] = atom4;
	atomTable[4] = atom5;

	glutInit(&argc, argv);                 // Initialize GLUT

	//glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(640, 640);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner

	glutCreateWindow("Klaster atomowy"); // Create a window with the given title
	//engine.timeStep(60 * 60 * 24*10);
	engine.timeStep(0.0000000000000000000000001L);
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutReshapeFunc(reshape);
	glutTimerFunc(25, update, 0);

	glutMouseFunc(mouseButton); // process mouse button push/release
	glutMotionFunc(mouseMove); // process mouse dragging motion
	glutKeyboardFunc(processNormalKeys); // process standard key clicks
	glutSpecialFunc(pressSpecialKey); // process special key pressed
						// Warning: Nonstandard function! Delete if desired.
	glutSpecialUpFunc(releaseSpecialKey); // process special key release

	glutMainLoop();           // Enter the infinitely event-processing loop

}
