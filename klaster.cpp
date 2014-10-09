#include <iostream>
#include "Point.h"
#include "PhysicsEngine.h"
#include <windows.h>
#include <GL/glut.h>

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	// Draw a Red 1x1 Square centered at origin
	glBegin(GL_POLYGON);              // Each set of 4 vertices form a quad
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex2f(-0.5f, -0.5f);    // x, y
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glEnd();

	glFlush();  // Render now
}

int main(int argc, char** argv) {
	std::cout << "Hello inzynierko!" << std::endl;

	PhysicsEngine engine2;
	engine2.timeStep(60 * 60 * 24);

	Point ziemia;
	ziemia.mass(5.97e24);
	ziemia.position(1.5e11, 0.);
	ziemia.velocity(0., 2.978e4);

	Point slonce;
	slonce.mass(1.99e30);
	slonce.position(0., 0.);
	slonce.velocity(0., 0.);

	int liczbaPunktow = 2;

	Point* tabela = new Point[liczbaPunktow];
	tabela[0] = ziemia;
	tabela[1] = slonce;

	for (int i = 0; i < 365; i++) {
		engine2.step(tabela, liczbaPunktow);
		std::cout << tabela[0].position().x() << " " << tabela[0].position().y()
				<< " " << tabela[1].position().x() << " "
				<< tabela[1].position().y() << std::endl;
	}

	glutInit(&argc, argv);                 // Initialize GLUT
	glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
	glutInitWindowSize(320, 320);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutMainLoop();           // Enter the infinitely event-processing loop

}
