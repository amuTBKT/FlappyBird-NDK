#include "GameObject.h"

GameObject::GameObject(char *gobjName) {
	name = gobjName;
	transform = new Transform();
	mesh = 0;
	transform->name = name;
	isHidden = false;
	isActive = true;
	collider = 0;
}

GameObject::GameObject(const GameObject& g) {
	name = g.name;
	transform = g.transform;
	mesh = g.mesh;
	collider = g.collider;
	isHidden = g.isHidden;
	isActive = g.isActive;
}

void GameObject::Update(){
}

void GameObject::SetMesh(Mesh *msh){
	mesh = msh;
}

Mesh *GameObject::GetMesh(){
	return mesh;
}

void GameObject::SetPosition(float x, float y){
	SetPosition(Vector2(x, y));
}

void GameObject::SetPosition(const Vector2& pos){
	transform->position = pos;
	if (collider != 0){
		collider->position = pos;
		collider->UpdateAABB();
	}
}

void GameObject::Translate(float x, float y){
	Translate(Vector2(x, y));
}

void GameObject::Translate(const Vector2& dp){
	transform->position += dp;
	if (collider != 0){
		collider->position += dp;
		collider->UpdateAABB();
	}
}

void GameObject::SetScale(float x, float y){
	SetScale(Vector2(x, y));
}

void GameObject::SetScale(const Vector2& scl){
	if (collider != 0){
		collider->bounds.width *= scl.x / transform->scale.x;
		collider->bounds.height *= scl.y / transform->scale.y;
		collider->UpdateAABB();
	}
	transform->scale = scl;
}

void GameObject::Scale(float x, float y){
	SetScale(Vector2(x, y));
}

void GameObject::Scale(const Vector2& scl){
	transform->scale.x *= scl.x;
	transform->scale.y *= scl.y;
	if (collider != 0){
		collider->bounds.width *= scl.x;
		collider->bounds.height *= scl.y;
		collider->UpdateAABB();
	}
}

void GameObject::SetRotation(float r){
	transform->SetRotation(r);
}

void GameObject::Rotate(float dr){
	transform->Rotate(dr);
}

const Vector2 GameObject::GetPosition(){
	return transform->position;
}

const Vector2 GameObject::GetScale(){
	return transform->scale;
}

const float GameObject::GetRotation(){
	return transform->rotation;
}

Matrix4* GameObject::GetModelMatrix(){
	return transform->GetModelMatrix();
}

void GameObject::AddCollider(float width, float height){
	collider = new Collider();
	collider->position = transform->position;
	collider->transform = transform;
	collider->bounds.width = width;
	collider->bounds.height = height;
	collider->UpdateAABB();

	collider->parent = this;
}

void GameObject::OnCollision(Collider *collider){
}

Collider* GameObject::GetCollider(){
	return collider;
}

GameObject::~GameObject() {
	delete transform;
	mesh = 0;
	if (collider != 0){
		delete collider;
	}
}

