#include "HeroModel.h"
#include "GameRole.h"
#include "SceneDefinition.h"

#include "userdata/SystemData.h"
#include "userdata/UserData.h"
#include "userdata/GameData.h"
#include "ext/CCFlashAnimation.h"

// HeroModel类中的静态常量数组定义
// 这些数组用于映射外观类型到对应的目录名称和显示名称

// 外观类型对应的资源目录名称数组
// 用于构建动画资源文件的路径
const std::string HeroModel::AVATAR_TYPE_DIR_NAME[AVATAR_TYPE_NUMBER] = {"cloth", "weapon","wings"};

const std::string HeroModel::AVATAR_TYPE_NAME[AVATAR_TYPE_NUMBER] = {"cloth", "weapon","wings"};


HeroModel::HeroModel()
: m_direction(4)
{
	for (int type =0; type<AVATAR_TYPE_NUMBER; type++)
	{
		m_pSprite[type] = NULL;
		m_pAnimations[type] = NULL;
		m_nDress[type] = 0;
		m_bNewDress[type] = false;
	}
}

HeroModel::~HeroModel()
{
	for (int type =AVATAR_TYPE_CLOTH; type<AVATAR_TYPE_NUMBER; type++)
	{
		if(m_pSprite[type])
		{
			m_pBodySprite->removeChild(m_pSprite[type],true);
			m_pSprite[type] = NULL;
		}
		if(m_pAnimations[type])
		{
			m_pAnimations[type] = NULL;
		}
	}
}

HeroModel* HeroModel::create()
{
	HeroModel* pHero = new HeroModel();
	if(pHero->init())
	{
		return pHero;
	}
	return NULL;
}

bool HeroModel::init()
{
	m_pBodySprite = CCSprite::create();
	if(!m_pBodySprite)
	{
		return false;
	}
	return true;
}

void HeroModel::update(AliveGhost *ghost)
{
	for ( int index = AVATAR_TYPE_CLOTH; index < AVATAR_TYPE_EFFECT; index ++ ) 
	{
		m_bNewDress[index] = false;
		const int &dressID = ghost->getDress(index);
		if(m_nDress[index]!= dressID)
		{
			if(m_nDress[index])
			{
				if(m_pSprite[index])
				{
					m_pAnimations[index] = NULL;
					m_pBodySprite->removeChild(m_pSprite[index],true);
					m_pSprite[index] = NULL;
				}
			}

			if (dressID)
			{
				char url[64];
				sprintf(url,"%s_%d", SystemData::getAnimationName(dressID, GHOST_TYPE_THIS, index, ghost->mGhostGender).c_str(), AVATAR_ACTION_IDLE);
				std::string strUrl = url;
				m_pAnimations[index] = SystemData::getAnimation(strUrl);
				m_pSprite[index] = CCSprite::create();
				m_bNewDress[index] = true;
			}
			stopAnimation();
			m_nDress[index] = dressID;
		}
	}
	addNewDress();
	runAnimation();
}

void HeroModel::attach( CCNode* target )
{
	target->addChild(m_pBodySprite);
}

void HeroModel::turnRight()
{
	m_direction = ((m_direction-1)+8)%8;
	runAnimation();
}

void HeroModel::turnLeft()
{
	m_direction = (m_direction+1)%8;
	runAnimation();
}

void HeroModel::setPosition( CCPoint position )
{
	m_pBodySprite->setPosition(position);
}

void HeroModel::stopAnimation()
{
	for(int i=AVATAR_TYPE_CLOTH; i<AVATAR_TYPE_NUMBER; i++)
	{
		if(m_pSprite[i])
		{
			m_pSprite[i]->stopAllActions();
		}
	}
}

/**
 * HeroModel::runAnimation - 角色动画播放函数
 * 
 * 功能描述：
 * 1. 遍历角色所有部位（从服装类型开始到全部部位类型）
 * 2. 对每个已穿戴且有效的部位执行动画播放
 * 3. 最后刷新翅膀和武器的显示层级
 * 
 * 动画播放逻辑：
 * - 仅处理已穿戴（m_nDress[i]非空）、精灵存在（m_pSprite[i]非空）、动画资源存在（m_pAnimations[i]非空）的部位
 * - 获取当前方向（m_direction）对应的动画动作
 * - 停止该部位所有现有动作，避免动作叠加
 * - 以永久重复的方式运行动画
 * 
 * 后续处理：
 * 1. refreshWingsZOrder() - 刷新翅膀的显示层级（确保正确遮挡关系）
 * 2. refreshWeaponZOrder() - 刷新武器的显示层级
 */
