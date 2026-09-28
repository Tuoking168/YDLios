#include "ItemGhost.h"
#include "UserDataModule.h"
#include "MainUIModule.h"
#include "EffectDefinition.h"
#include "userdata/UserItemData.h"
#include "scene/Game.h"
#include "scene/GameAlive.h"
#include "scene/panel/EffectSprite.h"

#include "ext/CCFlashAnimation.h"

#include "userdata/LayoutData.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/StaticData.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/mapdata/PixesMap.h"
#include "ItemDefinition.h"
#include "userdata/luadata/LuaData.h"


#define ITEM_Z_ORDER	-50000
#define ITEM_NAME_Z_ORDER 10000


ItemGhost::ItemGhost()
: m_disName(NULL)
,mPosterBoard(NULL)
,mPosterLabel(NULL)
,mCount(0)
{
	mName = "item";
}

ItemGhost::~ItemGhost()
{
 	if (m_pBodySprite)
	{
		m_pBodySprite->stopAllActions();
 		m_pBodySprite->release();
		m_pBodySprite = NULL;
	}

	if (mType == GHOST_TYPE_MAP_ITEM &&
		m_disName)
	{
		m_disName->removeFromParent();
		m_disName->release();
		m_disName = NULL;
	}
}

ItemGhost* ItemGhost::create()
{
	ItemGhost* pGhost = new ItemGhost();
	if (pGhost)
	{
		pGhost->autorelease();
		return pGhost;
	}
	return NULL;
}

bool ItemGhost::init()
{
	if (m_pBodySprite)
	{
		m_pBodySprite->release();
		m_pBodySprite = NULL;
	}

	if (mType == GHOST_TYPE_MAP_ITEM)
	{
		return initItem();
	}
	else if(mType == GHOST_TYPE_SKILL)
	{
		return initSkill();
	}
	else if(mType == GHOST_TYPE_COLLECTION)
	{
		return initMarket();
	}
	return false;	
}

/**
 * 初始化幽灵物品
 * 
 * 该方法用于创建并配置一个幽灵物品的显示对象，包括加载图标、设置位置、添加特效等
 * 幽灵物品通常指地图上可被拾取但尚未被拾取的物品实体
 * 
 * @return bool 初始化是否成功，true表示成功，false表示失败
 */
bool ItemGhost::initItem()
{
	// 1. 加载物品图标精灵
	m_pBodySprite = LayoutData::getItemIcon(mStaticID);
	if (!m_pBodySprite) return false;
	
	m_pBodySprite->retain();
	m_pBodySprite->setScale(LayoutData::getFloat(CPModuleName::COMMON, "itemIconScale"));
	setMapPosition(0, mTx, mTy);
	setGhostZOrder(-1);
	GameData::getGhostManager()->addGhost(this);
	
	LuaData::getProp(LuaData::ITEM, mStaticID, "name", mName);
	initName();
	
	// 8. 检查是否有guangzhu属性
	int guangzhuValue = 0;
	bool hasGuangzhu = LuaData::getProp(LuaData::ITEM, mStaticID, "guangzhu", guangzhuValue);
	
	// 9. 创建特效
	CCSprite* pEffect = NULL;
	
	if (hasGuangzhu)
	{
		// 有guangzhu属性，根据值选择对应的光柱特效
		switch (guangzhuValue)
		{
		case 1:
			pEffect = EffectSprite::create(Effect::effect_item_ghost_guangzhu1);
			break;
		case 2:
			pEffect = EffectSprite::create(Effect::effect_item_ghost_guangzhu2);
			break;
		case 3:
			pEffect = EffectSprite::create(Effect::effect_item_ghost_guangzhu3);
			break;
		case 4:
			pEffect = EffectSprite::create(Effect::effect_item_ghost_guangzhu4);
			break;
		case 5:
			pEffect = EffectSprite::create(Effect::effect_item_ghost_guangzhu5);
			break;
		default:
			// guangzhu值不是1、2、3，使用默认星星
			pEffect = EffectSprite::create(Effect::effect_item_ghost_star);
			break;
		}
	}
	else
	{
		// 没有guangzhu属性，使用默认星星
		pEffect = EffectSprite::create(Effect::effect_item_ghost_star);
	}
	
	if (pEffect)
	{
		pEffect->setPosition(ccp(PixesMap::TILE_WIDTH/2, PixesMap::TILE_HEIGHT/2));
		attachMe(pEffect);
	}
	
	return true;
}
/**
 * 初始化技能实体（ItemGhost）
 * 创建技能实体并设置其动画效果，通常用于技能特效、掉落物等游戏对象
 * 
 * @return bool 初始化是否成功
 *         - true: 初始化成功
 *         - false: 精灵创建失败
 */
