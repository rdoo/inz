#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
#include <windows.h>					// Header File For Windows
#include <cmath>

#define CAMERASPEED	0.03f				// The Camera Speed

class Camera {
public:
	int isDragging = 0;
	POINT mousePos;
	Vector mPos;
	Vector mView;
	Vector mUp;

	void strafeCamera(float speed);
	void mouseMove(int wndWidth, int wndHeight);
	void moveCamera(float speed);
	void rotateView(float speed);
	void positionCamera(float pos_x, float pos_y, float pos_z, float view_x,
			float view_y, float view_z, float up_x, float up_y, float up_z);
};

#endif
