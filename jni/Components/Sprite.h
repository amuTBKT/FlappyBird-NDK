#ifndef SPRITE_H_
#define SPRITE_H_

#include "GameObject.h"
#include "../Core/MeshManager.h"

struct FrameSetting{
	Vector2 frames;				// number of frames (columns and rows)
	float animationCounter;		// float for interpolating between frames
	Vector2 currentFrame;		// current frame
};

class Sprite : public GameObject{
private:
	float width, height;
	FrameSetting frame;
public:
	Sprite(Texture*, char*);
	~Sprite();

	// animation settings
	void SetNumFrames(int x, int y);
	void Animate(float delta);

	void SetWidth(float w);
	void SetHeight(float h);

	// override scale methods, to manipulate sprite's width and height
	void SetScale(float x, float y);
	void SetScale(const Vector2 &scl);
	void Scale(float x, float y);
	void Scale(const Vector2 &scl);

	// change width and height only using scale function
	float const GetWidth();
	float const GetHeight();
};

#endif
