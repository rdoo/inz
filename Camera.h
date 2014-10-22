#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
#include <windows.h>					// Header File For Windows
#include <GL/glut.h>
#include <cmath>

#define CAMERASPEED	0.03f				// The Camera Speed

class Camera {
	POINT mousePos;
	int m_screenWidth, m_screenHeight;
public:
	int isDragging = 0;
	Vector mPos;
	Vector mView;
	Vector mUp;

	Camera(int width, int height);
	void strafeCamera(float speed);
	void mouseMove();
	void moveCamera(float speed);
	void rotateView(float speed);
	void positionCamera(float pos_x, float pos_y, float pos_z, float view_x,
			float view_y, float view_z, float up_x, float up_y, float up_z);
	int getMidX();
	int getMidY();
	void setScreenSize(int width, int height);
};

#endif
