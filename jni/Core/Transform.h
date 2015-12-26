#pragma once

#include "Matrix4.h"
#include "Vector2.h"

class Transform
{
public:
	Vector2 position, scale;
	float rotation;
	Matrix4 *modelMatrix;
	char *name;

	Transform();
	~Transform();

	void Translate(float dx, float dy);
	void Translate(const Vector2 &dp);
	void SetPosition(float x, float y);
	void SetPosition(const Vector2 &pos);

	void Scale(float dx, float dy);
	void Scale(const Vector2 &ds);
	void SetScale(float x, float y);
	void SetScale(const Vector2 &scl);

	void Rotate(float dr);
	void SetRotation(float r);
	
	void LookAt(const Vector2 &target);
	void SmoothFollow(const Vector2 &targetPosition, float targetRotation, float delta);

	Vector2 &GetForward() const;
	Vector2 &GetUp() const;
	
	Matrix4* GetModelMatrix();
};

