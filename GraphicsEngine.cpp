# include "GraphicsEngine.h"

void GraphicsEngine::initialize(int argc, char** argv, int width, int height) {
	glutInit(&argc, argv);                 // Initialize GLUT

	//glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(640, 640);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner

	glutCreateWindow("Klaster atomowy"); // Create a window with the given title
	//engine.timeStep(60 * 60 * 24*10);

	//camera.positionCamera(0, 0, 0,	0, 0, -1,   0, 0.1, 0);

	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutReshapeFunc(reshape);
	glutTimerFunc(15, update, 0);
	glutMouseFunc(Mouse_Button);
}

void GraphicsEngine::display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(powe, powe, powe);

	gluLookAt(camera.mPos.x(),  camera.mPos.y(),  camera.mPos.z(),
			  camera.mView.x(), camera.mView.y(), camera.mView.z(),
			  camera.mUp.x(),   camera.mUp.y(),   camera.mUp.z());

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

void GraphicsEngine::displayAtom(int atomNumber){
	//glLoadIdentity();
	glColor3f(224 / 255.0f, 224 / 255.0f, 200 / 255.0f);
	glPushMatrix();

	glTranslatef(atomTable[atomNumber].position().x(), atomTable[atomNumber].position().y(), atomTable[atomNumber].position().z());
	glutWireSphere(.0000000001*0.7, 10, 10);
	glPopMatrix();
}

void GraphicsEngine::reshape(int width, int height) {
	// Compute aspect ratio of the new window
	if (height == 0)
		height = 1;                // To prevent divide by 0

	double aspect = (double) width / (double) height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset

	glOrtho(-100 * aspect, 100 * aspect, -100, 100, -100, 100);

}

void GraphicsEngine::update(int value) {
	switch(m_enablePhysx){
	case 0: break;
	case 1:
		algoEngine.step(atomTable, numberOfAtoms);
		break;
	case 2:
		physxEngine.step(atomTable, numberOfAtoms);
		break;
	}
	/*
	if (m_enablePhysx)
		physxEngine.step(atomTable, numberOfAtoms);
	else
		algoEngine.step(atomTable, numberOfAtoms);
*/
	//std::cout << atomTable[0].position() << "\t\t" << atomTable[1].position() << std::endl;
	//std::cout << objCamera.isDragging << "\t\t" << std::endl;
	glutPostRedisplay();
	glutTimerFunc(15, update, 0);
}

void GraphicsEngine::createMenu() {
	glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Stop", 0);
	glutAddMenuEntry("Algorithm Engine", 1);
	glutAddMenuEntry("Physics Engine", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void GraphicsEngine::processMenuEvents(int enablePhysx) {
	m_enablePhysx = enablePhysx;
}

void GraphicsEngine::keyboardInput()
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
