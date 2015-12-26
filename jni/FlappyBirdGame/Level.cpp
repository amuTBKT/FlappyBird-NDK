#include "Level.h"

#include "../Core/Game.h"
#include "MainMenu.h"

void FlappyLevel::Initialize(){
	delta = 0;
	elapsedTime = 0;
	score = 0;
	pauseGame = true;
	gameOver = false;

	screenWidth = 480;
	screenHeight = 800;

	// initialize scene's main camera
	mainCamera = new Camera(screenWidth, screenHeight, 0, 100, "MainCamera");
	mainCamera->SetPosition(screenWidth / 2, screenHeight / 2);
	mainCamera->UpdateViewMatrix();
	
	Input::GetInstance()->SetCameraParams(mainCamera);

	// initialize physics world
	world = new PhysicsWorld();
	world->SetGravity(Vector2(0, -40));

	// create background sprite
	Texture *texture = TextureManager::GetInstance()->LoadTexture("background.png", GL_NEAREST, GL_REPEAT);
	background = new Sprite(texture, "background");
	background->SetPosition(screenWidth / 2, screenHeight / 2);
	background->SetWidth(screenWidth);
	background->SetHeight(screenHeight);
	background->GetMesh()->GetMaterial()->SetDiffuseTextureTiling(2 * screenWidth / 640.0, 1);
	AddChild(background);

	// create ground sprite
	texture = TextureManager::GetInstance()->LoadTexture("ground.png", GL_NEAREST, GL_REPEAT);
	ground = new Sprite(texture, "ground");
	ground->SetWidth(screenWidth);
	ground->SetPosition(screenWidth / 2, ground->GetHeight() / 2);
	ground->AddCollider(ground->GetWidth(), ground->GetHeight());
	ground->GetCollider()->affectedByGravity = false;

	// our flappy bird
	texture = TextureManager::GetInstance()->LoadTexture("flappy_atlas.png", GL_NEAREST, GL_REPEAT);
	bird = new Bird(texture, "bird");
	bird->SetPosition(screenWidth / 4, screenHeight / 2);

	// pipe pair 1
	pipePair1 = new PipePair(screenWidth / 2, screenWidth, screenHeight);
	AddPipePair(pipePair1);

	// pipe pair 2
	pipePair2 = new PipePair(screenWidth, screenWidth, screenHeight);
	AddPipePair(pipePair2);

	// pipe pair 3
	pipePair3 = new PipePair(3 * screenWidth / 2, screenWidth, screenHeight);
	AddPipePair(pipePair3);

	// gui to display score
	scoreGUI = new NumberRenderer("score_group");
	scoreGUI->Scale(3.0, 3.0);
	scoreGUI->SetPosition(screenWidth - scoreGUI->width * 2.5, screenHeight - scoreGUI->height * 2.5);

	// add gameobjects in required drawing order
	AddChild(ground);
	AddChild(bird);
	
	// initialize and add score card to scene
	CreateScoreCard();

	// add score gui's game objects
	AddChild(scoreGUI->GetGameObjectAtIndex(0));
	AddChild(scoreGUI->GetGameObjectAtIndex(1));
	AddChild(scoreGUI);

	// add colliders to the world
	world->AddCollider(ground->GetCollider());
	world->AddCollider(bird->GetCollider());

	// audio effects
	flapAudio = AudioManager::GetInstance()->CreateSFX("sfx_wing.ogg");
	hitAudio = AudioManager::GetInstance()->CreateSFX("sfx_hit.ogg");
	pointAudio = AudioManager::GetInstance()->CreateSFX("sfx_point.ogg");
	swooshAudio = AudioManager::GetInstance()->CreateSFX("sfx_swooshing.ogg");

	// particle system
	feathersParticleSystem = new ParticleSystem(20);
	feathersParticleSystem->SetTexture(TextureManager::GetInstance()->LoadTexture("feather_2.png", GL_LINEAR, GL_REPEAT));
	feathersParticleSystem->GetEmitter()->particleStartSize.set(23, 12);
	feathersParticleSystem->GetEmitter()->particleEndSize.set(23, 12);
	AddParticleSystem(feathersParticleSystem);

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

void FlappyLevel::AddPipePair(PipePair *pipePair){
	AddChild(pipePair->GetLowerPipe());
	AddChild(pipePair->GetUpperPipe());
	world->AddCollider(pipePair->GetLowerPipe()->GetCollider());
	world->AddCollider(pipePair->GetUpperPipe()->GetCollider());
}

void FlappyLevel::Update(float d){
	delta = d;

	if (pauseGame){
		return;
	}
	if (gameOver){
		// animate score card
		if (gameOver){
			if (scoreCardGroup->GetPosition().y < screenHeight / 2){
				scoreCardGroup->Translate(0, screenHeight * delta);
			}
			else {
				scoreGUI->SetPosition(screenWidth / 2 + scoreCard->GetWidth(), screenHeight / 2);
			}
		}
		return;
	}

	elapsedTime += d;

	// update game objects
	Scene::UpdateGameObjects();

	// update physics world
	world->Update(delta * 6.5);
	
	////// ---------- our game logic goes from here on ---------- //////

	// creating parallax effect
	background->GetMesh()->GetMaterial()->SetDiffuseTextureOffset(elapsedTime, 0);
	ground->GetMesh()->GetMaterial()->SetDiffuseTextureOffset(elapsedTime / 5.0, 0);

	// check for bird
	if (!bird->IsAlive()){
//		AudioManager::GetInstance()->PlaySFX(hitAudio);
		gameOver = true;
		ShowScoreCard();
	}

	// update pipes
	pipePair1->Update();
	pipePair2->Update();
	pipePair3->Update();

	// update score
	UpdateScore();
}

void FlappyLevel::UpdateScore(){
	if (pipePair1->NeedToIncreaseScore()){
		pipePair1->ScoreIncreased();
		score++;
//		AudioManager::GetInstance()->PlaySFX(pointAudio);
	}
	if (pipePair2->NeedToIncreaseScore()){
		pipePair2->ScoreIncreased();
		score++;
//		AudioManager::GetInstance()->PlaySFX(pointAudio);
	}
	if (pipePair3->NeedToIncreaseScore()){
		pipePair3->ScoreIncreased();
		score++;
//		AudioManager::GetInstance()->PlaySFX(pointAudio);
	}
	scoreGUI->UpdateNumber(score);
}

void FlappyLevel::CreateScoreCard(){
	Texture *texture = TextureManager::GetInstance()->LoadTexture("score_dialogue.png", GL_NEAREST, GL_REPEAT);
	scoreCard = new Sprite(texture, "score_card");
	
	texture = TextureManager::GetInstance()->LoadTexture("medals_atlas.png", GL_NEAREST, GL_REPEAT);
	medals = new Sprite(texture, "score_card");
	medals->SetNumFrames(3, 1);
	medals->SetScale(1.0 / 3.0, 1.0);
	medals->SetPosition(-scoreCard->GetWidth() / 4 - medals->GetWidth() / 4.5, -medals->GetHeight() / 4.5);

	texture = TextureManager::GetInstance()->LoadTexture("ok_button.png", GL_NEAREST, GL_REPEAT);
	continueButton = new Sprite(texture, "continueButton");
	continueButton->SetPosition(0, -50);
	continueButton->AddCollider(continueButton->GetWidth(), continueButton->GetHeight());
	
	// hide
	scoreCard->isHidden = true;
	medals->isHidden = true;
	continueButton->isHidden = true;

	// drawing order
	AddChild(scoreCard);
	AddChild(medals);
	AddChild(continueButton);

	// to group objects for animating them together
	scoreCardGroup = new GameObjectGroup("scorecard_group");
	scoreCardGroup->AddGameObject(scoreCard);
	scoreCardGroup->AddGameObject(medals);
	scoreCardGroup->AddGameObject(continueButton);
	AddChild(scoreCardGroup);
	scoreCardGroup->SetPosition(screenWidth / 2, -screenHeight / 2);
	scoreCardGroup->Scale(3.0, 3.0);
}

void FlappyLevel::ShowScoreCard(){
	// show
	scoreCard->isHidden = false;
	medals->isHidden = false;
	continueButton->isHidden = false;

	// bronze, silver, gold or no medal
	if (score <= 10 && score > 0){
		medals->GetMesh()->GetMaterial()->SetDiffuseTextureOffset(0.0 / 3.0, 0);
	}
	else if (score <= 20 && score > 10){
		medals->GetMesh()->GetMaterial()->SetDiffuseTextureOffset(1.0 / 3.0, 0);
	}
	else if (score > 20){
		medals->GetMesh()->GetMaterial()->SetDiffuseTextureOffset(2.0 / 3.0, 0);
	}
	else {
		// no medal
		medals->isHidden = true;
	}
//	AudioManager::GetInstance()->PlaySFX(swooshAudio);
}

void FlappyLevel::TouchBegan(){
	// start game
	if (pauseGame){
		pauseGame = false;
	}

	// listen for continue button, if game is over
	if (gameOver){
		if (continueButton->GetCollider()->InBounds(Input::GetInstance()->GetTouchPosition())){
			// set screen to main menu
			Game::GetInstance()->ChangeScene(new MainMenu());
			return;
		}
	}

	// flap the bird
	if (bird->IsAlive()){
		bird->ApplyImpulse();
		feathersParticleSystem->SetPosition(bird->GetPosition());
		feathersParticleSystem->Emit(3);
//		AudioManager::GetInstance()->PlaySFX(flapAudio);
	}
}

void FlappyLevel::Pause(){
	pauseGame = true;
}

void FlappyLevel::Resume(){

}
