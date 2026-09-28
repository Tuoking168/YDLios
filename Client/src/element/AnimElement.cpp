#include "AnimElement.h"
#include "cocos2d.h"
#include "SceneDefinition.h"
#include "CPElementHelper.h"
#include "ElementDefinition.h"

#include "ext/CCFlashAnimation.h"

#include "userdata/LayoutData.h"

using namespace cocos2d;

namespace AnimNode
{
	enum
	{
		begin = 0,

		shadow = 0,
		cloth,
		weapon,
		wings,

		end,
	};
}

/**
 * 根据实体类型获取对应的服装动画类型
 * 此函数用于映射游戏逻辑中的实体类型到动画资源系统中的动画类型
 * 
 * @param elementType 实体类型枚举值，来自CPElement::Type
 * @return 对应的动画类型枚举值，来自AnimType
 *         如果未匹配到已知类型，则返回AnimType::null表示无效类型
 */
static int getClothAnimType(int elementType)
{
	// 使用switch-case进行实体类型到动画类型的映射
	switch (elementType)
	{
	case CPElement::Type::player:		// 玩家角色
		return AnimType::cloth;		// 使用服装动画（角色外观可自定义）
		
	case CPElement::Type::pet:			// 宠物
		return AnimType::pet;		// 使用宠物专用动画
		
	case CPElement::Type::npc:			// NPC（非玩家角色）
		return AnimType::npc;		// 使用NPC动画
		
	case CPElement::Type::monster:		// 怪物
		return AnimType::monster;	// 使用怪物动画
		
	case CPElement::Type::skill:		// 技能特效
		return AnimType::effect;	// 使用特效动画
		
		// 注意：没有default分支，使用返回值作为fallback
	}
	
	// 默认返回null，表示无效或未知的动画类型
	return AnimType::null;
}
// 静态函数：根据动画节点类型和元素类型获取对应的动画类型
// 这个函数用于将外观装备映射到具体的动画资源
static int getAnimType( int animNodeType, int elementType )
{
	switch (animNodeType)
	{
	case AnimNode::cloth:
		return getClothAnimType(elementType);
	case AnimNode::weapon:
	case AnimNode::wings:
		return AnimType::weapon;
	}
	return AnimType::null;
}

///////////PlayerNode///////////////////////////////////////////////
AnimElement::AnimElement()
	:mGender(0)
	,mDirection(DIR_DOWN)
	,mAnimState(CPElement::State::idle)
{

}

AnimElement::~AnimElement()
{
	
}

AnimElement * AnimElement::create( int id, int type )
{
	return create(id, type, 0);
}

AnimElement * AnimElement::create( int id, int type, int gender )
{
	AnimElement *ret = new AnimElement;
	if (ret && ret->initWithData(id, type, gender))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool AnimElement::initWithData( int id, int type, int gender )
{
	if (!BaseElement::initWithData(id, type))
	{
		return false;
	}
	mGender = gender;

	initUI();

	return true;
}

void AnimElement::initUI()
{
	CCSprite *shadowNode = LayoutData::getSprite(CPModuleName::COMMON, "shadow");
	//getContainer()->setContentSize(shadowNode->getContentSize());
	getContainer()->addChild(shadowNode, 0, AnimNode::shadow);
}

void AnimElement::refreshShadow( bool visible )
{
	CCNode *shadowNode = getAnimNode(AnimNode::shadow);
	if (shadowNode)
	{
		shadowNode->setVisible(visible);
	}
}

void AnimElement::setCloth( int clothID )
{
	if (clothID > 0)
	{
		setAnimData(AnimNode::cloth, clothID);
	}
	else
	{
		setAnimData(AnimNode::cloth, -mGender);
	}	
}

void AnimElement::setWeapon( int weaponID )
{
	if (weaponID > 0)
	{
		setAnimData(AnimNode::weapon, weaponID);
	}
}
// 设置翅膀外观的动画元素
// 这个函数用于为角色设置翅膀的动画外观
void AnimElement::setWings( int wingsID )
{
	if (wingsID > 0)
	{
		setAnimData(AnimNode::wings, wingsID);
	}
}


void AnimElement::act( int animState, int direction )
{
	mAnimState = animState;
	mDirection = direction;
	updateAllAnim();
}

int AnimElement::getAnimState() const
{
	return mAnimState;
}

int AnimElement::getDirection() const
{
	return mDirection;
}

void AnimElement::setAnimData( int animNodeType, int data )
{
	addAnimNodeIfNeed(animNodeType);
	mIDMap[animNodeType] = data;
	updateAnim(animNodeType);
}

void AnimElement::addAnimNodeIfNeed( int animNodeType )
{
	CCNode *node = getAnimNode(animNodeType);
	if (!node)
	{
		node = CCSprite::create();
		getContainer()->addChild(node, 0, animNodeType);
	}
}

void AnimElement::updateAllAnim()
{
	for (int i = AnimNode::begin; i < AnimNode::end; i++)
	{
		updateAnim(i);
	}
}

void AnimElement::updateAnim( int animNodeType )
{
	CCNode *node = getAnimNode(animNodeType);
	CCAction *action = getAction(animNodeType);
	if (node && action)
	{
		node->stopAllActions();
		node->runAction(action);
		updateNodeZOrder(animNodeType, node);
	}
}
// 更新动画节点的渲染层级（Z-Order）
// 这个函数根据角色的方向和节点类型调整渲染顺序，解决视觉遮挡问题
void AnimElement::updateNodeZOrder( int animNodeType, cocos2d::CCNode *animNode )
{
	if (!animNode)
	{
		return;
	}

	if (animNodeType == AnimNode::wings)
	{
		if (mDirection == DIR_UP ||
			mDirection == DIR_UP_LEFT ||
			mDirection == DIR_UP_RIGHT)
		{
			getContainer()->reorderChild(animNode, 1);
		}
		else
		{
			getContainer()->reorderChild(animNode, -1);
		}
	}
	else if (animNodeType == AnimNode::weapon)
	{
		if (mDirection == DIR_DOWN)
		{
			getContainer()->reorderChild(animNode, -1);
		}
		else
		{
			getContainer()->reorderChild(animNode, 1);
		}
	}
}

cocos2d::CCNode * AnimElement::getAnimNode( int animNodeType )
{
	CCNode *container = getContainer();
	if (container)
	{
		return container->getChildByTag(animNodeType);
	}
	return NULL;
}

CCFlashAnimation * AnimElement::getAnimation( int animNodeType )
{
	CCFlashAnimation *ret = NULL;
	IDMap::iterator it = mIDMap.find(animNodeType);
	if (it != mIDMap.end())
	{
		const int animType = getAnimType(it->first, getType());
		if (animType != AnimType::null)
		{
			ret = CPElementHelper::getAnim(animType, it->second, mAnimState);
		}
	}
	return ret;
}

cocos2d::CCAction * AnimElement::getAction( int animNodeType )
{
	CCAction *ret = NULL;
	CCFlashAnimation *anim = getAnimation(animNodeType);
	if (anim)
	{
		CCActionInterval *act = anim->getAnimate(mDirection);
		if (act)
		{
			if (mAnimState != CPElement::State::die)
			{
				ret = CCRepeatForever::create(act);
			}
			else
			{
				ret = act;
			}
		}
	}
	return ret;
}

void AnimElement::visit()
{
	CCFlashAnimation *anim = getAnimation(AnimNode::cloth);
	if (anim)
	{
		CCSpriteFrame *firstFrame = anim->getSprite(DIR_UP);
		if (firstFrame)
		{
			setContentSize(firstFrame->getOriginalSize());
		}
	}
	BaseElement::visit();
}