void HeroModel::runAnimation()
{
	// 遍历所有部位类型：从服装类型开始，到部位类型总数结束
	for(int i = AVATAR_TYPE_CLOTH; i < AVATAR_TYPE_NUMBER; i++)
	{
		// 条件检查：部位已穿戴、精灵存在、动画数据存在
		if(m_nDress[i] && m_pSprite[i] && m_pAnimations[i])
		{	
			// 获取当前方向对应的动画动作
			CCActionInterval *action = m_pAnimations[i]->getAnimate(m_direction);
			
			// 如果动画动作有效
			if (action)
			{
				// 停止该部位所有当前动作
				m_pSprite[i]->stopAllActions();
				
				// 运行动画（永久重复播放）
				m_pSprite[i]->runAction(CCRepeatForever::create(action));
			}
		}
	}
	
	// 刷新显示层级（确保视觉正确性）
	refreshWingsZOrder();	// 翅膀层级调整
	refreshWeaponZOrder();	// 武器层级调整
}

void HeroModel::addNewDress()
{
	for(int i=AVATAR_TYPE_CLOTH; i<AVATAR_TYPE_NUMBER; i++)
	{
		if(m_nDress[i])
		{	
			if(m_bNewDress[i])
			{
				m_pBodySprite->addChild(m_pSprite[i]);
				m_bNewDress[i] = false;
			}
		}
	}
}

// 刷新翅膀的渲染层级
// 功能：根据角色朝向调整翅膀在身体精灵前或后渲染
void HeroModel::refreshWingsZOrder()
{
	// 1. 获取翅膀精灵
	CCSprite *wings = m_pSprite[AVATAR_TYPE_WINGS];
	
	// 2. 如果翅膀精灵存在，则调整其渲染层级
	if (wings)
	{
		// 3. 判断角色朝向是否为向上方向
		// 当角色朝上时，翅膀应该在身体后面
		// 当角色朝下时，翅膀应该在身体前面
		if (m_direction == DIR_UP ||         // 正上方向
			m_direction == DIR_UP_LEFT ||    // 左上方向
			m_direction == DIR_UP_RIGHT)     // 右上方向
		{
			// 4. 角色朝上时，翅膀放在身体后面（ZOrder较小）
			// 参数1表示较低的渲染层级，在身体后面
			m_pBodySprite->reorderChild(wings, 1);
		}
		else
		{
			// 5. 角色朝其他方向时，翅膀放在身体前面（ZOrder较大）
			// 参数-1通常表示较高的渲染层级，在身体前面
			// 注意：不同引擎ZOrder系统可能不同，这里-1可能表示最前面
			m_pBodySprite->reorderChild(wings, -1);
		}
	}
	
	// 注意：这里假设翅膀是m_pBodySprite的子节点
	// 通过reorderChild重新调整同一父节点下的子节点渲染顺序
}

/**
 * HeroModel::refreshWeaponZOrder - 刷新武器显示层级
 * 
 * 功能描述：
 * 根据角色当前朝向，动态调整武器精灵在身体精灵（m_pBodySprite）中的显示层级（Z-Order）。
 * 主要用于处理武器与身体之间的遮挡关系，确保视觉正确性。
 * 
 * 逻辑规则：
 * 1. 当角色朝下（DIR_DOWN）时：武器显示在身体下方（Z-Order = -1）
 * 2. 当角色朝其他方向时：武器显示在身体上方（Z-Order = 1）
 * 
 * 注意事项：
 * - 仅当武器精灵（weapon）存在时执行层级调整
 * - 调整的是武器在身体精灵子节点中的层级顺序
 * - 通过负值和正值控制前后遮挡关系
 */
void HeroModel::refreshWeaponZOrder()
{
	// 获取武器精灵（通过部位类型索引）
	CCSprite *weapon = m_pSprite[AVATAR_TYPE_WEAPON];
	
	// 确保武器精灵存在
	if (weapon)
	{
		// 根据当前朝向决定武器显示层级
		if (m_direction == DIR_DOWN)
		{
			// 朝下时：武器在身体下方（被身体遮挡）
			m_pBodySprite->reorderChild(weapon, -1);
		}
		else
		{
			// 其他方向：武器在身体上方（遮挡身体）
			m_pBodySprite->reorderChild(weapon, 1);
		}
	}
}
