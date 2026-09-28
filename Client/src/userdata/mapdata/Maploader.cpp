#include "maploader.h"
#include "CCFileDataStream.h"
#include "MapData.h"
#include <vector>

#include "res/Path.h"


bool MapLoader::loadMap(const std::string& file, MapData* mapdata)
{
	std::string binfile = file + ".mapo";
	PathR::convert(binfile);

	CCFileDataStream mtba;
	if (!mtba.load(binfile.c_str()))
	{
		CCLog("Error: File %s read error....", binfile.c_str());
		return false;
	}

	CCFileDataStream* ba = &mtba;
	ba->read(mapdata->mVersion);
	if ( mapdata->mVersion == 3 )
	{
		LoadVersion3(ba, mapdata);
	}
	else if ( mapdata->mVersion == 4 )
	{
		LoadVersion4(ba, mapdata);
	}
	return true;
}

void MapLoader::LoadVersion3(CCFileDataStream* ba, MapData* mapdata)
{
	mapdata->mDefaultBlock = 0;

	//load the tile data
	short layerNum = 0;
	ba->read(layerNum);
	mapdata->mTileData.resize(layerNum);
	for(short i=0; i<layerNum; i++)	
	{
		mapdata->mTileData[i] = new TileData;
		loadTileData(ba,mapdata->mTileData[i]);
	}

	//
	ba->read(mapdata->mLogicWidth);
	ba->read(mapdata->mLogicHeight);
	const short width = mapdata->mLogicWidth;
	const short height = mapdata->mLogicHeight;

	//load the block data
	int size = 0;
	ba->read(size);
	std::vector<short> bad;
	int ind = 0;
	unsigned char b = 0;
	unsigned char l = 0;
	while (ind<size)
	{
		ba->read(b);
		ba->read(l);
		for (int i = 0; i < l; i++)
		{
			bad.push_back(b);
		}
		ind = ind + 1;
	}
	int badindex = 0;
	int badData = 0;
	mapdata->mBlockData = new unsigned char*[height]();
	for ( int h=0; h < height; h++ )
	{
		mapdata->mBlockData[h] = new unsigned char[width]();
		for ( int w=0; w < width; w++ )
		{
			badData = 0;
			if (badindex < (int)bad.size())
			{
				badData = bad[badindex++];
			}
			mapdata->mBlockData[h][w] = badData;
		}
	}
}

void MapLoader::LoadVersion4(CCFileDataStream* ba, MapData* mapdata)
{
	mapdata->mDefaultBlock = 0;

	//
	ba->read(mapdata->mLogicWidth);
	ba->read(mapdata->mLogicHeight);
	const short width = mapdata->mLogicWidth;
	const short height = mapdata->mLogicHeight;

	int size = 0;
	ba->read(size);
	std::vector<short> bad;
	int badindex = 0;
	int ind = 0;
	unsigned char b;
	unsigned char l;
	while (ind<size)
	{
		ba->read(b);
		ba->read(l);
		for (int i = 0; i < l; i++)
		{
			bad.push_back(b);
		}
		ind = ind + 1;
	}

	badindex = 0;
	int badData = 0;
	mapdata->mBlockData = new unsigned char*[height]();
	for ( int h=0; h < height; h++ )
	{
		mapdata->mBlockData[h] = new unsigned char[width]();
		for ( int w=0; w < width; w++ )
		{
			badData = 0;
			if (badindex < (int)bad.size())
			{
				badData = bad[badindex++];
			}
			mapdata->mBlockData[h][w] = badData;
		}
	}
}

void MapLoader::loadTileData( CCFileDataStream* ba, TileData* tiledata )
{
	//load general data for tile layer
	ba->read(tiledata->mWidth);
	ba->read(tiledata->mHeight);
	ba->read(tiledata->mDir);

	ba->read(tiledata->mTileCollomn);
	ba->read(tiledata->mTileRow);
	ba->read(tiledata->mTileWidth);
	ba->read(tiledata->mTileHeight);
	if (tiledata->mTileWidth <= 0)
	{
		tiledata->mTileWidth = 1;
	}

	if (tiledata->mTileHeight <= 0)
	{
		tiledata->mTileHeight = 1;
	}

	//load the ground tile data
	tiledata->mData = new short*[tiledata->mHeight];
	for (int gh=0; gh < tiledata->mHeight; gh++ )
	{
		tiledata->mData[gh] = new short[tiledata->mWidth]();
		for (int gw=0; gw < tiledata->mWidth; gw++ )
		{
			short tile;
			ba->read(tile);
			tiledata->mData[gh][gw] = tile;
		}
	}
}
