#include "Collider.h"

Collider::Collider() {
	isActive = true;
	affectedByGravity = true;
}

void Collider::UpdateAABB(){
	bounds.minX = position.x - bounds.width / 2;
	bounds.maxX = position.x + bounds.width / 2;
	bounds.minY = position.y - bounds.height / 2;
	bounds.maxY = position.y + bounds.height / 2;
}

void Collider::Translate(float dx, float dy){
	Translate(Vector2(dx, dy));
}

void Collider::Translate(const Vector2& dV){
	position += dV;
}

bool Collider::InBounds(const Vector2& point){
	return ((point.x >= bounds.minX && point.x <= bounds.maxX) & (point.y >= bounds.minY && point.y <= bounds.maxY));
}

bool Collider::InBounds(float x, float y){
	return InBounds(Vector2(x, y));
}

bool Collider::TestAABB(const Collider& collider){
	if (bounds.maxX < collider.bounds.minX) return false;
	if (bounds.minX > collider.bounds.maxX) return false;
	if (bounds.maxY < collider.bounds.minY) return false;
	if (bounds.minY > collider.bounds.maxY) return false;

	// there is an overlap
	return true;
}

bool Collider::TestSphere(const Collider& collider){
	
	return false;
}

void Collider::Update(float delta){
	// apply forces (update velocity)
	UpdateForces();

	// update position
	position += velocity * delta;

	// update parent
	transform->SetPosition(position + offset);

	// update bounds
	UpdateAABB();
}

void Collider::ApplyForce(const Vector2 &force){
	// add force to be update later in Update()
	forces.push(force);
}

void Collider::UpdateForces(){
	while (!forces.empty()){
		velocity += forces.top();
		forces.pop();
	}
}

void Collider::Enable(){
	isActive = true;
}

void Collider::Disable(){
	isActive = false;
}

Collider::~Collider() {
}

