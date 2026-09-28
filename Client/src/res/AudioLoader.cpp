#include "AudioLoader.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "script/LuaWrapper.h"

#include "userdata/SystemData.h"


using namespace cocos2d;
using namespace CocosDenshion;

#define AUDIO_TRANSFORM_TAG 171

static bool getEffectSoundCount( int &count )
{
	if (Lua::instance()->call("g_get_effect_sound_cnt", 0, 1) &&
		Lua::instance()->pop(count))
	{
		return true;
	}
	CCLog(">>>Error: failed to call g_get_effect_sound_cnt");
	return false;
}

static bool getMusicSoundCount( int &count )
{
	if (Lua::instance()->call("g_get_music_sound_cnt", 0, 1) &&
		Lua::instance()->pop(count))
	{
		return true;
	}
	CCLog(">>>Error: failed to call g_get_music_sound_cnt");
	return false;
}

static bool getEffectSoundPath( int index, std::string &path )
{
	Lua::instance()->push(index);
	if (Lua::instance()->call("g_get_effect_sound_path", 1, 1) &&
		Lua::instance()->pop(path))
	{
		return true;
	}
	CCLog(">>>Error: failed to call g_get_effect_sound_path");
	return false;
}

static bool getMusicSoundPath( int index, std::string &path )
{
	Lua::instance()->push(index);
	if (Lua::instance()->call("g_get_music_sound_path", 1, 1) &&
		Lua::instance()->pop(path))
	{
		return true;
	}
	CCLog(">>>Error: failed to call g_get_music_sound_path");
	return false;
}

/////////AudioLoading////////////////////////////////////////////////
bool AudioLoader::sLoaded = false;
bool AudioLoader::sIsSilent = false;
bool AudioLoader::sIsEffectSilent = false;
std::string AudioLoader::sCurrentMusic;

void AudioLoader::doLoad()
{
	if (sLoaded)
	{
		return;
	}

	int cnt = 0;
	std::string path;
	getEffectSoundCount(cnt);
	for (int i = 0; i < cnt; i++)
	{
		path.clear();
		getEffectSoundPath(i + 1, path);
		if (!path.empty())
		{
			SimpleAudioEngine::sharedEngine()->preloadEffect(path.c_str());
		}
	}

	if (SystemData::getConfigInt("mini") == 0)
	{
		cnt = 0;
		getMusicSoundCount(cnt);
		for (int i = 0; i < cnt; i++)
		{
			path.clear();
			getMusicSoundPath(i + 1, path);
			if (!path.empty())
			{
				SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(path.c_str());
			}
		}
	}
	
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);

	sLoaded = true;
}

void AudioLoader::play( int effectID )
{
	if (!isEffectSilent())
	{
		std::string path;
		getEffectSoundPath(effectID, path);
		play(path);
	}
}

void AudioLoader::play( const std::string &effectPath )
{
	if (!isEffectSilent())
	{
		if (!effectPath.empty())
		{
			SimpleAudioEngine::sharedEngine()->playEffect(effectPath.c_str(), false);
		}
	}
}

void AudioLoader::change( const std::string &targetMusicPath )
{
	if (SystemData::getConfigInt("mini") != 0)
	{
		return;
	}

	if (!targetMusicPath.empty() &&
		targetMusicPath != sCurrentMusic)
	{
		sCurrentMusic = targetMusicPath;
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(targetMusicPath.c_str(), true);
		if (sIsSilent)
		{
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		}
	}
}

void AudioLoader::transform( int musicID )
{
	std::string path;
	getMusicSoundPath(musicID, path);
	transform(path);
}

void AudioLoader::transform( const std::string &musicPath )
{
	if (!musicPath.empty() &&
		musicPath != sCurrentMusic)
	{
		change(musicPath);
	}
}

void AudioLoader::setSilent( bool silent )
{
	sIsSilent = silent;
	if (sIsSilent)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}

bool AudioLoader::isSilent()
{
	return sIsSilent;
}

void AudioLoader::stopAll()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void AudioLoader::setEffectSilent( bool silent )
{
	sIsEffectSilent = silent;
	if (sIsEffectSilent)
	{
		SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	}
}

bool AudioLoader::isEffectSilent()
{
	return sIsEffectSilent;
}

void AudioLoader::reduceEffectVoice()
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(SimpleAudioEngine::sharedEngine()->getEffectsVolume()-0.1f);
}

void AudioLoader::reduceBackGroundVoice()
{
	setBackGroundVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() - 0.1f);
}

void AudioLoader::addEffectVoice()
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(SimpleAudioEngine::sharedEngine()->getEffectsVolume()+0.1f);
}

void AudioLoader::addBackGroundVoice()
{
	setBackGroundVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() + 0.1f);
}

void AudioLoader::setBackGroundVolume( float volume )
{
	if (volume < 0)
	{
		volume = 0;
	}
	else if(volume > 1.0f)
	{
		volume = 1.0f;
	}
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}
