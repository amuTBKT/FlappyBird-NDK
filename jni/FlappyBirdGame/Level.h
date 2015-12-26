#ifndef FLAPPY_LEVEL_H_
#define FLAPPY_LEVEL_H_

#include "../Core/Scene.h"

#include "Bird.h"
#include "PipePair.h"
#include "NumberRenderer.h"

#include "../Rendering/PostProcessEffects/GrayscalePass.h"
#include "../Rendering/PostProcessEffects/VignettePass.h"
#include "../Rendering/PostProcessEffects/ClassicTheme.h"

class FlappyLevel : public Scene
{
private:
	bool pauseGame, gameOver;
	int score;
public:	
	void Initialize();
	void Update(float delta);
	void TouchBegan();

	void Pause();
	void Resume();

	// helper function to add pipe pair to scene
	void AddPipePair(PipePair *pipePair);

	// update score (whenever pipe crosses left edge)
	void UpdateScore();

	// display score card
	void ShowScoreCard();

	// initialize score card stuff
	void CreateScoreCard();

	// rate of update (1.0 / fps)
	float delta;

	// time since game started
	float elapsedTime;

	// screen width and height
	float screenWidth, screenHeight;

	// some sprites
	Sprite *ground, *background, *scoreCard, *medals, *continueButton;
	
	// group score card stuff for easy animation
	GameObjectGroup *scoreCardGroup;
	
	// gui to display score
	NumberRenderer *scoreGUI;
	
	// our bird
	Bird *bird;

	// particle system for feathers
	ParticleSystem *feathersParticleSystem;

	// we could use array to store pip pair, but this way is also nice as we only have to deal with 3 of them
	PipePair *pipePair1, *pipePair2, *pipePair3;

	AudioEffect *flapAudio, *hitAudio, *pointAudio, *swooshAudio;
};

#endif
