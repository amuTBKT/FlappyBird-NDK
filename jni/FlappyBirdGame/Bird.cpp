#include "Bird.h"

Bird::Bird(Texture* texture, char *name) : Sprite(texture, name){
	animationSpeed = 2;
	impulsePower = 90;
	impulseRotation = 30;
	rotationDecrement = 100;
	isAlive = true;

	// set size
	SetScale(2.5 / 3.0, 2.5);
	
	// define sprite sheet parameters
	SetNumFrames(3, 1);

	// add collider
	AddCollider(GetWidth() / 1.5, GetHeight() / 1.5);
	GetCollider()->affectedByGravity = true;
}

void Bird::Update(){
	// do not update if dead
	if (!isAlive){
		return;
	}

	// delta time
	float deltaTime = GameTime::GetInstance()->GetDeltaTime();

	// animate sprite
	Animate(deltaTime * animationSpeed);

	// update rotation (to seem like it is falling, not even trying)
	Rotate(-deltaTime * rotationDecrement);
}

void Bird::OnCollision(Collider *collider){
	// kill if the collider belongs to ground or pipe game object
	if (!strcmp(collider->transform->name, "ground") || !strcmp(collider->transform->name, "pipe")){
		Kill();
	}
}

void Bird::ApplyImpulse(){
	if (!isAlive){
		return;
	}

	// boost up velocity in y direction
	GetCollider()->velocity.y = impulsePower;
	// rotate bird upwards (to seem like it is trying to go up)
	SetRotation(impulseRotation);
}

bool Bird::IsAlive(){
	return isAlive;
}

void Bird::Kill(){
	isAlive = false;
	GetCollider()->velocity.y = 0;

	// disable collider
	GetCollider()->affectedByGravity = false;
}

void Bird::Respawn(){
	isAlive = true;

	// enable collider
	GetCollider()->affectedByGravity = true;
	
	// reset sprite's rotation
	SetRotation(0);
}

Bird::~Bird(){

}

