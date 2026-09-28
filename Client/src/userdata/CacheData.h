#ifndef	___CACHE_DATA_____
#define ___CACHE_DATA_____

#include "cocos2d.h"
USING_NS_CC;


class CCCacheData : public CCObject
{
public:
	static CCCacheData* sharedCacheData();

	bool asyncLoadData(const std::string& path);
	
	void releaseCacheDataFT();
	void releaseCacheDataAll();

private:
	bool isAlreadyCache(const std::string& path);
	void loadDataCallBack(CCObject* pObject);
	int	state_AsyncCache(const std::string& path);

private:
	enum CACHEDATA_STATE
	{
		STATE_NOT_LOAD,
		STATE_IS_LOADING,
		STATE_LOADED_MUTABLE,
		STATE_LOADED_IMMUTABLE
	};

	typedef std::map<std::string, int> CacheState;
	CacheState s_mapCache;
	static CCCacheData* s_pCacheData;
};



#endif //___CACHE_DATA_____
