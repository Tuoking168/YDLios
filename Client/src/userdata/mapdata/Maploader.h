#ifndef	___MAPLOADER_DATA_____
#define ___MAPLOADER_DATA_____


#include "cocos2d.h"

using namespace cocos2d;

class CCFileDataStream;
class MapData;
class TileData;

class MapLoader
{
public:
	static bool loadMap(const std::string& file, MapData* mapdata);

private:
	static void LoadVersion3(CCFileDataStream* ba, MapData* mapdata);
	static void LoadVersion4(CCFileDataStream* ba, MapData* mapdata);
	static void loadTileData(CCFileDataStream* ba, TileData* tiledata);
};




#endif //___MAPLOADER_DATA_____