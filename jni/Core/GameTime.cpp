#include "GameTime.h"

GameTime* GameTime::GetInstance(){
	static GameTime *instance;

	if (instance == 0){
		instance = new GameTime();
	}

	return instance;
}


void GameTime::Initialize(){
	timeCounter = milliseconds_now();
}

void GameTime::Update(){
	deltaTime = (float)GetTimeSinceLastUpdate() / 1000.0f;		// update delta time
	timeCounter = milliseconds_now();							// set time counter to current time
}

long GameTime::GetTimeSinceLastUpdate(){
	return milliseconds_now() - timeCounter;					// current time - time for previous update
}

float const GameTime::GetDeltaTime(){
	return deltaTime;
}
