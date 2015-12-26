#ifndef PHYSICS_WORLD_H_
#define PHYSICS_WORLD_H_

#include <vector>
#include "../Components/GameObject.h"

class PhysicsWorld{
private:
	std::vector<Collider *> colliders;
	Vector2 gravity;

public:
	void SetGravity(const Vector2& g);
	void AddCollider(Collider *collider);
	void Update(float delta);
	bool CheckForCollision(Collider *collider1, Collider *collider2);
	void ResolveCollision(Collider *collider1, Collider *collider2);
	std::vector<Collider *> *GetColliders();
};

#endif