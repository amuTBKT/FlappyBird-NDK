#ifndef GAME_H_
#define GAME_H_

#include "GameTime.h"
#include "Input.h"
#include "AudioManager.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "Scene.h"

class Game
{
private:
	// change current scene
	bool SetScene(Scene *scn);
	bool sceneChanged;
	Scene *nextScene;
public:	
	Game();

	static Game *GetInstance();

	// initializes game, shader manager, mesh manager, rendering engine (#MustCallBeforeDoingAnything)
	void Initialize(int screenWidth, int screenHeight);

	// sets update rate
	void SetDelta(float d);

	// updates scene
	void Update();

	// renders scene
	void Render();

	// disposes all the resources
	void Dispose();

	// when screen is touched
	void TouchBegan(int x, int y);

	// touch move
	void TouchMove(int x, int y);

	// touch end
	void TouchEnd(int x, int y);

	// add call back to change scene (scene is changed in update function)
	void ChangeScene(Scene *scn);

	// pause game
	void Pause();

	// resume game
	void Resume();

	// update rate (1 / fps)
	float delta;
	
	// scene to be used
	Scene *scene;

	bool gamePaused;
};

#endif
