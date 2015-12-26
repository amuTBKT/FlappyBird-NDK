#include "PipePair.h"

PipePair::PipePair(float positionX, float scrn_width, float scrn_height){
	increasePoint = false;
	checkForPoint = false;

	intialXPosition = positionX;
	screenWidth = scrn_width;
	screenHeight = scrn_height;
	
	horizontalSpeed = -30;

	lowerPipe = new Sprite(TextureManager::GetInstance()->LoadTexture("lower.png", GL_NEAREST, GL_REPEAT), "pipe");
	lowerPipe->SetWidth(80);
	lowerPipe->SetHeight(500);
	lowerPipe->AddCollider(lowerPipe->GetWidth(), lowerPipe->GetHeight());
	lowerPipe->GetCollider()->velocity.x = horizontalSpeed;
	lowerPipe->GetCollider()->affectedByGravity = false;

	upperPipe = new Sprite(TextureManager::GetInstance()->LoadTexture("upper.png", GL_NEAREST, GL_REPEAT), "pipe");
	upperPipe->SetWidth(80);
	upperPipe->SetHeight(500);
	upperPipe->AddCollider(upperPipe->GetWidth(), upperPipe->GetHeight() * 4);
	upperPipe->GetCollider()->offset.set(0, -upperPipe->GetHeight() * 1.5);
	upperPipe->GetCollider()->velocity.x = horizontalSpeed;
	upperPipe->GetCollider()->affectedByGravity = false;

	Reset(false);
}

void PipePair::Reset(bool justReseting){
	// generating random position in y-direction
	float random = 1 + rand() % 4;
	float lowerPipePosY = -100 + 125 * (random - 1);
	float upperPipePosY = -100 + 125 * (random - 1) + lowerPipe->GetHeight() + 150;
	upperPipePosY += upperPipe->GetHeight() * 1.5;

	// first time adding to the scene
	if (!justReseting){
		lowerPipe->SetPosition(-100 + intialXPosition + screenWidth, lowerPipePosY);
		upperPipe->SetPosition(-100 + intialXPosition + screenWidth, upperPipePosY);
	}
	// just resetting position
	else {
		lowerPipe->SetPosition(-100 + 3 * screenWidth / 2, lowerPipePosY);
		upperPipe->SetPosition(-100 + 3 * screenWidth / 2, upperPipePosY);
	}

	checkForPoint = true;
}

void PipePair::Update(){
	// increase point
	if (lowerPipe->GetPosition().x <= screenWidth / 4.0 - lowerPipe->GetWidth() && checkForPoint){
		increasePoint = true;
	}
	// reusing the pipes
	if (lowerPipe->GetPosition().x <= -lowerPipe->GetWidth()){
		Reset(true);
	}
}

bool PipePair::NeedToIncreaseScore(){
	return increasePoint;
}

void PipePair::ScoreIncreased(){
	increasePoint = false;
	checkForPoint = false;
}

Sprite* PipePair::GetLowerPipe(){
	return lowerPipe;
}

Sprite* PipePair::GetUpperPipe(){
	return upperPipe;
}

PipePair::~PipePair(){

}
