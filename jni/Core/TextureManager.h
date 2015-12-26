#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <hash_map>
#include <string>
#include "FileLoader.h"
#include "../Core/lodepng.h"
#include "../Rendering/Texture.h"

class TextureManager{
private:
	std::hash_map<std::string, Texture *> loadedTextures;
public:
	static TextureManager* GetInstance();
	
	// load texture from file, TextureManager handles deleting these textures
	Texture* LoadTexture(const char* fileName, int filter, int wrapMode);

	// create texture, TextureManager does not handles these textures
	Texture* CreateTexture(int width, int height, int filter, int wrapMode);

	void Dispose();
};

#endif
