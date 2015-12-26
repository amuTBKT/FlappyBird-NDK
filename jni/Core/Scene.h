#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include "Input.h"
#include "AudioManager.h"
#include "../Components/Camera.h"
#include "../Rendering/RenderingEngine.h"
#include "../Physics/PhysicsWorld.h"
#include "../Components/GameObjectGroup.h"
#include "../Components/Sprite.h"
#include "../Components/ParticleSystem.h"
#include "../Rendering/ShapeRenderer.h"

class Scene{
protected:
	std::vector<GameObject*> gameObjects;
	std::vector<ParticleSystem*> particleSystems;
	Camera *mainCamera;
	PhysicsWorld *world;
	ShapeRenderer *shapeRenderer;
public:
	virtual void Initialize()			= 0;
	virtual void Update(float delta)    = 0;
	
	virtual void Pause(){}
	virtual void Resume(){}

	virtual void TouchBegan(){}
	virtual void TouchMove(){}
	virtual void TouchEnd(){}

	void Dispose(){
		for (int i = 0; i < gameObjects.size(); i++){
			delete gameObjects[i];
			gameObjects[i] = 0;
		}
		gameObjects.clear();

		for (int i = 0; i < particleSystems.size(); i++){
			delete particleSystems[i];
			particleSystems[i] = 0;
		}
		particleSystems.clear();

		delete mainCamera;
	}

	void AddChild(GameObject *child){
		gameObjects.push_back(child);
	}

	void AddParticleSystem(ParticleSystem *system){
		particleSystems.push_back(system);
	}

	std::vector<GameObject*> &GetChildren(){
		return gameObjects;
	}

	Camera* GetMainCamera(){
		return mainCamera;
	}

	void UpdateGameObjects(){
		for (int i = 0; i < gameObjects.size(); i++){
			if (gameObjects[i]->isActive){
				gameObjects[i]->Update();
			}
		}

		for (int i = 0; i < particleSystems.size(); i++){
			particleSystems[i]->Update();
		}
	}

	void Render(){
		RenderingEngine *renderer = RenderingEngine::GetInstance();

		renderer->BindFrameBufferToScreen(renderer->GetScreenFrameBuffer());
		renderer->GetScreenFrameBuffer()->Clear(0, 0, 0, 1);

		// set camera matrix for rendering game objects
		renderer->SetCameraMatrix(mainCamera->GetCameraMatrix());

		// start alpha blending
		renderer->StartBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// first pass
		for (int i = 0; i < gameObjects.size(); i++){
			if (!gameObjects[i]->isHidden){
				renderer->RenderGameObject(gameObjects[i]);
			}
		}
		for (int i = 0; i < particleSystems.size(); i++){
			particleSystems[i]->Render(mainCamera->GetCameraMatrix());
		}

		// additional passes (any effect if added to pipeline)
		renderer->RenderAdditionalPasses();

		// stop alpha blending
		renderer->StopBlending();

//		if (shapeRenderer != 0){
//			shapeRenderer->Render(&mainCamera->GetCameraMatrix());
//		}
	}
};

#endif

