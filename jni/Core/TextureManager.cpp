#include "TextureManager.h"

TextureManager* TextureManager::GetInstance(){
	static TextureManager* instance;

	if (instance == NULL){
		instance = new TextureManager();
	}

	return instance;
}

Texture* TextureManager::LoadTexture(const char* fileName, int filter, int wrapMode){
	// reuse texture, if already loaded
	std::hash_map<std::string, Texture*> ::const_iterator it;
	it = loadedTextures.find(fileName);
	if (it != loadedTextures.end()) {
		return it->second;
	}

	// create new texture
	Texture *texture = new Texture();

	loadedTextures.insert(std::pair<std::string, Texture*>(fileName, texture));

	// path specific to the operating system the game is running on
	std::string absolutePath = "Textures/";
	absolutePath.append(fileName);

	unsigned char *imageData;
	long imageSize;
	FileLoader::GetInstance()->LoadTextureData(&imageData, imageSize, absolutePath.c_str());

	unsigned char *image;
	lodepng::State state;

	unsigned error = lodepng_decode(&image, &texture->width, &texture->height, &state, imageData, imageSize);

	delete[] imageData;

	if (error != 0){
		image = 0;
	}

	texture->InitializeTexture(image, filter, wrapMode);

	delete[] image;

	return texture;
}

Texture* TextureManager::CreateTexture(int width, int height, int filter, int wrapMode){
	Texture *texture = new Texture();
	texture->width = width;
	texture->height = height;
	texture->InitializeTexture(0, filter, wrapMode);
	return texture;
}

void TextureManager::Dispose(){
	std::hash_map<std::string, Texture*> ::const_iterator it = loadedTextures.begin();
	while (it != loadedTextures.end()) {
		delete it->second;
		it++;
	}
	loadedTextures.clear();
}

