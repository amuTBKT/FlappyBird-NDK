#ifndef PIPE_PAIR_H_
#define PIPE_PAIR_H_

#include <string>

#include "../Core/TextureManager.h"
#include "../Components/Sprite.h"
#include "../Core/GameTime.h"

class PipePair{
private:
	Sprite *lowerPipe, *upperPipe;
	float screenWidth, screenHeight, horizontalSpeed;
	float intialXPosition;

	bool checkForPoint;
	bool increasePoint;
public:
	PipePair(float positionX, float scrn_width, float scrn_height);
	~PipePair();

	Sprite *GetLowerPipe();
	Sprite *GetUpperPipe();

	void Update();

	// to re use the pipes
	void Reset(bool justResetting);

	// to notify level to increase score
	bool NeedToIncreaseScore();
	
	// to reset increaseScore flag (call after increasing score)
	void ScoreIncreased();
};

#endif
