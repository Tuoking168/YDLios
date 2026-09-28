#include "Ghost.h"
#include "userdata/SystemData.h"
#include "userdata/UserData.h"
#include "userdata/GameData.h"
#include "ext/CCFlashAnimation.h"
#include "userdata/mapdata/PixesMap.h"
#include "common/MsgPacket.h"


Ghost::Ghost() :
//m_ptMapPos(74*PixesMap::TILE_WIDTH,128*PixesMap::TILE_HEIGHT)
mTx(0)
, mTy(0)
, mType(-1)
, mID(0)
, m_pBodySprite(NULL)
,mStaticID(0)
{
	autorelease();
	retain();
}

Ghost::Ghost(int type) :
//m_ptMapPos(74*PixesMap::TILE_WIDTH,128*PixesMap::TILE_HEIGHT)
mTx(0)
, mTy(0)
, mType(-1)
, mID(0)
, m_pBodySprite(NULL)
,mStaticID(0)
{
	autorelease();
	retain();
	
	mType = type;
}

Ghost::~Ghost()
{
}

void Ghost::init(CCSprite* base)
{
	m_pBodySprite = base;
}

void Ghost::attach( CCLayer* target )
{
	if(!target || !m_pBodySprite)
	{
		CCLog("Ghost attach failed!");
		return;
	}
	target->addChild(m_pBodySprite);
}

void Ghost::attachMe(CCSprite* child)
{
	if(!child || !m_pBodySprite)
	{
		return;
	}

	m_pBodySprite->addChild(child);
}

void Ghost::detach( CCLayer* target )
{
	if(!target || !m_pBodySprite)
	{
		return;
	}

	target->removeChild(m_pBodySprite, true);
}

CCSprite* Ghost::getBodySprite() 
{
	return m_pBodySprite;
}

CCPoint Ghost::getSpritePosition() const
{
	if(m_pBodySprite)
	{
		return m_pBodySprite->getPosition();
	}
	return CCPointZero;
}

cocos2d::CCPoint Ghost::getMapPosition() const
{
	const CCPoint &point = getSpritePosition();
	return ccp(point.x, SystemData::size_y - point.y);
}

void Ghost::setMapPosition(int dir, int tx, int ty)
{
	const CCPoint &pt = PixesMap::getPixelPoint(tx, ty);
	m_pBodySprite->setPosition(ccp(pt.x, SystemData::size_y - pt.y));
}

void Ghost::setGhostZOrder( int z )
{
	setZOrder(z);
}

void Ghost::setZOrder(int z)
{
	m_pBodySprite->_setZOrder(z);
}

int Ghost::getZOrder() const
{
	return m_pBodySprite->getZOrder();
}

void Ghost::update( float dt )
{
}

bool Ghost::isSelected( const CCPoint &touchPos )
{
	if(m_pBodySprite && mType != -1)
	{
		const CCPoint &pos = m_pBodySprite->convertToNodeSpace(touchPos);
		const CCSize &contentSize = m_pBodySprite->getContentSize();
		const CCRect &rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
		if (rect.containsPoint(pos))
		{
			return true;
		}
	}
	return false;
}