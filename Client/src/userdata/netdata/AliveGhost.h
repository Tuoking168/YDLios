#ifndef __ALIVE_GHOST_H__
#define __ALIVE_GHOST_H__

#include "cocos2d.h"
#include <queue>
#include <map>
#include "Ghost.h"
#include "CommonType.h"
#include "utils/MacroUtils.h"
USING_NS_CC;

enum AVATAR_TYPE
{
    // 角色外观部件类型
    AVATAR_TYPE_CLOTH,        // 0: 服装/衣服外观
    AVATAR_TYPE_WEAPON,      // 1: 武器外观
    AVATAR_TYPE_WINGS,       // 2: 翅膀外观
    AVATAR_TYPE_EFFECT,       // 3: 特效/光效外观
	AVATAR_TYPE_YUANSHEN,     // 4: 元神外观
    AVATAR_TYPE_HORSE,        // 5: 坐骑身体部分
    AVATAR_TYPE_HORSEHEAD,    // 6: 坐骑头部装饰
    AVATAR_TYPE_NUMBER,       // 7: 外观类型总数（用于数组大小）

    // 特殊渲染层级标记
    AVATAR_CAST_ZORDER,       // 8: 施法效果渲染层级
    AVATAR_DAMEGE_ZORDER,     // 9: 伤害数字渲染层级
    AVATAR_SHADOW_ZORDER = -2 // -2: 阴影渲染层级
};

enum AVATAR_STATE
{
    AVATAR_ACTION_IDLE,           // 0: 待机/站立状态
    AVATAR_ACTION_WALK,           // 1: 行走状态
    AVATAR_ACTION_RUN,            // 2: 跑步状态
    AVATAR_ACTION_PREPARE,        // 3: 准备/蓄力状态
    AVATAR_ACTION_ATTACK,         // 4: 攻击状态
    AVATAR_ACTION_MAGIC,          // 5: 魔法/技能释放状态
    AVATAR_ACTION_INJURY,         // 6: 受伤状态
    AVATAR_ACTION_DIE,            // 7: 死亡状态
    AVATAR_ACTION_COUNT,          // 8: 动作状态总数
    AVATAR_ACTION_CHANGEDIRECTION, // 9: 改变方向状态
    AVATAR_ACTION_MINE            // 10: 挖矿/采集状态
};

struct StateInfo
{
	int state;
	int dir;
	int skilltype;
	int ptx;
	int pty;
	unsigned int pid;
	int resID;
	StateInfo():state(-1),dir(-1),skilltype(-1),ptx(-1),pty(-1),pid(-1),resID(-1){}
};

class CCFlashAnimation;
class SkillEffect;
class ProgressBar;
class AliveGhost : public Ghost
{
public:
	AliveGhost();
    ~AliveGhost();
	virtual bool init();

public:
	virtual void	initName();
	virtual void	runAnimation();
	virtual void	stopAnimation();
	virtual void	setOpacity(CCObject* object, GLubyte opaque);
	virtual void    setGhostZOrder(int z);

	virtual void    setNextStateCallback();
	virtual void	toBeSelected(bool issel);
	virtual void    showBeAttackedEffect(bool issel);
	virtual void    showBeFrozenEffect(bool isFrozen);

	virtual void	attach(CCLayer* target);

//below is the move functions
public:
	virtual void	update(float dt);
	virtual void	moveOneStep();
	bool			isMoving() const;
	void			forceMoveTo(int dir, int x, int y);

	virtual bool    isSelected(const CCPoint &touchPos);

public:
	virtual short	getState() const;
	virtual void	setDirection(int dir);
	virtual short	getDirection() const;
	virtual void	setState(StateInfo info);
	virtual void	setState(short state, int dir=-1);
	virtual void	setState(short state, int dir, StateInfo* info);
	virtual void	setMapPosition(int dir, int tx, int ty);
	virtual int		getNextTilePosX() const;
	virtual int		getNextTilePosY() const;
	virtual int		getNextTwoTilePosX() const;
	virtual int		getNextTwoTilePosY() const;
	virtual void	setLevel(int lv);
	virtual void    setPetRebornLv(int lv);
	virtual void    setDogSid(int lv);
	virtual void	handleHpChange(int changeHp);
	virtual void	delayHpChange( int hp,short delay );
	virtual void	delayBeAttack(int type, short delay);
	virtual void    setMP(int mp);
	virtual void	castSkill( int type, int x, int y, AliveGhost* aim );

