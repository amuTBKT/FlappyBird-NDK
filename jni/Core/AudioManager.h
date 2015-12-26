#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_

#include <SLES/OpenSLES_Android.h>
#include <assert.h>

#include <hash_map>
#include <string>
#include "FileLoader.h"

struct AudioEffect{
	SLObjectItf audioObject;
	SLPlayItf audioPlay;

	AudioEffect(){
		audioObject = 0;
		audioPlay = 0;
	}
};

class AudioManager{
private:
	SLObjectItf engineObject;
	SLEngineItf engine;
	SLObjectItf outputMixObject;

	std::hash_map<std::string, AudioEffect*> loadedSFX;

	static void play_callback(SLPlayItf player, void *context, SLuint32 event){
		if(event & SL_PLAYEVENT_HEADATEND){
			(*player)->SetPlayState(player, SL_PLAYSTATE_STOPPED);
		}
	}

public:
	static AudioManager* GetInstance();

	void Initialize();

	AudioEffect* CreateSFX(const char *file);
	void PlaySFX(AudioEffect *effect);

	void DeleteSFX(AudioEffect *effect);
	void Dispose();
};

#endif
