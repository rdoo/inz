#ifndef _MAIN_H
#define _MAIN_H


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")


#include <windows.h>					// Header File For Windows
#include <gl\gl.h>						// Header File For The OpenGL32 Library
#include <gl\glu.h>						// Header File For The GLU32 Library
//#include <gl\glaux.h>					// Header File For The Glaux Library

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
#include <math.h>
#include "Vector.h"



#define CAMERASPEED	0.03f				// The Camera Speed
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

//////////////////////////////////////
//The CCamera Class
//////////////////////////////////////
class CCamera 
{
	public:
	int isDragging = 0;
	POINT mousePos;
		Vector mPos;
		Vector mView;
		Vector mUp;

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

		void Strafe_Camera(float speed);

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
	//	void Mouse_Button(int button, int state, int x, int y);
		void Mouse_Move(int wndWidth, int wndHeight);
		void Move_Camera(float speed);
		void Rotate_View(float speed);
		void Position_Camera(float pos_x, float pos_y,float pos_z,
			 				 float view_x, float view_y, float view_z,
							 float up_x,   float up_y,   float up_z);
};



//////////////////////////////////////
//	Global Variables
//////////////////////////////////////
extern	HDC			hDC;				// Device context
extern	HGLRC		hRC;				// Permanent rendering context
extern	HWND		hWnd;				// Holds our window handle
extern	HINSTANCE	hInstance;			// Holds the instance of the application



//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

//////////////////////////////////////
//	MAIN FUNCTIONS
//////////////////////////////////////
void Keyboard_Input();
void Draw_Grid();

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////




#endif

//Ronny André Reierstad
//www.morrowland.com
//apron@morrowland.com
