#include "MapData.h"
#include "userdata/luadata/MinimapLua.h"


MapData::MapData()
	: mBlockData(NULL)
{

}

MapData::~MapData()
{
	MapConnVect tv;
	for (MapConnsMap::iterator itm=mMiniMapConn.begin();itm!=mMiniMapConn.end();itm++)
	{
		tv=itm->second;
		for (MapConnVect::iterator it=tv.begin();it!=tv.end();it++)
		{
			delete *it;
		}
	}
	mMiniMapConn.clear();
	for(unsigned int i = 0; i < mTileData.size(); i++)
	{
		if(mTileData[i])
		{
			delete mTileData[i];
			mTileData[i] = NULL;
		}
	}
}

void MapData::initMapDate()
{
	MiniMapLua::getMapPortals();
} 
   