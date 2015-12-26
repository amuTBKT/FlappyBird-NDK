#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"
#include "../core/Matrix4.h"

class Camera : public GameObject{
public:
	/*
	* width  : screen width
	* height : screen heigth
	* zNear  : near clip plane
	* zFar   : far clip plane
	*/
	float width, height, zNear, zFar;

	/*
	* projMatrix   : camera projection matrix (orthographic)
	* viewMatrix   : view matrix (just a look at matrix (looking in -z direction), translated in xy plane and rotated in z-axis
	* cameraMatrix : projMatrix * viewMatrix, used with shader 
	*/
	Matrix4 *projMatrix, *viewMatrix, *cameraMatrix;

	Camera(float, float, float, float, char *);
	~Camera();

	// call after changing camera position or rotation
	void UpdateViewMatrix();
	// call after changing camera paramters/properties
	void UpdateProjectionMatrix();

	Matrix4* GetProjectionMatrix();
	Matrix4* GetViewMatrix();
	Matrix4* GetCameraMatrix();
};

#endif
