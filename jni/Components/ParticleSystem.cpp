#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int maxParticles){
	emitter = new Emitter(maxParticles);
	quad = MeshManager::GetInstance()->CreateQuad(Vector2(1, 1));
	modelMatrix = new Matrix4();
	shader = ShaderManager::GetInstance()->LoadShader("ParticleShader.vsh", "ParticleShader.fsh");
	texture = 0;
}

void ParticleSystem::Translate(float dx, float dy){
	emitter->position.x += dx;
	emitter->position.y += dy;
}

void ParticleSystem::Translate(const Vector2 &dp){
	Translate(dp.x, dp.y);
}

void ParticleSystem::SetPosition(float x, float y){
	emitter->position.set(x, y);
}

void ParticleSystem::SetPosition(const Vector2 &pos){
	SetPosition(pos.x, pos.y);
}

void ParticleSystem::SetTexture(Texture *tex){
	texture = tex;
}

Emitter* ParticleSystem::GetEmitter(){
	return emitter;
}

void ParticleSystem::Emit(int numParticles){
	emitter->Emit(numParticles);
}

void ParticleSystem::Update(){
	emitter->Update();
}

void ParticleSystem::Render(Matrix4 *cameraMatrix){
	shader->Begin();

	if (texture != 0){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureId());
		shader->SetUniform1i("u_diffuseTexture", 0);
	}

	for (int i = 0; i < emitter->activeParticles.size(); i++){
		Particle *particle = emitter->activeParticles.at(i);

		modelMatrix->InitScaling(particle->size.x, particle->size.y);
		modelMatrix->Rotate(particle->rotation);
		modelMatrix->Translate(particle->positon);

		shader->SetUniformMatrix(shader->cameraProjViewMatrixLocation, *cameraMatrix);
		shader->SetUniformMatrix(shader->modelMatrixUniformLocation, *modelMatrix);
		shader->SetUniform4f("u_color", particle->color.r, particle->color.g, particle->color.b, particle->color.a);

		quad->Render(shader, GL_TRIANGLES);

	}

	shader->End();
}

ParticleSystem::~ParticleSystem(){
	delete emitter;
}
