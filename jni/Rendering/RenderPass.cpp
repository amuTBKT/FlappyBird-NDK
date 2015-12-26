#include "RenderPass.h"

RenderPass::RenderPass(int width, int height){
	Texture *texture = TextureManager::GetInstance()->CreateTexture(width, height, GL_LINEAR, GL_REPEAT);
	frameBuffer = new FrameBuffer(width, height, texture);
	shader = 0;
}

RenderPass::RenderPass(Shader *effect, int width, int height){
	Texture *texture = TextureManager::GetInstance()->CreateTexture(width, height, GL_LINEAR, GL_REPEAT);
	frameBuffer = new FrameBuffer(width, height, texture);
	shader = effect;
}

void RenderPass::UpdateShader(GLuint inputTexture, Matrix4 *cameraMatrix, Matrix4 *modelMatrix){
	shader->Begin();

	shader->SetUniformMatrix(shader->cameraProjViewMatrixLocation, *cameraMatrix);
	shader->SetUniformMatrix(shader->modelMatrixUniformLocation, *modelMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, inputTexture);
	shader->SetUniform1i("u_inputTexture", 0);

	if (additionalTexture != NULL && glGetUniformLocation(shader->GetProgram(), "u_extraTexture") != -1){
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, additionalTexture->GetTextureId());
		shader->SetUniform1i("u_extraTexture", 1);
	}
}

void RenderPass::EndShader(){
	shader->End();
}

FrameBuffer *RenderPass::GetFrameBuffer(){
	return frameBuffer;
}

void RenderPass::SetShader(Shader *effect){
	shader = effect;
}

Shader *RenderPass::GetShader(){
	return shader;
}

void RenderPass::SetAdditionalTexture(Texture *texture){
	additionalTexture = texture;
}

RenderPass::~RenderPass(){
	delete frameBuffer;
}
