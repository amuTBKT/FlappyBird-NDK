#include "Matrix4.h"

Matrix4::Matrix4()
{
	_m = new float[16];
	InitializeIdentity();
}

Matrix4::Matrix4(const Matrix4& mat) {
	_m = new float[16];
	std::memcpy((void*)_m, mat._m, 16 * sizeof(float));
}

void Matrix4::InitializeIdentity(){
	std::memset((void*)_m, 0, 16 * sizeof(float));
	_m[0] = _m[5] = _m[10] = _m[15] = 1;
}

void Matrix4::InitPerspective(float fov, float aspectRatio, float zNear, float zFar){
	float tanHalfFOV = tanf(fov / 2);
	float zRange = zNear - zFar;

	set(0, 0, 1.0 / (tanHalfFOV * aspectRatio));	set(0, 1, 0);					set(0, 2, 0);							set(0, 3, 0);
	set(1, 0, 0);									set(1, 1, 1.0 / tanHalfFOV);	set(1, 2, 0);							set(1, 3, 0);
	set(2, 0, 0);									set(2, 1, 0);					set(2, 2, (-zNear - zFar) / zRange);	set(2, 3, 2.0 * zFar * zNear / zRange);
	set(3, 0, 0);									set(3, 1, 0);					set(3, 2, 1.0);							set(3, 3, 0);
}

void Matrix4::InitOrthographic(float left, float right, float bottom, float top, float near, float far){
	float width = right - left;
	float height = top - bottom;
	float depth = far - near;

	set(0, 0, 2.0 / width);		set(0, 1, 0);				set(0, 2, 0);				set(0, 3, -(right + left) / width);
	set(1, 0, 0);				set(1, 1, 2.0 / height);	set(1, 2, 0);				set(1, 3, -(top + bottom) / height);
	set(2, 0, 0);				set(2, 1, 0);				set(2, 2, -2.0 / depth);	set(2, 3, -(far + near) / depth);
	set(3, 0, 0);				set(3, 1, 0);				set(3, 2, 0);				set(3, 3, 1.0);
}

void Matrix4::InitView(){
	InitializeIdentity();

	// set forward = (0, 0, -1)
	set(2, 2, -1.0);
}

void Matrix4::InitTranslation(float x, float y){
	InitializeIdentity();
	SetTranslation(x, y);
}

void Matrix4::InitTranslation(const Vector2 &pos){
	InitializeIdentity();
	SetTranslation(pos);
}

void Matrix4::InitScaling(float x, float y){
	InitializeIdentity();
	SetScale(x, y);
}

void Matrix4::InitScaling(const Vector2 &scl){
	InitializeIdentity();
	SetScale(scl);
}

void Matrix4::InitRotation(float r){
	InitializeIdentity();
	SetRotation(r);
}

void Matrix4::SetTranslation(float x, float y){
	set(0, 3, x);
	set(1, 3, y);
}

void Matrix4::SetTranslation(const Vector2 &pos){
	SetTranslation(pos.x, pos.y);
}

void Matrix4::Translate(float dx, float dy){
	set(0, 3, get(0, 3) + dx);
	set(1, 3, get(1, 3) + dy);
}

void Matrix4::Translate(const Vector2 &dp){
	Translate(dp.x, dp.y);
}

void Matrix4::SetScale(float x, float y){
	set(0, 0, x);
	set(1, 1, y);
}

void Matrix4::SetScale(const Vector2 &scl){
	SetScale(scl.x, scl.y);
}

void Matrix4::Scale(float dx, float dy){
	set(0, 0, get(0, 0) * dx);
	set(1, 1, get(1, 1) * dy);
}

void Matrix4::Scale(const Vector2 &ds){
	Scale(ds.x, ds.y);
}

void Matrix4::SetRotation(float r){
	float currentRotation = asinf(get(1, 0)) * 180 / M_PI;
	Rotate(r - currentRotation);
}

void Matrix4::Rotate(float dr){
	// for better performance
	static Matrix4 *rotMat;
	if (rotMat == NULL){
		rotMat = new Matrix4();
	}

	rotMat->InitializeIdentity();
	rotMat->set(0, 0, cosf(dr * M_PI / 180));
	rotMat->set(0, 1, -sinf(dr * M_PI / 180));
	rotMat->set(1, 0, sinf(dr * M_PI / 180));
	rotMat->set(1, 1, cosf(dr * M_PI / 180));

	*rotMat *= *this;
	*this = *rotMat;
}

Matrix4& Matrix4::operator= (Matrix4 mat){
	std::memcpy((void*)_m, mat._m, 16 * sizeof(16));

	return *this;
}

Matrix4& Matrix4::operator*(Matrix4 matrix){
	// for better performance
	static Matrix4 *mat;
	if (mat == NULL){
		mat = new Matrix4();
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat->set(i, j, get(i, 0) * matrix.get(0, j) +
				get(i, 1) * matrix.get(1, j) +
				get(i, 2) * matrix.get(2, j) +
				get(i, 3) * matrix.get(3, j));
		}
	}

	return *mat;
}

Matrix4& Matrix4::operator*=(Matrix4 matrix){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			set(i, j,	get(i, 0) * matrix.get(0, j) +
				get(i, 1) * matrix.get(1, j) +
				get(i, 2) * matrix.get(2, j) +
				get(i, 3) * matrix.get(3, j));
		}
	}

	return *this;
}

void Matrix4::set(int x, int y, float v){
	_m[x + y * 4] = v;
}

float Matrix4::get(int x, int y) const{
	return _m[x + y * 4];
}

float* Matrix4::GetData() const{
	return _m;
}

Matrix4::~Matrix4() {
	delete[] _m;
}
