#ifndef FILE_LOADER_H_
#define FILE_LOADER_H_

#include <iostream>
#include <android/asset_manager.h>
#include <malloc.h>
#include "Logger.h"

class FileLoader{
private:
	AAssetManager *assetManager;

public:
	static FileLoader *GetInstance();

	void Initialize(AAssetManager *manager);

	void LoadFile(char **data, long &size, const char *fileName);
	void LoadTextureData(unsigned char **data, long &size, const char *fileName);
	int LoadSFXData(const char *fileName, off_t &start, off_t &length);

	AAssetManager *GetAAssetManager() const;

};

#endif
