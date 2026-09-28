#ifndef __COMMON_PANEL_H__
#define __COMMON_PANEL_H__

#include "event/EventListener.h"
#include "cocos2d.h"
#include "userdata/UserItemData.h"
USING_NS_CC;

// Base Panel for function panel,store staus of every single panel,init common top menu bar.
class RadioGroup;

#define NOTIFICATION_POSTMSG "NOTIFICATION_POSTMSG"
#define NOTIFICATION_ADDITEMMARKET "NOTIFICATION_ADDITEMMARKET"
#define NOTIFICATION_SELLITEM "NOTIFICATION_SELLITEM"

enum TITLE_LEFT
{
	AVATAR=10,		//人物
	WRAITHSTONE,	//魂石
	PET,			//宠物
	PETBAG,			//宠物背包
	HORSE,			//坐骑  
	COMMON_TITLE_LEFT_END,
};
enum TITLE_RIGHT
{
	ATTRIBUTE=20,	//属性
	BAG,			//背包
	SKILL,			//技能
	WAREHOUSE,		//寻宝仓库
	PETSKILL,		//宠物技能
	HORSESKILL,		//坐骑技能
	COMMON_TITLE_RIGHT_END,
};

class CommonPanel : public CCLayer, public EventListener
{
private:
	CommonPanel();
	virtual ~CommonPanel();
	void hideHorseButtons(float dt); // 添加这行屏蔽坐骑
	
public:
	virtual void onEnter();
	virtual void onExit();

	static CommonPanel* create(int left = AVATAR, int right = BAG);
	virtual bool init(int tag); // init background,top common menu bar,close button...
	virtual bool initChildPanel(int left); // init child panel(left and right)
	virtual void callBack(CCObject* pSender); 
	virtual void rightTopCallBack(CCObject* pSender); 
	virtual void addCover(float width, float height);
	virtual void initRightTop(int tag);
	//CC_PROPERTY(RadioGroup*,m_pChoiceMenuRight,choiceMenuRight); 

	void selectTop(int tag);

	void postMsg(CCObject* pSender);
public:
	// Current acitive panel
	CCNode* leftCurrentPanel;
	CCLayer* rightCurrentPanel;

	int m_iCurrentLeftTop;
	int m_iCurrentRightTop;
	
	RadioGroup* choiceMenuLeft;
	RadioGroup* m_pChoiceMenuRight;

	enum MyEnum
	{
		leftMax=5,
	};
};

#endif
