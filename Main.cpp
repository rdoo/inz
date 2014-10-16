#include <iostream>
#include "PhysicsEngine.h"
#include "Algorithm.h"
#include <windows.h>
#include <GL/glut.h>
#include "Atom.h"
#include <gmp.h>
#include <math.h>
#include <time.h>

#include "Camera.h"

void displayAtom(int atomNumber);
void display();

PhysicsEngine engine;
Algorithm algo;
CCamera objCamera;

int numberOfAtoms = 15;
Atom* atomTable = new Atom[numberOfAtoms];

double powe = 100000000000;

void displayAtom(int atomNumber){
	//glLoadIdentity();
	glColor3f(224 / 255.0f, 224 / 255.0f, 100 * atomNumber / 255.0f);
	glPushMatrix();

	glTranslatef(atomTable[atomNumber].position().x(), atomTable[atomNumber].position().y(), atomTable[atomNumber].position().z());
	glutWireSphere(.0000000001*1, 10, 10);
	glPopMatrix();
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(powe, powe, powe);

	gluLookAt(objCamera.mPos.x(),  objCamera.mPos.y(),  objCamera.mPos.z(),
			  objCamera.mView.x(), objCamera.mView.y(), objCamera.mView.z(),
			  objCamera.mUp.x(),   objCamera.mUp.y(),   objCamera.mUp.z());

	Draw_Grid();

	Keyboard_Input();
	if (objCamera.isDragging)
	objCamera.Mouse_Move(640,640);

	for (int i = 0; i < numberOfAtoms; i++){
		//glPushMatrix();
		displayAtom(i);
		//glPopMatrix();
	}

	glFlush();  // Render now
}

void update(int value) {
	engine.step(atomTable, numberOfAtoms);
	//algo.step(atomTable, numberOfAtoms);
	std::cout << atomTable[0].position().toString() << "\t\t" << atomTable[1].position().toString() << std::endl;
	//std::cout << objCamera.isDragging << "\t\t" << std::endl;
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
	//gluPerspective(45.0f, aspect, 0.0f, 1000.f);

	glOrtho(-100, 100, -100, 100, -100, 100);


	//glMatrixMode(GL_MODELVIEW);

	//glLoadIdentity();

	// Set the viewport to cover the new window
	//glViewport(0, 0, width, height);

}

void Keyboard_Input()
{
	if((GetKeyState(VK_UP) & 0x80) || (GetKeyState('W') & 0x80))
	{
		objCamera.Move_Camera( CAMERASPEED);
	}

	if((GetKeyState(VK_DOWN) & 0x80) || (GetKeyState('S') & 0x80))
	{
		objCamera.Move_Camera(-CAMERASPEED);
	}

	if((GetKeyState(VK_LEFT) & 0x80) || (GetKeyState('A') & 0x80))
	{
		objCamera.Strafe_Camera(-CAMERASPEED);
	}

	if((GetKeyState(VK_RIGHT) & 0x80) || (GetKeyState('D') & 0x80))
	{
		objCamera.Strafe_Camera( CAMERASPEED);
	}
}


void Draw_Grid()
{
/*
	for(float i = -500; i <= 500; i += 5)
	{
		glBegin(GL_LINES);
			glColor3ub(150, 190, 150);
			glVertex3f(-500, 0, i);
			glVertex3f(500, 0, i);
			glVertex3f(i, 0,-500);
			glVertex3f(i, 0, 500);
		glEnd();
	}
	*/
}

void Mouse_Button(int button, int state, int x, int y){
	int mid_x = 640  >> 1;
	int mid_y = 640 >> 1;
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			SetCursorPos(mid_x, mid_y);
			objCamera.isDragging = 1; // start dragging
			//GetCursorPos(&objCamera.mousePos); // save x where button first pressed
		}
		else  { /* (state = GLUT_UP) */
			//angle += deltaAngle; // update camera turning angle
			objCamera.isDragging = 0; // no longer dragging
		}
	}
}

