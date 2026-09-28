//////////////////////////////////////////////////////////////////////////
//功能:实现主界面右侧几个技能的管理，包括初始化技能，添加技能，点击释放技能。
//	   并监听技能变化的信息，不断更新技能。
//时间：7/10/2013
//作者：tom
//////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_LAYER__
#define __SKILL_LAYER__

#include "cocos2d.h"
#include "event/EventListener.h"
#include "event/IEventListener.h"

const int SPIDER_PANEL_TAG = 1000;// 重复装备回收定义标签常量

using namespace cocos2d;

class AliveGhost;

class SkillLayer : public CCLayer,public EventListener, public IEventListener 
{
public:
	SkillLayer();
	~SkillLayer();

	void onEnter();
	void onExit();
	
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	//overwrite register to the touch dispatcher
	void registerWithTouchDispatcher();
	//初始化技能列表，服务器会在角色进游戏的时候发给客户端角色所具有的技能列表（包含技能的id，技能的类型如主动被动等）
	bool init();
	//调用引擎的宏命令实现create函数,其中实现了autorelease
	CREATE_FUNC(SkillLayer);

private:
	void initUI();
	void initNormal();
	void initSpecial();
	void refreshNormalAndSpecial();

	//处理技能发生改变的通知，更新技能列表，比如学习了新的技能
	void handleEvent(int channel);
	void onCPEvent(const std::string &eventName);

	//点击技能的回调，一般检查技能没有CD的话，就要像服务器发送使用技能的消息，准备使用该技能
	void useSkillCallback(CCObject* pSender);
	void useItemCallback(CCObject* pSender);

	void turnUpCallback(CCObject* pSender);
	void turnDownCallback(CCObject* pSender);

	void onSpecialSkill(CCObject *target);

	void updateSkillList();
	void updateArrowState(float angle);
	void unlockTouch();
	void showCoolDown(int skillID);
	void showCoolDown(int skillID, bool isClear);
	float getCoolDown(int skillid);

	void refreshSkillOnOff(int skillID, CCNode *skillBtn, bool isChange);
	void refreshSkillOnOff(int skillID, CCNode *skillBtn, bool isChange, const std::string &userDataKey, const std::string &onNote, const std::string &offNote);

	void removeSkillMenuChildren();

	void easyAttackCB(CCObject* pSender);
	void selectTargetBySlide(const CCPoint &curPoint);
	AliveGhost* getNextAttackPlayer();
	AliveGhost* getNextAttackMonster();

	static CCPoint s_sortRefPos;
	static bool compareGhostByDist(AliveGhost* a, AliveGhost* b);
	void updateItem();
	void updateAllAngle(float time);

	void emptyBtnCB(CCObject* pSender);
	void updateSelecttime(int time);
	void update(float delta);
	
    
	void selectBattlePet(CCObject* pSender);//宠物出战按钮
	void selectMountHorse(CCObject* pSender);//上下马按钮

    void newButtonCallback(CCObject* pSender); // 装备回收按钮的回调函数

private:
	CCLayer *mNormalLayer;
	CCLayer *mSpecialLayer;

	CCMenu* m_pSkillMenu;//存放技能按钮的Menu
	float	m_preAngle;
	CCNode*	  m_pRotateNode;//用来存放所有可以旋转的内容

	CCSprite* m_pUp; //表示技能栏是否可以继续滑动的箭头
	CCSprite* m_pDown;
	bool m_bLockTouch;

	bool mSkillMenuTouched;

	CCMenuItemImage* m_pEasyAttackBtn;
	bool m_bAttackTouch;
	bool m_bTargetSwiped;
	float m_lastSwitchY;

	CCPoint	m_beginPoint;
	CCPoint m_curPoint;

	bool m_isRotatingPannel;

	int m_iselectTime;
	int m_iselectTag;

	enum MyEnum
	{
		label_enum,
	};
};

#endif //__SKILL_LAYER__