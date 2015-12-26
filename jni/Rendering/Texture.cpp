#include "Texture.h"

Texture::Texture(){
	textureId = -1;
}

bool Texture::InitializeTexture(unsigned char *pixelData, int filter, int mode){
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0);

	return glIsTexture(textureId);
}

void Texture::SetTextureId(GLuint texId){
	textureId = texId;
}

GLuint Texture::GetTextureId(){
	return textureId;
}

Texture::~Texture(){
	glDeleteTextures(1, &textureId);
	textureId = -1;
}
