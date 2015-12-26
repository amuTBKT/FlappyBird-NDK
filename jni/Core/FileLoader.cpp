#include "FileLoader.h"

FileLoader* FileLoader::GetInstance(){

	static FileLoader *instance;

	if (instance == 0){
		instance = new FileLoader();
	}

	return instance;
}

void FileLoader::Initialize(AAssetManager *manager){
	assetManager = manager;
}

int FileLoader::LoadSFXData(const char *fileName, off_t &start, off_t &length){
	AAsset* asset = AAssetManager_open(assetManager, fileName, AASSET_MODE_UNKNOWN);
	if (asset == NULL) {
		ELOG("file not found %s", fileName);
		std::terminate();
	}
	int fd = AAsset_openFileDescriptor(asset, &start, &length);
	AAsset_close(asset);
	return fd;
}

void FileLoader::LoadTextureData(unsigned char **data, long &size, const char *fileName){
	AAsset* asset = AAssetManager_open(assetManager, fileName, AASSET_MODE_UNKNOWN);
	if (asset == NULL) {
		ELOG("file not found %s", fileName);
		std::terminate();
	}
	size = AAsset_getLength(asset);
	*data = (unsigned char*) malloc (sizeof(unsigned char) * size);
	AAsset_read (asset, *data, size);
	AAsset_close(asset);
}

void FileLoader::LoadFile(char **data, long &size, const char *fileName){
	AAsset* asset = AAssetManager_open(assetManager, fileName, AASSET_MODE_UNKNOWN);
	if (asset == NULL) {
		ELOG("file not found %s", fileName);
		std::terminate();
	}
	size = AAsset_getLength(asset);
	*data = (char*) malloc (sizeof(char)*size);
	AAsset_read (asset, *data, size);
	AAsset_close(asset);
}

AAssetManager* FileLoader::GetAAssetManager() const{
	return assetManager;
}
