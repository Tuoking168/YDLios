#include "PlistLoader.h"
#include "CCSpriteFrameCache.h"
#include "CCTextureCache.h"

#include "script/LuaWrapper.h"


using namespace cocos2d;


#define KEY_HEAD "data-a/"


static void load( const std::string &file )
{
	if (file.empty())
	{
		return;
	}

	const std::string &path = KEY_HEAD + file;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path.c_str());
}

static void unload( const std::string &file )
{
	if (file.empty())
	{
		return;
	}

	const std::string &plist = KEY_HEAD + file;
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plist.c_str());

	const std::string &png = KEY_HEAD + file.substr(0, file.find(".plist")) + ".png";
	CCTextureCache::sharedTextureCache()->removeTextureForKey(png.c_str());
}

static int getPlistCnt( const std::string &key )
{
	int cnt = 0;
	Lua::instance()->push(key);
	Lua::instance()->call("get_plist_cnt", 1, 1);
	Lua::instance()->pop(cnt);
	return cnt;
}

static std::string getPlistName( const std::string &key, int index )
{
	std::string file;
	Lua::instance()->push(key);
	Lua::instance()->push(index);
	Lua::instance()->call("get_plist_file", 2, 1);
	Lua::instance()->pop(file);
	return file;
}

static void loadPlistData( const std::string &key )
{
	const int cnt = getPlistCnt(key);
	for (int i = 0; i < cnt; i++)
	{
		load(getPlistName(key, i + 1));
	}
}

static void unloadPlistData( const std::string &key )
{
	const int cnt = getPlistCnt(key);
	for (int i = 0; i < cnt; i++)
	{
		unload(getPlistName(key, i + 1));
	}
}

///////////PlistLoader/////////////////////////////////////////////
namespace PlistKey
{
	static const std::string COMMON = "common";
	static const std::string WELCOME = "welcome";
	static const std::string LOGIN = "login";
	static const std::string LOADING = "loading";
	static const std::string MAIN = "main";
}

void PlistLoader::loadCommon()
{
	loadPlistData(PlistKey::COMMON);
}

void PlistLoader::loadWelcome()
{
	loadPlistData(PlistKey::WELCOME);
}

void PlistLoader::unloadWelcome()
{
	unloadPlistData(PlistKey::WELCOME);
}

void PlistLoader::loadLogin()
{
	loadPlistData(PlistKey::LOGIN);
}

void PlistLoader::unloadLogin()
{
	unloadPlistData(PlistKey::LOGIN);
}

void PlistLoader::loadLoading()
{
	loadPlistData(PlistKey::LOADING);
}

void PlistLoader::unloadLoading()
{
	unloadPlistData(PlistKey::LOADING);
}

int PlistLoader::getMainCount()
{
	return getPlistCnt(PlistKey::MAIN);
}

void PlistLoader::loadMain( int index )
{
	load(getPlistName(PlistKey::MAIN, index));
}

