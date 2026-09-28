#include "PixesMap.h"
#include "PixesGround.h"
#include "MapData.h"
#include "Maploader.h"
#include "PixesGroundGrid.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/luadata/LuaData.h"

PixesMap::PixesMap()
	: mGroundGrid(NULL)
	, mDestBD(NULL)
	,mMapVersion(0)
	,mWidth(SystemData::size_x)
	,mHeight(SystemData::size_y)
	,mLogicWidth(256)
	,mLogicHeight(256)
	,mResPath("data-a/")
	,mMapName(GameData::getCurrentMap()->mMapFile)
{
	mDestBD = CCLayer::create();
	mDestBD->setAnchorPoint(ccp(0, 1));

	LuaData::getProp(LuaData::MAP, GameData::getCurrentMap()->mID, "sizex", mLogicWidth);
	LuaData::getProp(LuaData::MAP, GameData::getCurrentMap()->mID, "sizey", mLogicHeight);

	mMapData = new MapData;
	mMapData->mLogicWidth = mLogicWidth;
	mMapData->mLogicHeight = mLogicHeight;

	const std::string &path = mResPath + "map/" + mMapName;
	MapLoader::loadMap(path, mMapData);

	std::string resourceExt;
	LuaData::getProp(LuaData::MAP, GameData::getCurrentMap()->mID, "resource_ext", resourceExt);
	if (resourceExt.size() > 1)
	{
		mMapName = resourceExt;
	}

	//
	init();
}

PixesMap::~PixesMap()
{
	for(unsigned int i=0; i<mLayers.size(); i++)
	{
		if(mLayers[i])
		{
			delete mLayers[i];
			mLayers[i] = NULL;
		}
	}
	mLayers.clear();
	if (mGroundGrid)
	{
		delete mGroundGrid;
	}
	if (mBlockData)
	{
		for(int i=0; i<mLogicHeight; i++)
		{
			delete []mBlockData[i];
		}
		delete[]mBlockData;
	}

	if (mMapData)
	{
		delete mMapData;
	}
}

void PixesMap::init()
{
	mMapVersion = mMapData->mVersion;
	mLogicWidth = mMapData->mLogicWidth;
	mLogicHeight = mMapData->mLogicHeight;
	mBlockData = mMapData->mBlockData;

	//
	mLayers.resize(mMapData->mTileData.size());
	for(unsigned int i = 0; i < mLayers.size(); i++)
	{
		mLayers[i] = NULL;
		if(mMapData->mTileData[i])	
		{
			mLayers[i] = new PixesGround;	
			mLayers[i]->init(this, mMapData->mTileData[i], i + 1);
		}
	}
	
	//
	mGroundGrid = new PixesGroundGrid();
	mGroundGrid->init(this, mMapData->mLogicWidth, mMapData->mLogicHeight);
}

void PixesMap::attach(CCLayer* target)
{
	if (mDestBD)
	{
		target->addChild(mDestBD);
	}
}

void PixesMap::setLayersPosition(int focusx, int focusy)
{
	if (mDestBD)
	{
		mDestBD->setPosition(ccp(-focusx, focusy));
	}
}

void PixesMap::render(int focusx, int focusy)
{
	setLayersPosition(focusx, focusy);
	
	for(unsigned int i = 0; i < mLayers.size(); i++)
	{
		if(mLayers[i])
		{
			mLayers[i]->render(focusx, focusy);
		}
	}
	mGroundGrid->render(focusx, focusy);
}

CCPoint PixesMap::getPixelPoint( int tileX, int tileY )
{
	CCPoint ret = CCPointZero;
	ret.x = tileX * TILE_WIDTH + TILE_WIDTH/2;
	ret.y = tileY * TILE_HEIGHT + TILE_HEIGHT/2;
	return ret;
}