	void handleRunRes(int tx, int ty, int dir);
	void handleWalkRes(int tx, int ty, int dir);
	void handleCollideRes(int tx, int ty, int dir);
	void handleSetPosition(int tx, int ty);

	virtual void refreshNameLabel(bool visible);

	void			setColor(const ccColor3B color);
	void			setOpacity(int opacity);

	void playEffect(CCAction* action);
	void playEffect(int skillID, bool isSrc);

	void getClothSizeByHeight(CCSize &size, CCPoint &offset) const;

	void setOwnerInfo(int ownerPID, const std::string &ownerName);
	void getOwnerInfo(int &ownerPID, std::string &ownerName);

	bool isDead();

	void setDress(int dressType, int dressID);
	int getDress(int dressType) const;

	virtual void setExData(int type, int data);
	int getExData(int type) const;

	virtual void setExStr(int type, const std::string &str);
	std::string getExStr(int type) const;

	void clearExData();

	bool hasEffectBuff(int buffID);
	
protected:
	void safeToLoad(short type, short state, const std::string& url);

	void addInjury(bool lifeChange, int data);
	void updateEffectBuff();
	bool isAttackKindState(int skillID);

private:
	void adjustClothSize();
	void forEachClothFrame(int state, int dir, SEL_CallFuncO handleFuc);
	void onAdjustClothSizeByHeight(CCObject *frame);
	void onAdjustClothSizeByArea(CCObject *frame);
protected:
	virtual void runAvatarAnimation();
	void refreshHorseAppearanceOnly();
private:
	void moveBy();
	void moveTo(int tx, int ty);
	void moveTo(int tx, int ty, float speed);

	bool isSheltered();

	void refreshNameLabelPosition();
	void refreshHPChangeList();
	void updateHpOnHead();
	void testSuitWeapon();

public:
	CCSprite*			m_pSprite[AVATAR_TYPE_NUMBER];	//the sprite that run the animations
 	CCFlashAnimation*	m_pAnimations[AVATAR_TYPE_NUMBER][AVATAR_ACTION_COUNT]; //the current animations
	int					m_nCurrentDress[AVATAR_TYPE_NUMBER][AVATAR_ACTION_COUNT];
	short				m_state;	 //the current action

	int					m_serverDir;
	int					m_serverTx;
	int					m_serverTy;

	int					m_frameCount;
	
	SkillEffect*        m_skill;

//below is data part
public:
	std::string mName;
	int mGhostGender;
	int mGhostJob;
	int mHp;	//	replace with combat data later
	int mMp;	//	replace with combat data later
	int mMaxHp;	//	replace with combat data later
	int mMaxMp;	//	replace with combat data later
	
	int mPKValue;
	int mLevel;
	int mReborn;
	int mPetReborn;
	int mDogSid;

	struct HPChangeDelay
	{
		int m_nHpChangeDelay;
		int m_nHpChange;
		int m_nChangType;
	};
	typedef std::vector<HPChangeDelay> HpChangeList;
	HpChangeList	m_nHpChangeList;

	typedef std::queue<StateInfo> StateQueue;
	StateQueue m_statelist;

protected:
	CCSprite *m_pSprMofadun;
	CCSprite *m_pSprBeAttackedCircle;
	CCSprite* m_sprShadow;
	CCLabelTTF *m_disName;
	ProgressBar *m_pHpBarOnHead;
	CCSprite *m_pHpBarBkg;
	CCSprite* m_pEffectSprite;

private:
	int	m_direction; //the current direction

	int mOwnerPid;
	std::string mOwnerName;

	int	m_nDress[AVATAR_TYPE_NUMBER]; // the id of animation for each type
	int mRealWeapon;

	typedef std::map<int, int> ExData;
	ExData mExData;

	typedef std::map<int, std::string> ExStr;
	ExStr mExStr;

	CCSize mClothSizeByHeight;
	CCPoint mClothOffsetByHeight;

	CCSize mClothSizeByArea;
	CCPoint mClothOffsetByArea;

	float mHPChangeDelayTime;
};

///////////GhostSelectedAnim///////////////////////////////////////////
class GhostSelectedAnim : public CCSprite
{
public:
	static GhostSelectedAnim *node();

	void show();
	void hide();

private:
	CP_MAKE_STATIC_CLASS(GhostSelectedAnim);
};

#endif //__ALIVE_GHOST_H__