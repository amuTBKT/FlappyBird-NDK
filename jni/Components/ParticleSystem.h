#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include <GLES2/gl2.h>
#include <vector>

#include "../Core/Vector2.h"
#include "../Core/GameTime.h"
#include "../Core/MeshManager.h"
#include "../Core/ShaderManager.h"

struct Particle{
	Vector2 positon;
	Vector2 velocity;
	Vector2 startSize, endSize, size;
	COLOR startColor, endColor, color;
	float life, age, rotation;

	void Update(float deltaTime, Vector2 force){
		// increase age of particle
		age += deltaTime;

		// no need to do calculations if particle is already dead
		if (age <= life){
			// update rotation
			rotation += deltaTime * 50.0;

			// lerp color from start to end color
			color.r = startColor.r * (1 - age / life) + endColor.r * age / life;
			color.g = startColor.g * (1 - age / life) + endColor.g * age / life;
			color.b = startColor.b * (1 - age / life) + endColor.b * age / life;
			color.a = startColor.a * (1 - age / life) + endColor.a * age / life;

			// lerp size from start to end size
			size = startSize * (1.0 - age / life) + endSize * age / life;
			size.x = size.x < 0 ? 0 : size.x;
			size.y = size.y < 0 ? 0 : size.y;

			// update velocity
			velocity += force * deltaTime;

			// update position
			positon += velocity * deltaTime;
		}
	}
};

struct Emitter{
	std::vector<Particle*> activeParticles, inactiveParticles;

	// emitter postion
	Vector2 position;

	// emission area
	float emissionArea;

	// particle parameters
	COLOR startColor, endColor;
	float particleLife;
	Vector2 particleStartSize, particleEndSize;
	Vector2 initialVelocity;
	Vector2 acceleration;

	// some helper functions
	float GetRandomNumberBetween(float l, float h){
		return l + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (h - l)));
	}

	Vector2 GetRandomVector(){
		return Vector2(GetRandomNumberBetween(0, 1), GetRandomNumberBetween(0, 1));
	}

	Emitter(int maxP){
		emissionArea = 30;

		// falling downward
		acceleration.set(0, -200);

		initialVelocity.set(-150, -10);

		startColor = COLOR(1, 1, 1, 1);
		endColor = COLOR(1, 1, 1, 0.5);

		particleLife = 2;
		particleStartSize = particleEndSize = Vector2(20, 20);

		for (int i = 0; i < maxP; i++){
			inactiveParticles.push_back(new Particle());
		}
	}

	void Update(){
		float deltaTime = GameTime::GetInstance()->GetDeltaTime();

		for (int i = 0; i < activeParticles.size(); i++){
			Particle *particle = activeParticles[i];
			particle->Update(deltaTime, acceleration);
			if (particle->age >= particleLife){
				// remove particle from list of active particles
				activeParticles.erase(activeParticles.begin() + i);
				// set particle as inactive to reuse it later
				inactiveParticles.push_back(particle);
			}
		}
	}

	void Emit(int numberOfParticles){
		int particlesGenerated = 0;

		for (int i = 0; i < numberOfParticles; i++){
			// check if any particle is available for reuse (number of particles has not exceed maximum value)
			if (inactiveParticles.size() > 0){
				Particle *particle = inactiveParticles.at(i - particlesGenerated);

				particle->positon = position + GetRandomVector() * emissionArea;

				particle->velocity = initialVelocity;
				particle->velocity *= GetRandomNumberBetween(1, 2);

				particle->startColor = startColor;
				particle->endColor = endColor;

				particle->life = particleLife;
				particle->age = 0;

				particle->rotation = -180.0 + 180.0 * GetRandomNumberBetween(0, 2);

				particle->startSize = particleStartSize;
				particle->endSize = particleEndSize;

				// set particle as active
				inactiveParticles.erase(inactiveParticles.begin() + i - particlesGenerated++);
				activeParticles.push_back(particle);
			}
		}
	}

	~Emitter(){
		for (int i = 0; i < activeParticles.size(); i++){
			delete activeParticles.at(i);
		}
		activeParticles.clear();

		for (int i = 0; i < inactiveParticles.size(); i++){
			delete inactiveParticles.at(i);
		}
		inactiveParticles.clear();
	}
};

class ParticleSystem{
private:
	Emitter *emitter;
	Matrix4 *modelMatrix;
	Mesh *quad;
	Shader *shader;
	Texture *texture;
public:
	ParticleSystem(int maxParticles);
	~ParticleSystem();

	void Emit(int numParticles);
	void Update();
	void Render(Matrix4 *cameraMatrix);

	void SetTexture(Texture *texture);

	Emitter* GetEmitter();

	void Translate(float dx, float dy);
	void Translate(const Vector2 &dp);
	void SetPosition(float x, float y);
	void SetPosition(const Vector2 &pos);
};

#endif
