#ifndef COLLIDER_H_
#define COLLIDER_H_

#include <stack>
#include "../Core/Transform.h"

/*

			------- width -------
		(minX, maxY)		(maxX, maxY)
	  |		+--------------------+
	  |		|					 |
	  |		|				     |
	height	|	     AABB		 |
	  |		|					 |
	  |		|					 |
  	  |		+--------------------+
		(minX, minY)		(maxX, minY)
*/
struct aabb{
	float minX, minY, maxX, maxY;
	float width, height;
};

class Collider {
private:
	// forces applied to collider are stored in this vector (cleared very frame after updating collider velocity)
	std::stack<Vector2> forces;
public:
	Collider();
	virtual ~Collider();

	// pointer to parent gameObject transform to update position
	Transform *transform;
	// (void*) to parent gameObject (parentGameObject = (GameObject*)parent) 
	void *parent;

	/*
	* position : position of collider (initialized when added to gameObject)
	* offest   : gameObject.position = position + offset
	* velocity : velocity of collider
	* bounds   : collider bounds, used or AABB collision detection
	*/
	Vector2 position;
	Vector2 offset;
	Vector2 velocity;
	aabb bounds;
	bool isActive, affectedByGravity;
	
	// updates aabb, both bounds and width and height
	void UpdateAABB();

	void Translate(const Vector2&);
	void Translate(float, float);

	// check if a point is within the bounds
	bool InBounds(const Vector2&);
	bool InBounds(float, float);
	// check for collision with another collider (AABB vs AABB collision detection)
	bool TestAABB(const Collider&);
	bool TestSphere(const Collider&);

	// apply forces and update position
	void Update(float delta);
	// apply force to collider
	void ApplyForce(const Vector2 &force);
	// apply forces (velocity += forces)
	void UpdateForces();

	void Disable();
	void Enable();
};

#endif
