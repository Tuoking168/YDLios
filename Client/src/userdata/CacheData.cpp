#include "CacheData.h"

#include "res/Path.h"

#include "utils/MacroUtils.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"


CCCacheData* CCCacheData::s_pCacheData = NULL;

bool CCCacheData::isAlreadyCache( const std::string & path )
{
	std::string fullpath = path;
	PathR::convert(fullpath);
	if (CCTextureCache::sharedTextureCache()->textureForKey(fullpath.c_str()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CCCacheData::state_AsyncCache( const std::string& path )
{
	if (s_mapCache.find(path) != s_mapCache.end())
	{
		return s_mapCache[path];
	}

	if (isAlreadyCache(path))
	{
		s_mapCache[path] = STATE_LOADED_MUTABLE;
	}
	else
	{
		s_mapCache[path] = STATE_NOT_LOAD;
	}

	return s_mapCache[path];
}

bool CCCacheData::asyncLoadData(const std::string& path)
{
	if (state_AsyncCache(path) >= STATE_LOADED_MUTABLE)
	{
		return false;
	}

	if (s_mapCache[path] == STATE_IS_LOADING)
	{
		return true;
	}

	s_mapCache[path] = STATE_IS_LOADING;
	CCTextureCache::sharedTextureCache()->addImageAsync(path.c_str(), this, callfuncO_selector(CCCacheData::loadDataCallBack));
	return true;
}

void CCCacheData::loadDataCallBack(CCObject* pObject)
{
	CPForeach(it, CacheState, s_mapCache)
	{
		if (it->second == STATE_IS_LOADING)
		{
			if (CCTextureCache::sharedTextureCache()->textureForKey(it->first.c_str()))
			{
				it->second = STATE_LOADED_IMMUTABLE;
			}
		}
	}
}

void CCCacheData::releaseCacheDataFT()
{
	for (CacheState::iterator it = s_mapCache.begin(); it != s_mapCache.end();)
	{
		if (it->second == STATE_LOADED_IMMUTABLE)
		{
			CCTextureCache::sharedTextureCache()->removeTextureForKey(it->first.c_str());
			s_mapCache.erase(it++);
		}
		else
		{
			it++;
		}
	}
}

void CCCacheData::releaseCacheDataAll()
{
	CPForeach(it, CacheState, s_mapCache)
	{
		CCTextureCache::sharedTextureCache()->removeTextureForKey(it->first.c_str());
	}
	s_mapCache.clear();
}

CCCacheData* CCCacheData::sharedCacheData()
{
	if (!s_pCacheData)
	{
		static CCCacheData _data;
		s_pCacheData = &_data;//new CCCacheData  memory leaks here;
	}
	return s_pCacheData;
}