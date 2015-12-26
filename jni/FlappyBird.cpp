#include <jni.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "Core/FileLoader.h"
#include "Core/Game.h"

#include "FlappyBirdGame/MainMenu.h"

static Game *game = 0;
static bool init = false;

extern "C"{

JNIEXPORT void JNICALL Java_com_amu_flappybird_NativeRenderer_nativeOnStart(JNIEnv *jenv, jobject obj){
	// get instance for singleton Game class
	game = Game::GetInstance();
}

JNIEXPORT void JNICALL Java_com_amu_flappybird_NativeRenderer_nativeOnSurfaceCreated(JNIEnv *jenv, jobject obj, int width, int height){
	if (!init){
		init = true;

		// initialize game and its  components (resource loader, audio, rendering)
		game->Initialize(width, height);

		// set current scene to main menu
		game->ChangeScene(new MainMenu());
	}
}

JNIEXPORT void JNICALL Java_com_amu_flappybird_NativeRenderer_nativeOnRender(JNIEnv *jenv, jobject obj){
	if (game){
		// update game
		game->Update();

		// render game
		game->Render();
	}
}

JNIEXPORT void JNICALL Java_com_amu_flappybird_NativeRenderer_nativeOnTouch(JNIEnv *jenv, jobject obj, int x, int y, int touchDown){
	if (touchDown == 1){
		// touch down
		game->TouchBegan(x, RenderingEngine::GetInstance()->SCREEN_HEIGHT - y);
	}
	else {
		// touch end
		game->TouchEnd(x, RenderingEngine::GetInstance()->SCREEN_HEIGHT - y);
	}
}

JNIEXPORT void JNICALL Java_com_amu_flappybird_NativeRenderer_nativeOnPause(JNIEnv *jenv, jobject obj){
	if (game != 0){
		// pause game
		game->Pause();
	}
}

JNIEXPORT void JNICALL Java_com_amu_flappybird_NativeRenderer_nativeOnResume(JNIEnv *jenv, jobject obj){
	if (game != 0){
		// resume game
		game->Resume();
	}
}

JNIEXPORT void JNICALL Java_com_amu_flappybird_NativeRenderer_nativeOnQuit(JNIEnv *jenv, jobject obj){
	init = false;
	if (game != 0){
		// dispose game and its components
		game->Dispose();
		delete game;
		game = 0;
	}
}

JNIEXPORT void JNICALL Java_com_amu_flappybird_NativeRenderer_nativeSetAssetManager(JNIEnv *jenv, jobject object, jobject assetManager){
	// get asset manager from java
	AAssetManager *manager = AAssetManager_fromJava(jenv, assetManager);

	// initialize resource loader
	FileLoader::GetInstance()->Initialize(manager);
}

}
