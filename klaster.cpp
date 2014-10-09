#include <iostream>
#include "Point.h"
#include "PhysicsEngine.h"
#include <windows.h>
#include <GL/glut.h>

PhysicsEngine engine2;

int liczbaPunktow = 2;
Point* tabela = new Point[liczbaPunktow];
float pos = 0.0f;

void show1() {
	glLoadIdentity();
	glTranslatef(pos, pos, -1); // Translate our object along the y axis
	glColor3f(224/ 255.0f, 224/ 255.0f, 224/ 255.0f); // Red
	glutWireSphere(0.1, 20, 20);

}

void show2() {
	glLoadIdentity();
	glTranslatef(pos, 0, -1 + pos*(-5)); // Translate our object along the y axis
	glColor3f(204/ 255.0f, 151/ 255.0f, 151/ 255.0f); // green
	glutWireSphere(0.1, 20, 20);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();

    // w³¹czenie œwiat³a GL_LIGHT0 z parametrami domyœlnymi
    glEnable( GL_LIGHT0 );

	show1();
	show2();


	glFlush();  // Render now
}

void update(int value) {
	pos += 0.0001;
	engine2.timeStep(60 * 60 * 24);
	engine2.step(tabela, liczbaPunktow);
	std::cout << "update" << pos << std::endl;
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char** argv) {
	std::cout << "Hello inzynierko!" << std::endl;

	Point ziemia;
	ziemia.mass(5.97e24);
	ziemia.position(1.5e11, 0.);
	ziemia.velocity(0., 2.978e4);

	Point slonce;
	slonce.mass(1.99e30);
	slonce.position(0., 0.);
	slonce.velocity(0., 0.);

	tabela[0] = ziemia;
	tabela[1] = slonce;
	/*
	 for (int i = 0; i < 365; i++) {
	 engine2.step(tabela, liczbaPunktow);
	 std::cout << tabela[0].position().x() << " " << tabela[0].position().y()
	 << " " << tabela[1].position().x() << " "
	 << tabela[1].position().y() << std::endl;
	 }
	 */
	glutInit(&argc, argv);                 // Initialize GLUT

	//glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(640, 640);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner

	glutCreateWindow("Klaster atomowy"); // Create a window with the given title

	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutReshapeFunc(reshape);
	glutTimerFunc(25, update, 0);


	glutMainLoop();           // Enter the infinitely event-processing loop

}
