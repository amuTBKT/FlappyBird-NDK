#ifndef GAMEOBJECT_GROUP_H_
#define GAMEOBJECT_GROUP_H_

#include <vector>
#include "GameObject.h"

class GameObjectGroup : public GameObject{
private:
	std::vector<GameObject *> objects;
public:
	GameObjectGroup(char *name);
	~GameObjectGroup();

	void AddGameObject(GameObject *object);
	GameObject *GetGameObjectAtIndex(int i);
	std::vector<GameObject *> *GetObjects();

	void SetPosition(float x, float y);
	void SetPosition(const Vector2 &pos);
	void Translate(float x, float y);
	void Translate(const Vector2 &dp);
	void SetScale(float x, float y);
	void SetScale(const Vector2 &scl);
	void Scale(float x, float y);
	void Scale(const Vector2 &scl);
	void SetRotation(float r);
	void Rotate(float dr);

	void Update();
};
#endif
