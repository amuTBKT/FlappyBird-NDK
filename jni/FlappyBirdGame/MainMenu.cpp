#include "MainMenu.h"

#include "Level.h"
#include "../Core/Game.h"

void MainMenu::Initialize(){
	delta = 0;
	elapsedTime = 0;

	float screenWidth = 480;
	float screenHeight = 800;

	// initialize scene's main camera
	mainCamera = new Camera(screenWidth, screenHeight, 0, 10, "MainCamera");
	mainCamera->SetPosition(screenWidth / 2, screenHeight / 2);
	mainCamera->UpdateViewMatrix();

	Input::GetInstance()->SetCameraParams(mainCamera);

	Texture *texture;
	// add background
	texture = TextureManager::GetInstance()->LoadTexture("background.png", GL_NEAREST, GL_REPEAT);
	background = new Sprite(texture, "background");
	background->SetPosition(screenWidth / 2, screenHeight / 2);
	background->SetWidth(screenWidth);
	background->SetHeight(screenHeight);
	background->GetMesh()->GetMaterial()->SetDiffuseTextureTiling(2 * screenWidth / 640.0, 1);

	// add ground
	texture = TextureManager::GetInstance()->LoadTexture("logo.png", GL_NEAREST, GL_REPEAT);
	logo = new Sprite(texture, "logo");
	logo->Scale(3, 3);
	logo->SetPosition(screenWidth / 2, 3 * screenHeight / 4);

	texture = TextureManager::GetInstance()->LoadTexture("play_button.png", GL_NEAREST, GL_REPEAT);
	playButton = new Sprite(texture, "playButton");
	playButton->SetScale(4, 4);
	playButton->SetPosition(screenWidth / 2, screenHeight / 4);
	playButton->AddCollider(playButton->GetWidth(), playButton->GetHeight());

	// drawing order
	AddChild(background);
	AddChild(logo);
	AddChild(playButton);

	// my phone was too slow for these effects

//	// add post process effects
//	// gray scale effect
//	RenderingEngine::GetInstance()->AddRenderPass(new GrayscalePass(screenWidth, screenHeight));
//
//	// vignette effect
//	RenderingEngine::GetInstance()->AddRenderPass(new VignettePass(screenWidth, screenHeight));
//
//	// radial gradient and noise
//	ClassicTheme *classyTheme = new ClassicTheme(screenWidth, screenHeight);
//	classyTheme->SetCenter(new Vector2(screenWidth / 2, screenHeight / 2));
//	classyTheme->SetRadius(1200);
//	RenderingEngine::GetInstance()->AddRenderPass(classyTheme);
}

void MainMenu::Update(float d){
	delta = d;

	elapsedTime += d;

	// update game objects
	Scene::UpdateGameObjects();

	////// ---------- our own logic goes from here on ---------- //////

	logo->Translate(0, 2 * sinf(2 * elapsedTime));
}

void MainMenu::TouchBegan(){
	// start level of button is touched
	if (playButton->GetCollider()->InBounds(Input::GetInstance()->GetTouchPosition())){
		Game::GetInstance()->ChangeScene(new FlappyLevel());
		return;
	}
}
