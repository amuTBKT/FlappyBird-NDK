#include "Game.h"

Game::Game(){
	gamePaused = true;
	scene = 0;

	sceneChanged = false;
	nextScene = 0;
}

Game* Game::GetInstance(){
	static Game *game;

	if (game == 0){
		game = new Game();
	}

	return game;
}

void Game::Initialize(int screenWidth, int screenHeight){
	GameTime::GetInstance()->Initialize();
	AudioManager::GetInstance()->Initialize();
	ShaderManager::GetInstance()->Initialize();
	RenderingEngine::GetInstance()->Initialize(screenWidth, screenHeight);
}

void Game::Update(){
	// change scene
	if (sceneChanged){
		sceneChanged = false;
		SetScene(nextScene);
		nextScene = 0;
	}

	GameTime::GetInstance()->Update();
	SetDelta(GameTime::GetInstance()->GetDeltaTime());

	if (scene != 0 && !gamePaused){
		scene->Update(delta);
	}
}

void Game::Pause(){
	gamePaused = true;

	if (scene != 0){
		scene->Pause();
	}
}

void Game::Resume(){
	gamePaused = false;

	if (scene != 0){
		scene->Resume();
	}
}

void Game::TouchBegan(int x, int y){
	Input::GetInstance()->SetTouchStatus(1, x, y);

	if (scene != 0){
		scene->TouchBegan();
	}
}

void Game::TouchMove(int x, int y){
	if (scene != 0){
		scene->TouchMove();
	}
}

void Game::TouchEnd(int x, int y){
	Input::GetInstance()->SetTouchStatus(0, x, y);

	if (scene != 0){
		scene->TouchEnd();
	}
}

void Game::SetDelta(float d){
	delta = d;
}

void Game::Render(){
	if (scene != 0  && !gamePaused){
		scene->Render();
	}
}

bool Game::SetScene(Scene *scn){
	// delete loaded meshes
	MeshManager::GetInstance()->Dispose();

	// reset render passes (also initializes rendering engine components)
	RenderingEngine::GetInstance()->Reset();

	if (scene != 0){
		scene->Dispose();
		delete scene;
		scene = 0;
	}

	scene = scn;
	scene->Initialize();

	return true;
}

void Game::ChangeScene(Scene *scn){
	sceneChanged = true;
	nextScene = scn;
}

void Game::Dispose(){
	if (scene != 0) {
		scene->Dispose();
	}

	AudioManager::GetInstance()->Dispose();
	MeshManager::GetInstance()->Dispose();
	TextureManager::GetInstance()->Dispose();
	RenderingEngine::GetInstance()->Dispose();
	ShaderManager::GetInstance()->Dispose();
}
