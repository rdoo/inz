/************************************************************
*	APRON TUTORIALS PRESENTED BY MORROWLAND					*
*************************************************************
*	Author					: Ronny André Reierstad			*
*	Web Page				: www.morrowland.com			*
*	E-Mail					: apron@morrowland.com			*
*	Date					: 24.03.2004					*
************************************************************/

#include "Camera.h"
#include <GL/glut.h>
/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA POSITION CAMERA
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Position_Camera(float pos_x,  float pos_y,  float pos_z,
							  float view_x, float view_y, float view_z,
							  float up_x,   float up_y,   float up_z)
{
	mPos	= Vector(pos_x,  pos_y,  pos_z ); // set position
	mView	= Vector(view_x, view_y, view_z); // set view
	mUp		= Vector(up_x,   up_y,   up_z  ); // set the up vector
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA MOVE CAMERA
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Move_Camera(float speed)
{
	double spowolnienie = 1000000000.;
	Vector vVector = mView - mPos;	// Get the view vector
	
	// forward positive cameraspeed and backward negative -cameraspeed.
	mPos.setX(mPos.x()  + vVector.x() * speed / spowolnienie);
	mPos.setZ(mPos.z()  + vVector.z() * speed / spowolnienie);
	mView.setX(mView.x() + vVector.x() * speed / spowolnienie);
	mView.setZ(mView.z() + vVector.z() * speed / spowolnienie);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA ROTATE VIEW
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Rotate_View(float speed)
{
	Vector vVector = mView - mPos;	// Get the view vector

	mView.setZ(mPos.z() + sin(speed)*vVector.x() + cos(speed)*vVector.z());
	mView.setX(mPos.x() + cos(speed)*vVector.x() - sin(speed)*vVector.z());
}


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA STRAFE CAMERA
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Strafe_Camera(float speed)
{
	double spowolnienie = 1000000000.;
	Vector vVector = mView - mPos;	// Get the view vector
	Vector vOrthoVector;              // Orthogonal vector for the view vector

	vOrthoVector.setX(-vVector.z());
	vOrthoVector.setZ(vVector.x());

	// left positive cameraspeed and right negative -cameraspeed.
	mPos.setX(mPos.x()  + vOrthoVector.x() * speed / spowolnienie);
	mPos.setZ(mPos.z()  + vOrthoVector.z() * speed / spowolnienie);
	mView.setX(mView.x() + vOrthoVector.x() * speed / spowolnienie);
	mView.setZ(mView.z() + vOrthoVector.z() * speed / spowolnienie);
}

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA MOUSE MOVE
/////////////////////////////////////////////////////////////////////////////////////////////////
/*
void CCamera::Mouse_Button(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = 1; // start dragging
			GetCursorPos(&mousePos); // save x where button first pressed
		}
		else  {
			//angle += deltaAngle; // update camera turning angle
			isDragging = 0; // no longer dragging
		}
	}
}
*/
void CCamera::Mouse_Move(int wndWidth, int wndHeight)
{

	int mid_x = wndWidth  >> 1;	
	int mid_y = wndHeight >> 1;	
	float angle_y  = 0.0f;				
	float angle_z  = 0.0f;							
	
	GetCursorPos(&mousePos);	// Get the 2D mouse cursor (x,y) position

	if( (mousePos.x == mid_x) && (mousePos.y == mid_y) ) return;
	SetCursorPos(mid_x, mid_y);	// Set the mouse cursor in the center of the window

	//if (!isDragging) return;
	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angle_y = (float)( (mid_x - mousePos.x) ) / 1000;
	angle_z = (float)( (mid_y - mousePos.y) ) / 1000;

	// The higher the value is the faster the camera looks around.
	mView.setY(mView.y() + angle_z * 2);

	// limit the rotation around the x-axis
	if((mView.y() - mPos.y()) > 8)  mView.setY(mPos.y() + 8);
	if((mView.y() - mPos.y()) <-8)  mView.setY(mPos.y() - 8);
	
	Rotate_View(-angle_y); // Rotate


}



//Ronny André Reierstad
//www.morrowland.com
//apron@morrowland.com
