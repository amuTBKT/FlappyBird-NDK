#ifndef RENDER_PASS_H_
#define RENDER_PASS_H_

#include <GLES2/gl2.h>
#include "Shader.h"
#include "FrameBuffer.h"
#include "../Core/TextureManager.h"

class RenderPass{
protected:
	/*
	*	framebuffer			: framebuffer to store rendered scene
	*	shader				: shader to produce required effect
	*	additionalTexture	: texture if required beside the inputTexture (like normal map, noise etc)
	*/
	FrameBuffer *frameBuffer;
	Shader *shader;
	Texture *additionalTexture;
public:
	RenderPass(Shader* effect, int width, int height);
	RenderPass(int width, int height);
	~RenderPass();

	// set additonalTexture if required
	void SetAdditionalTexture(Texture *texture);
	// update shader uniforms
	void UpdateShader(GLuint inputTexture, Matrix4 *cameraMatrix, Matrix4 *modelMatrix);
	// update extra uniforms (if added beside default uniforms)
	virtual void UpdateExtraUniforms() = 0;
	// end current shader
	void EndShader();

	FrameBuffer *GetFrameBuffer();
	void SetShader(Shader *effect);
	Shader *GetShader();
};

#endif
