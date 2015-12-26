#include "Vector2.h"

//// constructors ////
Vector2::Vector2(float m = 0, float n = 0):x(m), y(n){}
Vector2::Vector2():x(0), y(0){}
Vector2::Vector2(const Vector2& v){ // copy constructor
	x = v.x;
	y = v.y;
}
//////////////////////

//// getters and setters ////
void Vector2::set(float m, float n){
	x = m;
	y = n;
}

void Vector2::setX(float m){
	x = m;
}

void Vector2::setY(float n){
	y = n;
}

void Vector2::setLength(float length){
	float angle = getAngle() * M_PI / 180;
	x = cosf(angle) * length;
	y = sinf(angle) * length;
}

void Vector2::setAngle(float angle){
	float length = getLength();
	angle *= M_PI / 180;
	x = cosf(angle) * length;
	y = sinf(angle) * length;
}

float Vector2::getX(){
	return x;
}

float Vector2::getY(){
	return y;
}

float Vector2::getLength(){
	return sqrtf(getLengthSQR());
}

float Vector2::getLengthSQR(){
	return *this * *this;
}

float Vector2::getAngle(){
	return atan2(y, x) * 180 / M_PI;
}
/////////////////////////////

//// methods ////
Vector2& Vector2::operator =(const Vector2& v){
	x = v.x;
	y = v.y;
	return *this;
}

Vector2 Vector2::operator +(const Vector2& v){
	return Vector2(x + v.x, y + v.y);
}

Vector2& Vector2::operator +=(const Vector2& v){
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator -(const Vector2& v){
	return Vector2(x - v.x, y - v.y);
}

Vector2& Vector2::operator -=(const Vector2& v){
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator *(float c){
	return Vector2(x * c, y * c);
}

Vector2& Vector2::operator *=(float c){
	x *= c;
	y *= c;
	return *this;
}

Vector2 Vector2::operator /(float c){
	//if (c == 0) throw (1 / c);
	return Vector2(x / c, y / c);
}

Vector2& Vector2::operator /=(float c){
	x /= c;
	y /= c;
	return *this;
}

bool Vector2::operator ==(const Vector2& v){
	return (x == v.x && y == v.y);
}

bool Vector2::operator !=(const Vector2& v){
	return (x != v.x && y != v.y);
}

float Vector2::operator *(const Vector2& v){
	return (x * v.x + y * v.y);
}

void Vector2::truncate(float limit){
	float length = getLength();
	length = fminf(length, limit);
	setLength(length);
}

void Vector2::reverse(){
	*this *= -1;
}

void Vector2::rotate(float dA){
	float angle = getAngle();
	setAngle(angle + dA);
}

//Vector2 Vector2::reflect(const Vector2& normal){
//	Vector2 tmp(normal);
//	tmp.normalize();
//	tmp = *this - tmp * 2 * (tmp * *this);
//	tmp.normalize();
//	return tmp;
//}

void Vector2::normalize(){
	if (getLength() == 0){
		x = 1;
		y = 0;
	}
	else {
		*this /= getLength();
	}
}

bool Vector2::isNormalized(){
	return getLength() == 1;
}

float Vector2::angleBetween(const Vector2 v){
	Vector2 tmp1 = Vector2(*this);
	tmp1.normalize();
	Vector2 tmp2 = Vector2(v);
	tmp2.normalize();
	return acosf(tmp1 * tmp2) * 180 / M_PI;
}

float Vector2::distanceBetween(const Vector2 v){
	Vector2 tmp = Vector2(*this);
	tmp -= v;
	return tmp.getLength();
}
/////////////////
