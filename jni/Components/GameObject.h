#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../Physics/Collider.h"
#include "../rendering/Mesh.h"

class GameObject {
protected:
	Transform *transform;
public:
	/*
	* name      : gameObject name
	* transform : handles translation, rotation and scaling
	* mesh		: rendering component (visual element)
	* children  : children gameObjects
	* parent	: parent gameOBject
	* isActive	: do we need to update gameObject
	* isHidden  : do we need to render gameObject
	* collider  : physics component
	*/
	char *name;
	Mesh *mesh;
	std::vector<GameObject *> children;
	GameObject *parent;
	bool isActive;
	bool isHidden;
	Collider *collider;

	GameObject(char *gobjName);
	GameObject(const GameObject&);
	~GameObject();

	void SetMesh(Mesh *mesh);
	Mesh* GetMesh();

	// transform functions
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

	const Vector2 GetPosition();
	const Vector2 GetScale();
	const float GetRotation();

	// get model matrix for passing to shader
	Matrix4* GetModelMatrix();

	// add collider
	void AddCollider(float width, float height);
	// get collider
	Collider *GetCollider();
	// called when collision occurs with another collider
	virtual void OnCollision(Collider *collider);

	// updates gameObject
	virtual void Update();
};
#endif
