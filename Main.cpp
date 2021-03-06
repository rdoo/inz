#include "Main.h"

PhysicsEngine physxEngine(1e-17);
AlgorithmEngine algoEngine;

int width = 640;
int height = 640;

Camera camera(width, height);

int numberOfSteps = 500;
int numberOfAtoms = 35;
Atom* atomTable = new Atom[numberOfAtoms];
long double diameter = 6e-10L;//6e-10L;
long double atomMass = 4.480389e-26; // Al

double staticZoom = 100000000000;
double dynamicZoom = 1;

bool axesEnabled = true;
bool rotateEnabled = false;
std::string readFile;
int rows = 5, columns = 4;

std::ofstream pliku, pliku2;

enum programState {
	pause,
	algorithm,
	physics,
	reset,
	save,
	axes,
	rotate,
	read,
	a2 = 20,
	a5,
	a10,
	a15,
	a20,
	a50,
	a100,
	s1 = 30,
	s5,
	s10,
	s30,
	s50,
	s100,
	s1000,
	rr = 40,
	r5,
	r10,
	r15,
	r20,
	r2d
};

programState state = pause;
programState lastState = pause;

int main(int argc, char** argv) {
	std::cout << "Initial number of atoms: " << numberOfAtoms << std::endl;
	std::cout << "Initial steps per frame: " << numberOfSteps << std::endl;
	srand(time(NULL));

	generateAtoms(atomTable, numberOfAtoms, diameter, atomMass);

	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(width, height); // Set the window's initial width & height
	glutCreateWindow("Klaster atomowy"); // Create a window with the given title

	float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float mat_shininess[] = { 90.0 };
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
	glutAddMenuEntry("5", 21);
	glutAddMenuEntry("10", 22);
	glutAddMenuEntry("15", 23);
	glutAddMenuEntry("20", 24);
	glutAddMenuEntry("50", 25);
	glutAddMenuEntry("100", 26);

	int stepMenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("1", 30);
	glutAddMenuEntry("5", 31);
	glutAddMenuEntry("10", 32);
	glutAddMenuEntry("30", 33);
	glutAddMenuEntry("50", 34);
	glutAddMenuEntry("100", 35);
	glutAddMenuEntry("1000", 36);

	int readMenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Random", 40);
	glutAddMenuEntry("5", 41);
	glutAddMenuEntry("10", 42);
	glutAddMenuEntry("15", 43);
	glutAddMenuEntry("20", 44);
	glutAddMenuEntry("2D", 45);

	glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Pause (Space Bar)", 0);
	glutAddMenuEntry("Monte Carlo (Enter)", 1);
	glutAddMenuEntry("System evolution over time", 2);
	glutAddMenuEntry("Reset", 3);
	glutAddMenuEntry("Save to file", 4);
	glutAddMenuEntry("Enable/disable axes", 5);
	glutAddMenuEntry("Enable/disable rotate", 6);
	//glutAddMenuEntry("Read", 7);
	glutAddSubMenu("Read from file", readMenu);
	glutAddSubMenu("Number of atoms", atomMenu);
	glutAddSubMenu("Number of steps per frame", stepMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

//pliku.open("Energy.txt");
/*
pliku2.open("1500.txt");

double tempu = 1500;

for(int i=1; i <=20000;i++){
	pliku2 << i << " " << tempu  << std::endl;
	tempu = tempu * exp(-0.0002);
}

pliku2.close();
*/
	glutMainLoop();           // Enter the infinitely event-processing loop
	//pliku.close();
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glScalef(dynamicZoom, dynamicZoom, dynamicZoom);

	gluLookAt(camera.mPos.x(), camera.mPos.y(), camera.mPos.z(),
			camera.mView.x(), camera.mView.y(), camera.mView.z(),
			camera.mUp.x(), camera.mUp.y(), camera.mUp.z());

	if (axesEnabled)
		drawAxes();

	for (int i = 0; i < numberOfAtoms; i++) {
		displayAtom(i);
	}

	std::ostringstream titleStr, energyStr, stepStr, lastStr, workStr;

	//workStr << "[WORK IN PROGRESS]";

	if (state == algorithm) { // TODO: do poprawy
		titleStr << "MONTE CARLO ALGORITHM";
	} else if (state == physics) {
		std::ostringstream timeStr;
		titleStr << "SYSTEM EVOLUTION OVER TIME";
		timeStr << "Virtual simulation time in ns: "
				<< (double) physxEngine.timeFromBeginning() * 1.e9 << std::endl;

		writeString(timeStr.str(), -1., .75);
	}

	if (lastState == algorithm)
		energyStr << "Total energy: "
				<< (double) algoEngine.currentEnergy / elementaryCharge
				<< " eV";
	else if (lastState == physics)
		energyStr << "Total energy: "
				<< (double) physxEngine.currentEnergy / elementaryCharge
				<< " eV";
	else if (algoEngine.currentEnergy < physxEngine.currentEnergy)
		energyStr << "Total energy: "
				<< (double) algoEngine.currentEnergy / elementaryCharge
				<< " eV";
	else
		energyStr << "Total energy: "
				<< (double) physxEngine.currentEnergy / elementaryCharge
				<< " eV";

	stepStr << "Step number: " << algoEngine.steps;
	lastStr << "Last change at step: " << algoEngine.lastChangeStep;

	writeString(workStr.str(), -1., -1.);
	writeString(titleStr.str(), -1., .95);
	writeString(energyStr.str(), -1., .90);
	writeString(stepStr.str(), -1., .85);
	writeString(lastStr.str(), -1., .80);

	glFlush();  // Render now

}

void displayAtom(int atomNumber) {
	glColor3f(184 / 255.0f, 184 / 255.0f, 200 / 182.0f);
	glPushMatrix();
	glTranslatef(atomTable[atomNumber].position().x(),
			atomTable[atomNumber].position().y(),
			atomTable[atomNumber].position().z());
	glutSolidSphere(.0000000001 * 0.5, 20, 20);
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

	if (rotateEnabled)
		camera.rotateView(0.001);

	switch (state) {
	case pause:
		lastState = pause;
		break;
	case algorithm:
		lastState = algorithm;
		for (int i = 0; i < numberOfSteps; i++) {
			algoEngine.step(atomTable, numberOfAtoms);
		}
		//pliku << algoEngine.steps << " " << (double) (algoEngine.currentEnergy / elementaryCharge / numberOfAtoms) << std::endl;

		resetAtomsVelocities(atomTable, numberOfAtoms);
		break;
	case physics:
		lastState = physics;
		for (int i = 0; i < numberOfSteps; i++) {
			physxEngine.step(atomTable, numberOfAtoms);
		}
		break;
	case reset:
		generateAtoms(atomTable, numberOfAtoms, diameter, atomMass);
		//generateAtomsInCube(atomTable, numberOfAtoms, 2.5e-10, atomMass,
		//		rows, columns);
		algoEngine.currentEnergy = algoEngine.configurationEnergy(atomTable, numberOfAtoms);
		algoEngine.steps = 0;
		algoEngine.lastChangeStep = 0;
		algoEngine.temp = 750;
		physxEngine.resetTime();
		state = pause;
		break;
	case a2:
		numberOfAtoms = 2;
		atomTable = new Atom[numberOfAtoms];
		rows = 2;
		columns = 1;
		state = reset;
		break;
	case a5:
		numberOfAtoms = 5;
		atomTable = new Atom[numberOfAtoms];
		rows = 3;
		columns = 2;
		state = reset;
		break;
	case a10:
		numberOfAtoms = 10;
		atomTable = new Atom[numberOfAtoms];
		rows = 4;
		columns = 3;
		state = reset;
		break;
	case a15:
		numberOfAtoms = 15;
		atomTable = new Atom[numberOfAtoms];
		rows = 4;
		columns = 4;
		state = reset;
		break;
	case a20:
		numberOfAtoms = 20;
		atomTable = new Atom[numberOfAtoms];
		rows = 5;
		columns = 4;
		state = reset;
		break;
	case a50:
		numberOfAtoms = 50;
		atomTable = new Atom[numberOfAtoms];
		rows = 8;
		columns = 7;
		state = reset;
		break;
	case a100:
		numberOfAtoms = 100;
		atomTable = new Atom[numberOfAtoms];
		rows = 10;
		columns = 10;
		state = reset;
		break;
	case s1:
		numberOfSteps = 1;
		state = lastState;
		break;
	case s5:
		numberOfSteps = 5;
		state = lastState;
		break;
	case s10:
		numberOfSteps = 10;
		state = lastState;
		break;
	case s30:
		numberOfSteps = 30;
		state = lastState;
		break;
	case s50:
		numberOfSteps = 50;
		state = lastState;
		break;
	case s100:
		numberOfSteps = 100;
		state = lastState;
		break;
	case s1000:
		numberOfSteps = 1000;
		state = lastState;
		break;
	case axes:
		axesEnabled = axesEnabled ? false : true;
		state = lastState;
		break;
	case rotate:
		rotateEnabled = rotateEnabled ? false : true;
		state = lastState;
		break;
	case read: {
		std::ifstream reader;
		reader.open(readFile.c_str());
		int ratoms, rsteps, rlastchange;
		long double renergy;
		std::string line;

		std::getline(reader, line);
		ratoms = atoi(line.substr(2, 3).c_str());
		std::getline(reader, line);
		rsteps = atoi(line.substr(2, 10).c_str());
		std::getline(reader, line);
		rlastchange = atoi(line.substr(2, 10).c_str());
		std::getline(reader, line);
		renergy = atof(line.substr(2, 10).c_str());

		algoEngine.steps = rsteps;
		algoEngine.lastChangeStep = rlastchange;
		algoEngine.currentEnergy = renergy * elementaryCharge;
		numberOfAtoms = ratoms;
		atomTable = new Atom[numberOfAtoms]; //TODO :zmienic
		Atom atom;
		Vector position;
		int i = 0;
		long double x, y, z;
		while (std::getline(reader, line)) {
			std::istringstream iss(line);
			iss >> x;
			iss >> y;
			iss >> z;
			position = Vector(x, y, z);
			atom = Atom(atomMass, position, Vector(0., 0., 0.));
			atomTable[i] = atom;
			i++;
		}
		reader.close();
	}

		state = pause;
		break;
	case rr:
		readFile = "random.txt";
		state = read;
		break;
	case r5:
		readFile = "5.txt";
		state = read;
		break;
	case r10:
		readFile = "10.txt";
		state = read;
		break;
	case r15:
		readFile = "15.txt";
		state = read;
		break;
	case r20:
		readFile = "20.txt";
		state = read;
		break;
	case r2d:
		readFile = "2d.txt";
		state = read;
		break;
	case save:
		std::ofstream plik;
		std::ostringstream name, comment;
		int licznika = 0;
		double suum = 0;
		for (int f=0; f < numberOfAtoms; f++)
			for (int k=0; k < numberOfAtoms; k++){
				double odleglosc = atomTable[f].position().distanceFromVector(atomTable[k].position());
				if (odleglosc > 2e-10 && odleglosc < 3e-10){
					std::cout << odleglosc << std::endl;
					licznika++;
					suum += odleglosc;
				}
			}

		std::cout << "liczba sasiadow: "<< licznika << " suma: " << suum << " srednia: " << suum/licznika << std::endl;

		name << numberOfAtoms << "-" << algoEngine.steps << ".txt";
		comment << "# " << numberOfAtoms << " atoms" << std::endl << "# "
				<< algoEngine.steps << " steps" << std::endl << "# "
				<< algoEngine.lastChangeStep << " last change step" << std::endl
				<< "# " << (double) algoEngine.currentEnergy / elementaryCharge
				<< " eV" << std::endl;
		plik.open(name.str().c_str());
		plik << comment.str();
		for (int i = 0; i < numberOfAtoms; i++)
			plik << atomTable[i].position() << std::endl;
		plik.close();
		state = pause;
		break;
	}

	//if ((algoEngine.steps - algoEngine.lastChangeStep) > 20000)
	//	state = pause;

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
			if (dynamicZoom > 0.1)
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
	/*} else if ((GetKeyState(VK_SPACE) & 0x80)) {
		state = pause;
	} else if ((GetKeyState(VK_RETURN) & 0x80)) {
		state = algorithm;*/
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
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
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

void writeStringIn3D(std::string str, double x, double y, double z) {
	glRasterPos3f(x, y, z);
	glColor3f(0.0f, 0.0f, 0.0f);
	const char * p = str.c_str();
	do
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p);
	while (*(++p));
}

void drawAxes() {
	double ang = 1e-10;
	int halfLength = 7;
	double off = 0.2;

	glDisable(GL_LIGHTING);
	glColor3f(0, 0, 0);

	glBegin(GL_LINES);
	glVertex3f(-halfLength * ang, -halfLength * ang, halfLength * ang);
	glVertex3f(halfLength * ang, -halfLength * ang, halfLength * ang);

	glVertex3f(-halfLength * ang, -halfLength * ang, halfLength * ang);
	glVertex3f(-halfLength * ang, halfLength * ang, halfLength * ang);

	glVertex3f(-halfLength * ang, -halfLength * ang, -halfLength * ang);
	glVertex3f(-halfLength * ang, -halfLength * ang, halfLength * ang);
	glEnd();

	for (int i = -halfLength + 1; i < halfLength; i++) {
		std::ostringstream oss;
		oss << i;
		writeStringIn3D(oss.str(), i * ang, (-halfLength + off) * ang,
				halfLength * ang);
		writeStringIn3D(oss.str(), (-halfLength + off) * ang, i * ang,
				halfLength * ang);
		writeStringIn3D(oss.str(), -halfLength * ang, (-halfLength + off) * ang,
				i * ang);
	}

	writeStringIn3D("x [A]", 0 * ang, (-halfLength - 2 * off) * ang,
			halfLength * ang);
	writeStringIn3D("y [A]", (-halfLength - 4 * off) * ang, 0 * ang,
			halfLength * ang);
	writeStringIn3D("z [A]", -halfLength * ang, (-halfLength - 2 * off) * ang,
			0 * ang);

	glEnable(GL_LIGHTING);
}
