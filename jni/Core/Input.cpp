#include "Input.h"

Input* Input::GetInstance(){
	static Input *instance;

	if (instance == 0){
		instance = new Input();
	}

	return instance;
}

void Input::SetCameraParams(Camera *camera){
	cameraParams.size.set(camera->width, camera->height);
	cameraParams.position = camera->GetPosition();
}

void Input::SetTouchStatus(bool down, int x, int y){
	// set touch status (touch began or touch end)
	touchStatus.touch = down;

	// transform touch location from screen space to game space
	int tx = ((float)x / (float)RenderingEngine::GetInstance()->SCREEN_WIDTH) * cameraParams.size.x;
	int ty = ((float)y / (float)RenderingEngine::GetInstance()->SCREEN_HEIGHT) * cameraParams.size.y;

	// set touch position in game space
	touchStatus.touchPosition.set(tx, ty);
}

Touch *Input::GetTouchStatus(){
	return &touchStatus;
}

const Vector2& Input::GetTouchPosition(){
	return touchStatus.touchPosition;
}
