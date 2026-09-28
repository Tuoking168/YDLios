#include "SceneData.h"
#include "ModuleData.h"
#include "SceneModule.h"
#include "script/LuaWrapper.h"
#include "utils/StringUtils.h"

static void setSceneData( const std::string &keyHead, int key, int data )
{
	const std::string &fullKey = keyHead + StringUtils::toString(key);
	ModuleData::setInt(CPModuleName::SCENE, fullKey, data);
}

static int getSceneData( const std::string &keyHead, int key )
{
	int ret = 0;
	const std::string &fullKey = keyHead + StringUtils::toString(key);
	ModuleData::getInt(CPModuleName::SCENE, fullKey, ret);
	return ret;
}

static void setSceneStringData( const std::string &keyHead, int key, const std::string &data )
{
	const std::string &fullKey = keyHead + StringUtils::toString(key);
	ModuleData::setString(CPModuleName::SCENE, fullKey, data);
}

static std::string getSceneStringData( const std::string &keyHead, int key )
{
	std::string ret;
	const std::string &fullKey = keyHead + StringUtils::toString(key);
	ModuleData::getString(CPModuleName::SCENE, fullKey, ret);
	return ret;
}

/////////SceneData/////////////////////////////////////////////////
void SceneData::clear()
{
	ModuleData::clearModule(CPModuleName::SCENE);
}

void SceneData::setProp( int key, int data )
{
	setSceneData(CPSceneData::PROP_, key, data);
}

int SceneData::getProp( int key )
{
	return getSceneData(CPSceneData::PROP_, key);
}

int SceneData::getProp( const std::string &keyName )
{
	return getProp(getPropKey(keyName));
}

void SceneData::setStringProp( int key, const std::string &data )
{
	setSceneStringData(CPSceneData::PROP_, key, data);
}

std::string SceneData::getStringProp( int key )
{
	return getSceneStringData(CPSceneData::PROP_, key);
}

std::string SceneData::getStringProp( const std::string &keyName )
{
	return getStringProp(getPropKey(keyName));
}

int SceneData::getPropKey( const std::string &keyName )
{
	int ret = 0;
	Lua::instance()->push(keyName);
	Lua::instance()->call("cb_get_scene_prop_key", 1, 1);
	Lua::instance()->pop(ret);
	return ret;
}

void SceneData::setHasEnterScene( bool flag )
{
	int data = 0;
	if (flag)
	{
		data = 1;
	}
	ModuleData::setInt(CPModuleName::SCENE, CPSceneData::HAS_ENTER_SCENE, data);
}

bool SceneData::hasEnterScene()
{
	int data = 0;
	ModuleData::getInt(CPModuleName::SCENE, CPSceneData::HAS_ENTER_SCENE, data);
	return (data != 0);
}