int main(int argc, char** argv) {
	std::cout << "Hello inzynierko!" << std::endl;
	srand(time(NULL));
	/*
		Atom atom1;
		atom1.mass(2e-26);
		atom1.position(0, 0, -1e-9);
		atom1.velocity(0.0, 0.0, 0.);

		Atom atom2;
		atom2.mass(2e-26);
		atom2.position(0, 0, -0.01);
		atom2.velocity(0., 0., 0.);

		Atom atom3;
		atom3.mass(2e-26);
		atom3.position(0., -0.01, -1e-9);
		atom3.velocity(0.0, 0.0, 0.);

		Atom atom4;
		atom4.mass(2e-26);
		atom4.position(-1, -0.5, -1e-9);
		atom4.velocity(0.0, 0.0, 0.);

		Atom atom5;
		atom5.mass(2e-26);
		atom5.position(-10, 2e-10L, -1e-9);
		atom5.velocity(0.0, 0.0, 0.);
	*/
	Atom atom1;
	atom1.mass(2e-26);
	atom1.position(-1e-10L, 0, 0);
	atom1.velocity(0.0, 0.0, 0.);

	Atom atom2;
	atom2.mass(2e-26);
	atom2.position(1e-10L, 0, -1e-10);
	atom2.velocity(0., 0., 0.);

	Atom atom3;
	atom3.mass(2e-26);
	atom3.position(0., -3e-10L, -1e-10);
	atom3.velocity(0.0, 0.0, 0.);

	Atom atom4;
	atom4.mass(2e-26);
	atom4.position(-3e-10L, -3e-10L, 0);
	atom4.velocity(0.0, 0.0, 0.);

	Atom atom5;
	atom5.mass(2e-26);
	atom5.position(2e-10L, 0, 1e-10);
	atom5.velocity(0.0, 0.0, 0.);

	Atom atom6;
	atom6.mass(2e-26);
	atom6.position(1e-10L, -2e-10L, 1e-10);
	atom6.velocity(0.0, 0.0, 0.);

	Atom atom7;
	atom7.mass(2e-26);
	atom7.position(1.e-10, 1e-10L, 0.);
	atom7.velocity(0.0, 0.0, 0.);

	Atom atom8;
	atom8.mass(2e-26);
	atom8.position(2e-10L, -2e-10L, 0);
	atom8.velocity(0.0, 0.0, 0.);

	Atom atom9;
	atom9.mass(2e-26);
	atom9.position(1e-10L, -2e-10L, 0);
	atom9.velocity(0.0, 0.0, 0.);

	Atom atom10;
	atom10.mass(2e-26);
	atom10.position(2e-10L, -2e-10L, -1e-10L);
	atom10.velocity(0.0, 0.0, 0.);

	Atom atom11;
	atom11.mass(2e-26);
	atom11.position(1e-10L, 1e-10L, 0);
	atom11.velocity(0.0, 0.0, 0.);

	Atom atom12;
	atom12.mass(2e-26);
	atom12.position(1e-10L, 2e-10L, -1e-10L);
	atom12.velocity(0.0, 0.0, 0.);

	Atom atom13;
	atom13.mass(2e-26);
	atom13.position(1e-10L, -1e-10L, 1e-10L);
	atom13.velocity(0.0, 0.0, 0.);

	Atom atom14;
	atom14.mass(2e-26);
	atom14.position(-1e-10L, -1e-10L, -1e-10L);
	atom14.velocity(0.0, 0.0, 0.);

	Atom atom15;
	atom15.mass(2e-26);
	atom15.position(-1e-10L, 1e-10L, 1e-10L);
	atom15.velocity(0.0, 0.0, 0.);


	atomTable[0] = atom1;
	atomTable[1] = atom2;
	atomTable[2] = atom3;
	atomTable[3] = atom4;
	atomTable[4] = atom5;
	atomTable[5] = atom6;
	atomTable[6] = atom7;
	atomTable[7] = atom8;
	atomTable[8] = atom9;
	atomTable[9] = atom10;
	atomTable[10] = atom11;
	atomTable[11] = atom12;
	atomTable[12] = atom13;
	atomTable[13] = atom14;
	atomTable[14] = atom15;

	glutInit(&argc, argv);                 // Initialize GLUT

	//glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(640, 640);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner

	glutCreateWindow("Klaster atomowy"); // Create a window with the given title
	//engine.timeStep(60 * 60 * 24*10);
	engine.timeStep(0.0000000000000000000000001L);

	objCamera.Position_Camera(0, 0, 0,	0, 0, -1,   0, 0.1, 0);

	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutReshapeFunc(reshape);
	glutTimerFunc(25, update, 0);

	glutMouseFunc(Mouse_Button); // process mouse button push/release
/*	glutMotionFunc(mouseMove); // process mouse dragging motion
	glutKeyboardFunc(processNormalKeys); // process standard key clicks
	glutSpecialFunc(pressSpecialKey); // process special key pressed
						// Warning: Nonstandard function! Delete if desired.
	glutSpecialUpFunc(releaseSpecialKey); // process special key release
*/
	glutMainLoop();           // Enter the infinitely event-processing loop

}
