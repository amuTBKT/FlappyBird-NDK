#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height, Texture *attachment){
	textureWidth = width;
	textureHeight = height;
	texture = attachment;

	// we only need GL_COLOR_ATTACHMENT as depth testing is disabled for 2d game
	glGenFramebuffers(1, &framebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);

	glBindTexture(GL_TEXTURE_2D, attachment->GetTextureId());
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, attachment->GetTextureId(), 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Clear(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void FrameBuffer::UpdateTexture(){
//	glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->GetTextureId(), 0);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FrameBuffer::GetFrameBufferId(){
	return framebufferId;
}

Texture* FrameBuffer::GetTexture(){
	return texture;
}

FrameBuffer::~FrameBuffer(){
	glDeleteFramebuffers(1, &framebufferId);
	delete texture;
}
