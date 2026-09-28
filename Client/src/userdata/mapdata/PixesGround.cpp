#include "PixesGround.h"
#include "PixesMap.h"
#include "MapData.h"

#include "userdata/CacheData.h"
#include "userdata/SystemData.h"

PixesGround::PixesGround()
	: mGroundData(NULL)
	, mMap(NULL)
	, mapDone(NULL)
	, mTileLoader(NULL)
	, mZorder(0)
{
    mapNodes.clear();
}

PixesGround::~PixesGround()
{
	for (int i=0; i<mGroundData->mWidth; i++)
	{
		if (mapDone && mapDone[i])
		{
			delete[] mapDone[i];
		}
	}

	if (mapDone)
	{
		delete[] mapDone;
	}

	if (mTileLoader)
	{
		delete mTileLoader;
	}

	if (mMap)
	{
		mMap->mDestBD->removeAllChildrenWithCleanup(true);
	}
}

void PixesGround::init( PixesMap* map, TileData* groundData, int vOrder )
{
	mZorder = vOrder;
	mMap = map;
	mGroundData = groundData;
	mTileLoader = new LoaderTile();

	initMapNodes();
}

void PixesGround::initMapNodes()
{
	if (mMap)
	{
		mRowNumber = SystemData::size_y / mGroundData->mTileHeight + 3;
		mColNumber = SystemData::size_x / mGroundData->mTileWidth + 3;
		mapNodes.clear();
		for (int i=0; i<mGroundData->mWidth; i++)
		{
			std::vector<CCSprite*> v(mGroundData->mHeight,NULL);
			mapNodes.push_back(v);
			for (int j=0; j<mGroundData->mHeight; j++)
           {
               mapNodes[i][j] = NULL;
           }
		}
	}
}

void PixesGround::render(int focusx, int focusy)
{
	const CCSize &winSize = CCDirector::sharedDirector()->getWinSize();
	const int loadRange = 3;
	const int recycleRange = 1;
	int winRow = winSize.width/mGroundData->mTileWidth + loadRange; 
	int winCol = winSize.height/mGroundData->mTileHeight + loadRange; 

	int datax = focusx / mGroundData->mTileWidth; 
	int datay = focusy / mGroundData->mTileHeight;

	int dx = 0;
	int dy = 0;
	int id = 0;
 	int rowb = 1 - recycleRange;
 	int rowe = winCol+ recycleRange;
 	int colb = 1 - recycleRange;
 	int cole = winRow+ recycleRange;
	for (int row = rowb; row < rowe; row++)
	{
		for (int col = colb; col < cole; col++)
		{
			dx = datax + col;
			dy = datay + row;
			//load the two more tiles than window width, in case of leaking black ground
			if(dx > 0)
			{
				dx-=1;
			}
			if(dy > 0)
			{
				dy-=1;
			}
			if (dx < 0 || dx >= mGroundData->mWidth || dy < 0 || dy >= mGroundData->mHeight)
				continue;
			if (row<(rowb+recycleRange)||row>(rowe-1-recycleRange)||col<(colb+recycleRange)||col>(cole-1-recycleRange))
			{
				CCSprite* sprite = mapNodes[dx][dy];
				if (sprite)
				{
					sprite->removeFromParentAndCleanup(true);
					mapNodes[dx][dy]=NULL;
				}
				continue;
			}
			if (mapNodes[dx][dy])
				continue;
				
			if ( mGroundData->mData[dy] && mGroundData->mData[dy][dx])
			{ 
				id = mGroundData->mData[dy][dx];
				if( id > 0 )
				{
					CCSprite* sprite = loadTile(mGroundData->mDir, id);
					if (sprite)
					{
						sprite->setAnchorPoint(ccp(0, 1));
						sprite->setPosition(ccp(dx * mGroundData->mTileWidth, SystemData::size_y - dy * mGroundData->mTileHeight));
                        mapNodes[dx][dy] = sprite;
					}
				}
			}
		}
	}
}

CCSprite* PixesGround::loadTile(int dir, int id) 
{
	char url[128];
	if(dir<10000)
	{
		sprintf(url, "data-a/tile/%05d.png", dir);
	}
	else
	{
		sprintf(url, "data-a/tile/%05d.jpg",dir-10000);
	}
	
	if (!CCCacheData::sharedCacheData()->asyncLoadData(url))
	{
		return mTileLoader->loadTile(dir, id, mGroundData->mTileRow, mGroundData->mTileCollomn, mGroundData->mTileWidth, mGroundData->mTileHeight, mMap->mDestBD,mZorder); 
	}
	else
	{
		return NULL;
	}
}

////////LoaderTile//////////////////////////////////////////////////
LoaderTile::LoaderTile()
	: m_tileSBNode(NULL)
{

}

LoaderTile::~LoaderTile()
{

}

CCSprite* LoaderTile::loadTile( int dir, int id, short row, short collomn, short tilewidth, short tileheight, CCLayer* father, int layerOrder)
{
	if (!m_tileSBNode)
	{
		char url[64];
		if(dir<10000)
		{
			sprintf(url, "data-a/tile/%05d.png", dir);
		}
		else
		{
			sprintf(url, "data-a/tile/%05d.jpg",dir-10000);
		}

		m_tileSBNode = CCSpriteBatchNode::create(url);
		if (m_tileSBNode)
		{
			father->addChild(m_tileSBNode, layerOrder);
		}
		else
		{
			CCLOG("Failed to load tileset : %s",url);
			return NULL;
		}
	}
	id -= 1;
	int i = id / collomn;
	int j = id % collomn;
	CCSprite* bnsprite = CCSprite::createWithTexture(m_tileSBNode->getTexture(), CCRectMake(j*tilewidth, i*tileheight, tilewidth, tileheight));
	bnsprite->setAnchorPoint(ccp(1,0.5));
	m_tileSBNode->addChild(bnsprite);
	return bnsprite;
}
