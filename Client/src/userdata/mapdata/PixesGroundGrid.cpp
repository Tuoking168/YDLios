#include "PixesGroundGrid.h"
#include "PixesMap.h"

#include "res/Path.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/CacheData.h"


PixesGroundGrid::PixesGroundGrid()
	: mapDone(NULL)
{
	mapNodes.clear();
	CW = 256;
	CH = 256;
}

PixesGroundGrid::~PixesGroundGrid()
{
	for (std::map<int,cell*>::iterator it = mData.begin(); it != mData.end();it++)
	{
		if (it->second)
		{
			delete it->second;
		}
	}
	mData.clear();
	
	for (int i=0; i<mMap->mLogicWidth; i++)
	{
		if (mapDone[i])
		{
			delete mapDone[i];
		}
	}

	if (mapDone)
	{
		delete[]mapDone;
	}
	
}

void PixesGroundGrid::init( PixesMap* map, int w, int h )
{
	mMap = map;
	mWidth = w;
	mHeight = h;
	mCellWidth = mWidth * 48.0 / CW + (mWidth * 48 % CW != 0 ? 1 : 0);
	mCellHeight = mHeight * 32.0 / CH + (mHeight * 32 % CH != 0 ? 1 : 0);
    
	mapDone = new unsigned char*[map->mLogicWidth];
	for (int i=0; i<map->mLogicWidth; i++)
	{
		mapDone[i] = new unsigned char[map->mLogicHeight];
		for (int j=0; j<map->mLogicHeight; j++)
		{
			mapDone[i][j] = 0;
		}
	}
	
	initMapNodes();
}

void PixesGroundGrid::initMapNodes()
{
	if (mMap)
	{
		mapNodes.clear();
		for (int i=0; i<mMap->mLogicWidth; i++)
		{
			std::vector<CCSprite*> v;
			for(int j=0; j<mMap->mLogicHeight; j++)
			{
				v.push_back(NULL);
			}
			mapNodes.push_back(v);
		}
	}
}

void PixesGroundGrid::render( int focusx,int focusy )
{
	int cx = focusx / CW;
	int cy = focusy / CH;
	int rx = mMap->mWidth / CW + 1;
	int ry = mMap->mHeight / CH + 1; 

	const int recycleRange = 1;
	
	int rowb = cx - recycleRange;
	int rowe = cx+rx+ recycleRange+1;
	int colb = cy - recycleRange;
	int cole = cy+ry+ recycleRange+1;
	for (int x = rowb; x <= rowe; x++)
	{
		for (int y = colb; y <= cole; y++)
		{
			if (x<0 || y<0 || x>mMap->mLogicHeight || y>mMap->mLogicWidth)
			{
				continue;
			}
			
			if (x<(rowb+recycleRange)||x>(rowe-1-recycleRange)||y<(colb+recycleRange)||y>(cole-1-recycleRange))
			{
				CCSprite* sprite = mapNodes[y][x];
				if (sprite)
				{
					sprite->removeFromParentAndCleanup(true);
					mapNodes[y][x]=NULL;
					mapDone[y][x]=0;
				}
				continue; 
			}
			
			if (mapDone[y][x] != 0)
				continue;
			if (mapNodes[y][x])
				continue;
			if ( x >= 0 && x < mCellWidth && y >= 0 && y < mCellHeight )
			{
				CCSprite* spr = get_img(x, y);
				if ( spr )
				{
					spr->setPosition(ccp(CW/2 + x * CW, SystemData::size_y - CH/2 - y * CH));
					mMap->mDestBD->addChild(spr);
					mapDone[y][x] = 1;
					mapNodes[y][x] = spr;
				}
			}
		}
	}
}

CCSprite* PixesGroundGrid::get_img( int x,int y )
{
	cell* c = get_cell(x, y);
	if ( c )
	{
		return c->load(mMap->mResPath, mMap->mMapName, x, y, y * mCellWidth + x);
	}
	return NULL;
}

cell* PixesGroundGrid::get_cell( int x,int y )
{
	int id = y * mCellWidth + x;
	if ( mData.find(id)==mData.end() )
	{
		mData[id] = new cell();
	}
	if( mData.find(id)!=mData.end())
	{
		return mData[id];
	}
	return NULL;
}

/////////////cell/////////////////////////////////////////////////////
cell::cell()
{

}

cell::~cell()
{
}

CCSprite* cell::load( std::string& respath, std::string& mapname, int x, int y, int id)
{
	char url[128];
	sprintf(url, "%smap/%s/%s_r%d_c%d.jpg", respath.c_str(), mapname.c_str(), mapname.c_str(), y+1, x+1);
	if (CCFileUtils::sharedFileUtils()->isFileExist(url))
	{
		if (!CCCacheData::sharedCacheData()->asyncLoadData(url))
		{
			CCSprite* spr = CCSprite::create(url);
			return spr;
		}
	}
	return NULL;
}
