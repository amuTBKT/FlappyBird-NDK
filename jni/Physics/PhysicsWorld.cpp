#include "PhysicsWorld.h"

#include <iostream>

void PhysicsWorld::SetGravity(const Vector2& g){
	gravity = g;
}

void PhysicsWorld::AddCollider(Collider *collider){
	colliders.push_back(collider);
}

void PhysicsWorld::Update(float delta){
	// update position and velocity of colliders
	for (int i = 0; i < colliders.size(); i++){
		Collider *collider = colliders[i];
		// apply gravity to collider
		if (collider->affectedByGravity){
			collider->ApplyForce(gravity * delta);
		}
		// update velocity (apply forces) and position
		collider->Update(delta);
	}

	// check for collisions
	for (int i = 0; i < colliders.size(); i++){
		Collider *collider1 = colliders[i];
		for (int j = 0; j < colliders.size(); j++){
			Collider *collider2 = colliders[j];
			if (collider1 != collider2){
				if (CheckForCollision(collider1, collider2)){
					// if collided, then resolve collision
					ResolveCollision(collider1, collider2);
				}
			}
		}
	}

}

bool PhysicsWorld::CheckForCollision(Collider *collider1, Collider *collider2){
	return collider1->TestAABB(*collider2);
}

// calls OnCollision function on parent gameObject
void PhysicsWorld::ResolveCollision(Collider *collider1, Collider *collider2){
	GameObject *gameObj1 = (GameObject*)collider1->parent;
	gameObj1->OnCollision(collider2);

	GameObject *gameObj2 = (GameObject*)collider2->parent;
	gameObj2->OnCollision(collider1);
}

std::vector<Collider *> *PhysicsWorld::GetColliders(){
	return &colliders;
}

