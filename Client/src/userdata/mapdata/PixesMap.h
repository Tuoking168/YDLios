#ifndef	___PIXESMAP_____
#define ___PIXESMAP_____


#include "cocos2d.h"

using namespace cocos2d;

class CCFileDataStream;
class MapData;
class PixesGround;
class PixesGroundGrid;

class PixesMap
{
public:
	PixesMap();
	~PixesMap();
	void attach(CCLayer* target);
	void render(int, int);

	static CCPoint getPixelPoint(int tileX, int tileY);

private:
	void init();
	void setLayersPosition(int focusx, int focusy);

public:
	static const int TILE_WIDTH = 48;
	static const int TILE_HEIGHT = 32;

	std::string mMapName;
	std::string mResPath;

	CCLayer* mDestBD;
	int mWidth;
	int mHeight;
	int mLogicWidth;
	int mLogicHeight;

	unsigned char** mBlockData;

private:
	MapData *mMapData;
	PixesGroundGrid* mGroundGrid;
	std::vector<PixesGround*> mLayers;

	int mMapVersion;
};




#endif //___PIXESMAP_____