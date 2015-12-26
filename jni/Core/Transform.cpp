#include "Transform.h"

Transform::Transform()
{
	position = Vector2(0, 0);
	scale = Vector2(1, 1);
	rotation = 0;
	modelMatrix = new Matrix4();
}

void Transform::Translate(const Vector2 &dp){
	position += dp;
}

void Transform::Translate(float dx, float dy){
	Translate(Vector2(dx, dy));
}

void Transform::SetPosition(float x, float y){
	SetPosition(Vector2(x, y));
}

void Transform::SetPosition(const Vector2 &pos){
	position = pos;
}

void Transform::Scale(const Vector2 &ds){
	scale.x *= ds.x;
	scale.y *= ds.y;
}

void Transform::Scale(float dx, float dy){
	Scale(Vector2(dx, dy));
}

void Transform::SetScale(float x, float y){
	SetScale(Vector2 (x, y));
}

void Transform::SetScale(const Vector2 &scl){
	Scale(scl.x / scale.x, scl.y / scale.y);
}

void Transform::Rotate(float dr){
	rotation += dr;
}

void Transform::SetRotation(float r){
	rotation = r;
}

Vector2 &Transform::GetForward() const{
	Vector2 forward(1, 0);
	forward.rotate(rotation);
	return forward;
}

Vector2 &Transform::GetUp() const{
	Vector2 up(0, 1);
	up.rotate(rotation);
	return up;
}

void Transform::LookAt(const Vector2 &target){
	float angle = position.angleBetween(target);
	SetRotation(angle);
}

void Transform::SmoothFollow(const Vector2 &targetPosition, float targetRotation, float delta){

}

Matrix4* Transform::GetModelMatrix(){
	modelMatrix->InitScaling(scale);
	modelMatrix->Rotate(rotation);
	modelMatrix->SetTranslation(position);
	return modelMatrix;
}

Transform::~Transform(){
	delete modelMatrix;
}
