#ifndef NUMBER_RENDERER_H_
#define NUMBER_RENDERER_H_

#include "../Core/TextureManager.h"
#include "../Components/Sprite.h"
#include "../Components/GameObjectGroup.h"

class NumberRenderer : public GameObjectGroup{
public:
	int width, height;
	NumberRenderer(char *name);
	~NumberRenderer();

	void UpdateNumber(int number);
};

#endif
