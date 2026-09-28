#ifndef __ITEM_GHOST_H__
#define __ITEM_GHOST_H__

#include "Ghost.h"
#include "AliveGhost.h"

class ItemGhost : public AliveGhost
{
public:
	ItemGhost();
    ~ItemGhost();
	static ItemGhost* create();

	virtual bool init();
	virtual void initName();
	virtual void update();

private:
	bool initItem();
	bool initSkill();
	bool initMarket();

	void refreshPoster();

public:
	std::string mName;
	CCLabelTTF *m_disName;
	int mCount;

private:
	CCNode *mPosterBoard;
	CCLabelTTF *mPosterLabel;
};

#endif //__ITEM_GHOST_H__