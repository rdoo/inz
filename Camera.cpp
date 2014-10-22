#include "Camera.h"

Camera::Camera(int width, int height){
	m_screenWidth = width;
	m_screenHeight = height;
	positionCamera(0, 0, 0,	0, 0, -1,   0, 0.1, 0);
}

void Camera::positionCamera(float pos_x, float pos_y, float pos_z, float view_x,
		float view_y, float view_z, float up_x, float up_y, float up_z) {
	mPos = Vector(pos_x, pos_y, pos_z); // set position
	mView = Vector(view_x, view_y, view_z); // set view
	mUp = Vector(up_x, up_y, up_z); // set the up vector
}

void Camera::moveCamera(float speed) {
	double spowolnienie = 1000000000.;
	Vector vector = mView - mPos;	// Get the view vector

	// forward positive cameraspeed and backward negative -cameraspeed.
	mPos.setX(mPos.x() + vector.x() * speed / spowolnienie);
	mPos.setZ(mPos.z() + vector.z() * speed / spowolnienie);
	mView.setX(mView.x() + vector.x() * speed / spowolnienie);
	mView.setZ(mView.z() + vector.z() * speed / spowolnienie);
}

void Camera::rotateView(float speed) {
	Vector vector = mView - mPos;	// Get the view vector

	mView.setZ(mPos.z() + sin(speed) * vector.x() + cos(speed) * vector.z());
	mView.setX(mPos.x() + cos(speed) * vector.x() - sin(speed) * vector.z());
}

void Camera::strafeCamera(float speed) {
	double spowolnienie = 1000000000.;
	Vector vector = mView - mPos;	// Get the view vector
	Vector orthoVector;              // Orthogonal vector for the view vector

	orthoVector.setX(-vector.z());
	orthoVector.setZ(vector.x());

	// left positive cameraspeed and right negative -cameraspeed.
	mPos.setX(mPos.x() + orthoVector.x() * speed / spowolnienie);
	mPos.setZ(mPos.z() + orthoVector.z() * speed / spowolnienie);
	mView.setX(mView.x() + orthoVector.x() * speed / spowolnienie);
	mView.setZ(mView.z() + orthoVector.z() * speed / spowolnienie);
}

void Camera::mouseMove() {

	if(!isDragging)
		return;

	int mid_x = getMidX();
	int mid_y = getMidY();

	float angle_y = 0.0f;
	float angle_z = 0.0f;

	GetCursorPos(&mousePos);	// Get the 2D mouse cursor (x,y) position

	if ((mousePos.x == mid_x) && (mousePos.y == mid_y))
		return;
	SetCursorPos(mid_x, mid_y);	// Set the mouse cursor in the center of the window

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angle_y = (float) ((mid_x - mousePos.x)) / 1000;
	angle_z = (float) ((mid_y - mousePos.y)) / 1000;

	// The higher the value is the faster the camera looks around.
	mView.setY(mView.y() + angle_z * 2);

	// limit the rotation around the x-axis
	if ((mView.y() - mPos.y()) > 8)
		mView.setY(mPos.y() + 8);
	if ((mView.y() - mPos.y()) < -8)
		mView.setY(mPos.y() - 8);

	rotateView(-angle_y); // Rotate

}

int Camera::getMidX(){
	return glutGet(GLUT_WINDOW_X) + (m_screenWidth >> 1);
}
int Camera::getMidY(){
	return glutGet(GLUT_WINDOW_Y) + (m_screenHeight >> 1);
}

void Camera::setScreenSize(int width, int height){
	m_screenWidth = width;
	m_screenHeight = height;
}
