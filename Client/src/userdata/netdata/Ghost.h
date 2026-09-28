#ifndef __GHOST_H__
#define __GHOST_H__

#include "cocos2d.h"
USING_NS_CC;

class MsgPacket;


enum GHOST_TYPE
{
	GHOST_TYPE_NPC = 500,
	GHOST_TYPE_PLAYER = 501,
	GHOST_TYPE_MONSTER = 502,
	GHOST_TYPE_MAP_ITEM = 503,
	GHOST_TYPE_SLAVE = 504,
	GHOST_TYPE_PLANT = 506,
	GHOST_TYPE_COLLECTION = 507,
	GHOST_TYPE_SKILL	= 509,
	GHOST_TYPE_PET	= 510,
	GHOST_TYPE_MINE	= 511,
	GHOST_TYPE_SKILL_BIND = 512,
	GHOST_TYPE_THIS = 999
};

class CCFlashAnimation;
class Ghost : public CCObject
{
public:
	Ghost();
	Ghost(int type);
    virtual ~Ghost();
	virtual bool init(){return true;}
	virtual void init(CCSprite* base);

public:
	virtual void	attach(CCLayer* target);
	virtual void	detach(CCLayer* target);
	virtual void	attachMe(CCSprite* child);
	virtual CCSprite* getBodySprite();

//below is the move functions
public:
	virtual void	update(float dt);
	CCPoint			getMapPosition() const;
	virtual void	setMapPosition(int dir, int tx, int ty);
	virtual CCPoint	getSpritePosition() const;
	virtual void    setGhostZOrder(int z);
	virtual void    setZOrder(int z);
	int				getZOrder() const;
	virtual bool    isSelected(const CCPoint &touchPos);

public:
	CCSprite*		m_pBodySprite;	//the sprite that as the container of other sprites

public:
	int mType;
	unsigned int mID;
	int mTx;
	int mTy;
	int mStaticID;
};

#endif //__GHOST_H__