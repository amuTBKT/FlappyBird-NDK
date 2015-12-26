#ifndef FRAME_BUFFER_H_
#define FRAME_BUFFER_H_

#include <GLES2/gl2.h>
#include <iostream>
#include "Texture.h"

class FrameBuffer{
private:
	/*
	* framebufferId : opengl id for framebuffer
	* texture		: texture in which scene gets rendered
	*/
	GLuint framebufferId;
	Texture *texture;
public:
	// width and height of framebuffer texture
	unsigned int textureWidth, textureHeight;

	FrameBuffer(int width, int height, Texture *attachment);
	~FrameBuffer();
	
	// clears framebuffer
	void Clear(float r, float g, float b, float a);
	
	// updates framebuffer texture
	void UpdateTexture();
	
	// returns opengl id for binding framebuffer
	GLuint GetFrameBufferId();

	// returns framebuffer texture
	Texture* GetTexture();
};

#endif
