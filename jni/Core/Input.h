#ifndef INPUT_H_
#define INPUT_H_

#include "../Components/Camera.h"
#include "../Rendering/RenderingEngine.h"
#include "Vector2.h"

struct Touch{
	bool touch;
	Vector2 touchPosition;
};

struct CameraParams{
	Vector2 size;
	Vector2 position;
};

class Input
{
private:
	// touch status
	Touch touchStatus;
	// for transforming touch location based on camera size (actual game screen)
	CameraParams cameraParams;
public:
	static Input* GetInstance();

	void SetCameraParams(Camera *camera);
	void SetTouchStatus(bool down, int x, int y);
	Touch *GetTouchStatus();
	const Vector2& GetTouchPosition();
};

#endif

