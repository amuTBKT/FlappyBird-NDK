#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vector2.h"
#include <memory>

class Matrix4
{
private:
	float *_m;
public:
	Matrix4();
	Matrix4(const Matrix4 &mat);

	~Matrix4();

	void InitializeIdentity();
	void InitTranslation(float x, float y);
	void InitTranslation(const Vector2 &pos);
	void InitScaling(float x, float y);
	void InitScaling(const Vector2 &scl);
	void InitRotation(float r);
	void InitPerspective(float minimumFieldOfView, float aspectRatio, float nearPlane, float farPlane);
	void InitOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
	void InitView();

	void SetTranslation(float x, float y);
	void SetTranslation(const Vector2 &pos);
	void Translate(float dx, float dy);
	void Translate(const Vector2 &dp);

	void SetScale(float x, float y);
	void SetScale(const Vector2 &scl);
	void Scale(float dx, float dy);
	void Scale(const Vector2 &ds);

	void SetRotation(float r);
	void Rotate(float dr);
	
	Matrix4& operator* (Matrix4 mat);
	Matrix4& operator*= (Matrix4 mat);
	Matrix4& operator= (Matrix4 mat);

	void set(int x, int y, float v);
	float get(int x, int y) const;

	float* GetData() const;

//	Vector2& GetTranslation() const;
//	Vector2& GetScale() const;
};

#endif

