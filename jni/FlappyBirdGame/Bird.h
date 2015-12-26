#ifndef BIRD_H_
#define BIRD_H_

#include "../Components/Sprite.h"
#include "../Core/GameTime.h"

class Bird : public Sprite{
private:
	float animationSpeed;
	float impulsePower;
	float impulseRotation;
	float rotationDecrement;
	bool isAlive;
public:
	Bird(Texture*, char*);
	~Bird();

	void Update();
	void ApplyImpulse();
	void OnCollision(Collider *collider);

	bool IsAlive();

	void Kill();
	void Respawn();
};

#endif
