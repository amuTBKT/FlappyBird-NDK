#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GLES2/gl2.h>
#include <vector>

class Texture
{
private:
	GLuint textureId;
public:
	unsigned int width, height;

	Texture();
	~Texture();

	void SetTextureId(GLuint texId);
	GLuint GetTextureId();

	bool InitializeTexture(unsigned char *pixelData, int filter, int mode);
};

#endif
