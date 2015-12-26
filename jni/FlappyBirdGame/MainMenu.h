#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include "../Core/Scene.h"

#include "../Rendering/PostProcessEffects/GrayscalePass.h"
#include "../Rendering/PostProcessEffects/VignettePass.h"
#include "../Rendering/PostProcessEffects/ClassicTheme.h"

class MainMenu : public Scene
{
public:	
	void Initialize();
	void Update(float delta);
	void TouchBegan();

	float delta;
	float elapsedTime;

	Sprite *logo, *background, *playButton;
};

#endif
