#include "GameObjectGroup.h"

GameObjectGroup::GameObjectGroup(char *name) : GameObject(name){
	// no need to render group
	isHidden = true;
}

void GameObjectGroup::SetPosition(float x, float y){
	SetPosition(Vector2(x, y));
}

void GameObjectGroup::SetPosition(const Vector2& pos){
	Vector2 dp = pos;
	dp -= GetPosition();

	GameObject::SetPosition(pos);

	// set position of objects
	for (int i = 0; i < objects.size(); i++){
		objects[i]->Translate(dp);
	}
}

void GameObjectGroup::Translate(float x, float y){
	Translate(Vector2(x, y));
}

void GameObjectGroup::Translate(const Vector2& dp){
	GameObject::Translate(dp);

	// translate objects
	for (int i = 0; i < objects.size(); i++){
		objects[i]->Translate(dp);
	}
}

void GameObjectGroup::SetScale(float x, float y){
	SetScale(Vector2(x, y));
}

void GameObjectGroup::SetScale(const Vector2& scl){
	Vector2 ds = scl;
	ds.x /= GetScale().x;
	ds.y /= GetScale().y;

	Scale(ds);

	//GameObject::SetScale(scl);

	//// set scale of objects
	//for (int i = 0; i < objects.size(); i++){
	//	objects[i]->Scale(ds);
	//	Vector2 relPos = objects[i]->GetPosition();
	//	relPos -= GetPosition();
	//	objects[i]->SetPosition(GetPosition().x + relPos.x * ds.x, GetPosition().y + relPos.y * ds.y);
	//}
}

void GameObjectGroup::Scale(float x, float y){
	Scale(Vector2(x, y));
}

void GameObjectGroup::Scale(const Vector2& scl){
	GameObject::Scale(scl);

	// scale objects
	for (int i = 0; i < objects.size(); i++){
		objects[i]->Scale(scl);
		Vector2 relPos = objects[i]->GetPosition();
		relPos -= GetPosition();
		objects[i]->SetPosition(GetPosition().x + relPos.x * scl.x, GetPosition().y + relPos.y * scl.y);
	}
}

void GameObjectGroup::SetRotation(float r){
	float dr = r - GetRotation();
	Rotate(r);
}

void GameObjectGroup::Rotate(float dr){
	GameObject::Rotate(dr);

	// rotate objects
	for (int i = 0; i < objects.size(); i++){
		objects[i]->Rotate(dr);
		Vector2 relPos = objects[i]->GetPosition();
		relPos -= GetPosition();
		relPos.rotate(dr);
		objects[i]->SetPosition(GetPosition().x + relPos.x, GetPosition().y + relPos.y);
	}
}

void GameObjectGroup::Update(){
}

void GameObjectGroup::AddGameObject(GameObject *object){
	objects.push_back(object);
}

GameObject* GameObjectGroup::GetGameObjectAtIndex(int i){
	int index = i >= objects.size() ? objects.size() - 1 : i;
	index = i < 0 ? 0 : i;

	return objects.at(index);
}

std::vector<GameObject *>* GameObjectGroup::GetObjects(){
	return &objects;
}

GameObjectGroup::~GameObjectGroup(){

}

