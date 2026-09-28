#ifndef	___MAPDATA_DATA_____
#define ___MAPDATA_DATA_____

#include "cocos2d.h"

typedef struct stucNetMapConn 
{
	int mStaticID;
	int mMapID;
	int mFromX;
	int mFromY;
	int mDesMapID;
	std::string mDesMapName;
	int mDesX;
	int mDesY;
	int mSize;
} NetMapConn;

class TileData
{
public:
	short mWidth;
	short mHeight;
	short mDir;
	short** mData;
	short mTileRow;
	short mTileCollomn;
	short mTileWidth;
	short mTileHeight;
	TileData()
		: mWidth(0),mHeight(0),mDir(0),mData(NULL),mTileWidth(0),mTileHeight(0),mTileRow(0),mTileCollomn(0)
	{}
	virtual ~TileData()
	{
		if (mData)
		{
			for(int h=0; h<mHeight; h++)
			{
				delete[] mData[h];
			}
			delete[] mData;
			mData = NULL;
		}
	}
};

typedef std::vector<NetMapConn*> MapConnVect;
typedef std::map<int, MapConnVect > MapConnsMap;
class MapData
{
public:
	MapData();
	~MapData();
	void initMapDate();

public:
	MapConnsMap mMiniMapConn;//地图的关联

	short mVersion;
	short mLogicWidth;
	short mLogicHeight;

	int mDefaultBlock;
	unsigned char** mBlockData;

	std::vector<TileData *> mTileData;
};




#endif //___MAPDATA_DATA_____