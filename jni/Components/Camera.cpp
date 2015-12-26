#include "Camera.h"

Camera::Camera(float w, float h, float near, float far, char *name) : GameObject(name){
	width = w;
	height = h;
	zNear = near;
	zFar = far;

	projMatrix = new Matrix4();
	viewMatrix = new Matrix4();
	cameraMatrix = new Matrix4();

	// update projection matrix
	UpdateProjectionMatrix();
	// update view matrix
	UpdateViewMatrix();
}

Matrix4* Camera::GetProjectionMatrix(){
	return projMatrix;
}

Matrix4* Camera::GetViewMatrix(){
	return viewMatrix;
}

void Camera::UpdateProjectionMatrix(){
	projMatrix->InitOrthographic(-width / 2, width / 2, -height / 2, height / 2, zNear, zFar);

	(*cameraMatrix) = (*projMatrix) * (*viewMatrix);
}

void Camera::UpdateViewMatrix(){
	viewMatrix->InitView();
	viewMatrix->Translate(transform->position * -1);
	viewMatrix->Rotate(transform->rotation);

	(*cameraMatrix) = (*projMatrix) * (*viewMatrix);
}

Matrix4* Camera::GetCameraMatrix(){
	return cameraMatrix;
}

Camera::~Camera() {
	delete cameraMatrix;
	delete projMatrix;
	delete viewMatrix;
}

