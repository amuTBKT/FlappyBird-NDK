#include "Sprite.h"

Sprite::Sprite(Texture* texture, char *name) : GameObject(name){
	width = texture->width;
	height = texture->height;

	mesh = MeshManager::GetInstance()->CreateQuad(Vector2(texture->width, texture->height));
	mesh->GetMaterial()->SetDiffuseTexture(texture); 

	frame.animationCounter = 0;
	frame.currentFrame.set(0, 1);
	frame.frames.set(1, 1);
}

void Sprite::SetNumFrames(int x, int y){
	frame.frames.set(x, y);
	mesh->GetMaterial()->SetDiffuseTextureTiling(1 / frame.frames.x, 1 / frame.frames.y);
}

void Sprite::Animate(float delta){
	frame.currentFrame.x += frame.animationCounter >= (frame.currentFrame.x) * (1.0 / frame.frames.x) ? 1.0 / frame.frames.x : 0;
	frame.animationCounter += delta;

	if ((frame.animationCounter) >= 1.0){
		frame.currentFrame.y -= 1.0 / frame.frames.y;
		frame.currentFrame.x = 0;
		frame.animationCounter = 0;
	}
	if (frame.currentFrame.y < 1.0 / frame.frames.y){
		frame.currentFrame.x = 0;
		frame.currentFrame.y = 1;
		frame.animationCounter = 0;
	}
	
	mesh->GetMaterial()->SetDiffuseTextureOffset(frame.currentFrame);
}

void Sprite::SetWidth(float w){
	SetScale(w / width, 1);
}

void Sprite::SetHeight(float h){
	SetScale(1, h / height);
}

void Sprite::SetScale(float x, float y){
	SetScale(Vector2(x, y));
}

void Sprite::SetScale(const Vector2& scl){
	if (collider != 0){
		collider->bounds.width *= scl.x / transform->scale.x;
		collider->bounds.height *= scl.y / transform->scale.y;
		collider->UpdateAABB();
	}
	width *= scl.x;// / transform->scale.x;
	height *= scl.y;// / transform->scale.y;
	transform->scale.x *= scl.x;
	transform->scale.y *= scl.y;
}

void Sprite::Scale(float x, float y){
	Scale(Vector2(x, y));
}

void Sprite::Scale(const Vector2& scl){
	SetScale(transform->scale.x * scl.x, transform->scale.y * scl.y);
}

float const Sprite::GetWidth(){
	return width;
}

float const Sprite::GetHeight(){
	return height;
}

Sprite::~Sprite(){
}

