#ifndef GAME_TIME_H_
#define GAME_TIME_H_

#include <time.h>

class GameTime{
private:
	long milliseconds_now() {
		timespec now;
		int err = clock_gettime(CLOCK_MONOTONIC, &now);
		return now.tv_sec * 1000.0L + now.tv_nsec / 1000000.0L;
	}
	long timeCounter;
	float deltaTime;
public:
	static GameTime* GetInstance();
	
	void Initialize();
	const float GetDeltaTime();
	long GetTimeSinceLastUpdate();
	void Update();
};

#endif
