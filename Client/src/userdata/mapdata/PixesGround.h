#ifndef	___PIXES_GROUND_____
#define ___PIXES_GROUND_____


#include "cocos2d.h"
#include "CommonType.h"

using namespace cocos2d;

class PixesMap;
class TileData;
class LoaderTile;

class PixesGround
{
public:
	PixesGround();
	~PixesGround();
	void init(PixesMap* map, TileData* groundData,int vOrder);
	void render(int focusx, int focusy);

private:
	void initMapNodes();
	CCSprite* loadTile(int dir, int id);

private:
	PixesMap* mMap;
	TileData* mGroundData;
	LoaderTile* mTileLoader;
	int mRowNumber;
	int mColNumber;
	int8** mapDone;
    std::vector<std::vector<CCSprite*> > mapNodes;
	int mZorder;
};

///////////LoaderTile//////////////////////////////////////////////
class LoaderTile
{
public:
	LoaderTile();
	~LoaderTile();
	CCSprite* loadTile(int dir, int id, short row, short collomn, short tilewidth, short tileheight, CCLayer* father, int layerOrder);

private:
	CCSpriteBatchNode* m_tileSBNode;
};
#endif // ___PIXES_GROUND_____