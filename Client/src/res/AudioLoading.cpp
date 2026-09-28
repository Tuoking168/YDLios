#include "AudioLoading.h"
#include "SimpleAudioEngine.h"
#include <stdio.h>
using namespace CocosDenshion;



static const int _sound_file_start[] =
{
	56,57,1000,1001,1002,1003,1004,1005,1006,1007,1008,2000,2001,2002,2004,3000,3001,3002,4003,4004,4701,4702,4801,4802,4901,4902,
	8001,8102,8601,8101,8103,8701,8801,8901
};

bool AudioLoading::_loaded = false;

bool AudioLoading::_sound_status = true;

short AudioLoading::_current_music_idx = -1;

void AudioLoading::doLoad()
{
	if (!_loaded)
	{
		_current_music_idx = -1;
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);

		_loaded = true;
		for (short i=0; i<sound_max; i++)
		{
			if (_sound_file_start[i]!=NULL)
			{
				char soundName[32];
// 				if(_sound_file_start[i] == 8101)
// 				{
// 					sprintf(soundName,"data-a/sound/%d.wav",_sound_file_start[i]);
// 				}
// 				else
// 				{
					sprintf(soundName,"data-a/sound/%d.mp3",_sound_file_start[i]);
//				}
				SimpleAudioEngine::sharedEngine()->preloadEffect(soundName);
			}
		}
	}
}

int AudioLoading::start( int idx,bool loop/*=false*/ )
{
	if (_sound_status)
	{
		char soundName[32];
		sprintf(soundName,"data-a/sound/%d.mp3",idx);
		return SimpleAudioEngine::sharedEngine()->playEffect(soundName, loop);
	}
	return -1;
}

void AudioLoading::startBackgroundMusic(int idx)
{
	if (_sound_status && idx!=_current_music_idx)
	{
		char soundName[32];
		sprintf(soundName,"data-a/sound/%d.mp3",idx);
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(soundName, true);
	}
	_current_music_idx = idx;
}

void AudioLoading::set_state_sound(bool v)
{
	_sound_status = v;
	if (v)
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

void AudioLoading::stop( int effectId )
{
	SimpleAudioEngine::sharedEngine()->stopEffect(effectId);
}

void AudioLoading::stopAll()
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
}