bool ItemGhost::initSkill()
{
	// 1. 创建基础精灵（技能实体的主显示对象）
	m_pBodySprite = CCSprite::create();
	if (!m_pBodySprite)		// 检查精灵创建是否成功
	{
		return false;		// 创建失败，返回false
	}

	// 2. 保留精灵引用计数，防止被自动释放
	m_pBodySprite->retain();
	
	// 3. 从Lua配置中获取技能动画名称
	std::string path = "effect/";			// 特效资源的基础路径
	std::string anim = "";					// 存储动画名称
	std::string key  = "anim";				// Lua配置表中的字段名
	LuaData::getProp(LuaData::SKILLENT,	// 技能实体配置表
	                 mStaticID,				// 技能静态ID
	                 key,					// 字段名："anim"
	                 anim);					// 输出的动画名称
	anim = path + anim;						// 构建完整资源路径
	
	// 4. 设置技能实体的地图位置和渲染层级
	setMapPosition(0, mTx, mTy);			// 设置地图坐标（0可能表示地图ID）
	setGhostZOrder(ITEM_Z_ORDER);			// 设置渲染层级（物品层级）
	
	// 5. 将技能实体添加到游戏实体的管理器中
	GameData::getGhostManager()->addGhost(this);
	
	// 6. 创建并运行动画效果
	CCFlashAnimation *pBlinkStar = SystemData::getAnimationOneDir(anim);	// 加载动画
	CCSprite *pStar = CCSprite::create();	// 创建动画精灵
	pStar->setPosition(CCPointZero);		// 设置位置为相对坐标(0,0)
	attachMe(pStar);						// 将动画精灵附加到主精灵上
	// 运行动画（循环播放，索引0通常表示默认动画序列）
	pStar->runAction(CCRepeatForever::create(pBlinkStar->getAnimate(0)));
	
	return true;	// 初始化成功
}

bool ItemGhost::initMarket()
{
	m_pBodySprite = LayoutData::getSprite(CPModuleName::MAIN_UI, "market");
	if (!m_pBodySprite)
	{
		return false;
	}
	m_pBodySprite->retain();
	setMapPosition(0, mTx, mTy);
	setGhostZOrder(-1);

	GameData::getGhostManager()->addGhost(this);

	const CCSize &bodySize = m_pBodySprite->getContentSize();
	mPosterBoard = LayoutData::getScale9Sprite(CPModuleName::MAIN_UI, "marketPosterBoard");
	mPosterBoard->setPosition(ccp(bodySize.width/2, bodySize.height));
	m_pBodySprite->addChild(mPosterBoard);

	mPosterLabel = LayoutData::getLabelTTF(CPModuleName::MAIN_UI, "marketPost");
	mPosterLabel->setPosition(LayoutData::getCenter(mPosterBoard->getContentSize()));
	mPosterBoard->addChild(mPosterLabel);

	//
	initName();
	refreshPoster();
	return true;
}

void ItemGhost::initName()
{
	const CCSize &size = m_pBodySprite->getContentSize();
	m_disName = LayoutData::getLabelTTF(CPModuleName::COMMON, "itemName");
	m_disName->setString(mName.c_str());
	if (mType == GHOST_TYPE_MAP_ITEM)
	{
		const float scale = LayoutData::getFloat(CPModuleName::COMMON, "itemIconScale");
		m_disName->retain();
		switch (GameData::getUserItemData()->getEquipColor(mStaticID))
		{
		case ItemQuality_Null:
			m_disName->setColor(ccGREEN);
			break;
		case ItemQuality_Green:
			m_disName->setColor(ccGREEN);
			break;
		case ItemQuality_Blue:
			m_disName->setColor(ccBLUE);
			break;
		case ItemQuality_Magenta:
			m_disName->setColor(ccMAGENTA);
			break;
		case ItemQuality_Yellow:
			m_disName->setColor(ccYELLOW);
			break;
		case ItemQuality_Hose:
			m_disName->setColor(ccRED);
			break;
		case ItemQuality_Tuo:
			m_disName->setColor(ccMAGENTA);
			break;
		case ItemQuality_King:
			m_disName->setColor(ccBLACK);
			break;
		default:
			m_disName->setColor(ccGREEN);
			break;
		}	
		//m_disName->setColor(ccRED);
		m_disName->setFontSize(LayoutData::getInt(CPModuleName::COMMON, "itemNameFontSize"));
		m_disName->setScale(scale);
		m_disName->setAnchorPoint(ccp(0.5f, 0.5f));
		m_disName->setPosition(m_pBodySprite->getPosition());
		CCNode *aliveLayer = Game::getGameAlive();
		if (aliveLayer)
		{
			aliveLayer->addChild(m_disName, ITEM_NAME_Z_ORDER);
		}
	}
	else
	{
		if (mType == GHOST_TYPE_COLLECTION)
		{
			int pid = 0;
			std::string ownerName;
			getOwnerInfo(pid, ownerName);
			const std::string &fullName = ownerName + LayoutData::getString(CPModuleName::COMMON, "market");
			m_disName->setString(fullName.c_str());
		}
		m_disName->setPosition(ccp(size.width/2, size.height));
		m_pBodySprite->addChild(m_disName);
	}
}

void ItemGhost::update()
{
	if (mType == GHOST_TYPE_MAP_ITEM)
	{
		if (m_disName)
		{
			const bool visible = (UserData::getIntData(HeroData::getPID(), CPUserData::SHOW_ITEMNAME) != 0);
			m_disName->setVisible(visible);
		}
	}
}

void ItemGhost::refreshPoster()
{
	if (!mPosterLabel
		|| !mPosterBoard)
	{
		return;
	}
	
	mPosterLabel->setString(mName.c_str());
	mPosterBoard->setVisible(!mName.empty());
	if (mName.empty())
	{
		const CCSize &size = m_pBodySprite->getContentSize();
		m_disName->setPosition(ccp(size.width/2, size.height));
	}
	else
	{
		m_disName->setPositionX(m_pBodySprite->getContentSize().width/2);
		m_disName->setPositionY(mPosterBoard->getPositionY() + mPosterBoard->getContentSize().height);
	}
}
