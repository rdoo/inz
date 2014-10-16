#include "Atom.h"
#include "Camera.h"
#include "PhysicsEngine.h"
#include "AlgorithmEngine.h"
#include <iostream>
//#include <windows.h>
#include <GL/glut.h>
#include <gmp.h>
#include <ctime>

PhysicsEngine physxEngine(0.0000000000000000000000001L);
AlgorithmEngine algoEngine;
Camera camera;

int numberOfAtoms = 25;
Atom* atomTable = new Atom[numberOfAtoms];

double powe = 100000000000;

void Keyboard_Input()
{
	if((GetKeyState(VK_UP) & 0x80) || (GetKeyState('W') & 0x80))
	{
		camera.moveCamera(CAMERASPEED);
	}

	if((GetKeyState(VK_DOWN) & 0x80) || (GetKeyState('S') & 0x80))
	{
		camera.moveCamera(-CAMERASPEED);
	}

	if((GetKeyState(VK_LEFT) & 0x80) || (GetKeyState('A') & 0x80))
	{
		camera.strafeCamera(-CAMERASPEED);
	}

	if((GetKeyState(VK_RIGHT) & 0x80) || (GetKeyState('D') & 0x80))
	{
		camera.strafeCamera(CAMERASPEED);
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

void displayAtom(int atomNumber){
	//glLoadIdentity();
	glColor3f(224 / 255.0f, 224 / 255.0f, 200 / 255.0f);
	glPushMatrix();

	glTranslatef(atomTable[atomNumber].position().x(), atomTable[atomNumber].position().y(), atomTable[atomNumber].position().z());
	glutWireSphere(.0000000001*0.7, 10, 10);
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

	gluLookAt(camera.mPos.x(),  camera.mPos.y(),  camera.mPos.z(),
			  camera.mView.x(), camera.mView.y(), camera.mView.z(),
			  camera.mUp.x(),   camera.mUp.y(),   camera.mUp.z());

	Draw_Grid();

	Keyboard_Input();
	if (camera.isDragging)
	camera.mouseMove(640,640);

	for (int i = 0; i < numberOfAtoms; i++){
		//glPushMatrix();
		displayAtom(i);
		//glPopMatrix();
	}

	glFlush();  // Render now
}

void update(int value) {
	//engine.step(atomTable, numberOfAtoms);
	algoEngine.step(atomTable, numberOfAtoms);
	std::cout << atomTable[0].position() << "\t\t" << atomTable[1].position() << std::endl;
	//std::cout << objCamera.isDragging << "\t\t" << std::endl;
	glutPostRedisplay();
	glutTimerFunc(15, update, 0);
}

void reshape(GLsizei width, GLsizei height) {
	// Compute aspect ratio of the new window
	if (height == 0)
		height = 1;                // To prevent divide by 0

	GLfloat aspect = (GLfloat) width / (GLfloat) height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset

	glOrtho(-100 * aspect, 100 * aspect, -100, 100, -100, 100);

}

void Mouse_Button(int button, int state, int x, int y){
	int mid_x = 640  >> 1;
	int mid_y = 640 >> 1;
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			SetCursorPos(mid_x, mid_y);
			camera.isDragging = 1; // start dragging
			//GetCursorPos(&objCamera.mousePos); // save x where button first pressed
		}
		else  { /* (state = GLUT_UP) */
			//angle += deltaAngle; // update camera turning angle
			camera.isDragging = 0; // no longer dragging
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

	Atom atom16;
	atom16.mass(2e-26);
	atom16.position(-3e-10L, 1e-10L, 1e-10L);
	atom16.velocity(0.0, 0.0, 0.);

	Atom atom17;
	atom17.mass(2e-26);
	atom17.position(-1e-10L, 3e-10L, 1e-10L);
	atom17.velocity(0.0, 0.0, 0.);

	Atom atom18;
	atom18.mass(2e-26);
	atom18.position(-1e-10L, 1e-10L, 2e-10L);
	atom18.velocity(0.0, 0.0, 0.);

	Atom atom19;
	atom19.mass(2e-26);
	atom19.position(-1e-10L, -3e-10L, -1e-10L);
	atom19.velocity(0.0, 0.0, 0.);

	Atom atom20;
	atom20.mass(2e-26);
	atom20.position(3e-10L, 1e-10L, -2e-10L);
	atom20.velocity(0.0, 0.0, 0.);

	Atom atom21;
	atom21.mass(2e-26);
	atom21.position(-1e-10L, -2e-10L, -1e-10L);
	atom21.velocity(0.0, 0.0, 0.);

	Atom atom22;
	atom22.mass(2e-26);
	atom22.position(-1e-10L, -1e-10L, -1e-10L);
	atom22.velocity(0.0, 0.0, 0.);

	Atom atom23;
	atom23.mass(2e-26);
	atom23.position(-1e-10L, 1e-10L, 2e-10L);
	atom23.velocity(0.0, 0.0, 0.);

	Atom atom24;
	atom24.mass(2e-26);
	atom24.position(1e-10L, -1e-10L, -2e-10L);
	atom24.velocity(0.0, 0.0, 0.);

	Atom atom25;
	atom25.mass(2e-26);
	atom25.position(3e-10L, 2e-10L, 1e-10L);
	atom25.velocity(0.0, 0.0, 0.);


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
	atomTable[15] = atom16;
	atomTable[16] = atom17;
	atomTable[17] = atom18;
	atomTable[18] = atom19;
	atomTable[19] = atom20;
	atomTable[20] = atom21;
	atomTable[21] = atom22;
	atomTable[22] = atom23;
	atomTable[23] = atom24;
	atomTable[24] = atom25;

	glutInit(&argc, argv);                 // Initialize GLUT

	//glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(640, 640);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner

	glutCreateWindow("Klaster atomowy"); // Create a window with the given title
	//engine.timeStep(60 * 60 * 24*10);

	camera.positionCamera(0, 0, 0,	0, 0, -1,   0, 0.1, 0);

	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutReshapeFunc(reshape);
	glutTimerFunc(15, update, 0);

	glutMouseFunc(Mouse_Button); // process mouse button push/release
/*	glutMotionFunc(mouseMove); // process mouse dragging motion
	glutKeyboardFunc(processNormalKeys); // process standard key clicks
	glutSpecialFunc(pressSpecialKey); // process special key pressed
						// Warning: Nonstandard function! Delete if desired.
	glutSpecialUpFunc(releaseSpecialKey); // process special key release
*/
	glutMainLoop();           // Enter the infinitely event-processing loop

}
