#ifndef __HERO_MODEL_H__
#define __HERO_MODEL_H__

#include "cocos2d.h"
#include "AliveGhost.h"
USING_NS_CC;

class CCFlashAnimation;
class GhostManager;

class HeroModel
{
public:
	HeroModel();
	HeroModel(int type);
    ~HeroModel();
	static HeroModel* create();
	virtual bool init();

public:
	void	update(AliveGhost *ghost);
	void    setPosition(CCPoint position);
	void    stopAnimation();
	void    runAnimation();

public:
	void	attach(CCNode* target);
	void    turnRight();
	void    turnLeft();

private:
	void addNewDress();
	void refreshWingsZOrder();
	void refreshWeaponZOrder();
	
public:
	static const std::string AVATAR_TYPE_NAME[AVATAR_TYPE_NUMBER];
	static const std::string AVATAR_TYPE_DIR_NAME[AVATAR_TYPE_NUMBER];

private:
	CCSprite*			m_pBodySprite;
	CCSprite*			m_pSprite[AVATAR_TYPE_NUMBER];	//the sprite that run the animations
 	CCFlashAnimation*	m_pAnimations[AVATAR_TYPE_NUMBER]; //the current animations
	int					m_direction; //the current direction
	int					m_nDress[AVATAR_TYPE_NUMBER];
	bool				m_bNewDress[AVATAR_TYPE_NUMBER];
};

#endif //__HERO_MODEL_H__