#ifndef ___PIXES_GROUND_GRID____
#define ___PIXES_GROUND_GRID____

#include "cocos2d.h"

using namespace cocos2d;

class PixesMap;
class cell;


class PixesGroundGrid
{
public:
	PixesGroundGrid();
	~PixesGroundGrid();
	void init(PixesMap *map, int w, int h);
	void render(int focusx, int focusy);
	
private:
	void initMapNodes();
	CCSprite* get_img(int x,int y);
	cell*  get_cell(int x,int y);

private:
	PixesMap* mMap;
	int mWidth;
	int mHeight;
	int mCellWidth;
	int mCellHeight;
	int CW;
	int CH;

	typedef std::map<int,cell*> MapCell;
	MapCell mData;

	unsigned char** mapDone;
	std::vector<std::vector<CCSprite*> > mapNodes;
};

/////////cell///////////////////////////////////////////////////
class cell : public CCObject
{
public:
	cell();
	~cell();
	CCSprite* load(std::string& respath, std::string& mapname, int x, int y, int id);
};


#endif //___PIXES_GROUND_GRID____