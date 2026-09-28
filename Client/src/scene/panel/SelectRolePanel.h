#ifndef __SelectRolePanel_H__
#define __SelectRolePanel_H__

/*
功能：任务栏，显示当前的任务或者可接，并可响应点击任务自动寻路到目标NPC
*/

#include "ext/BasePanel.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

class SelectRolePanel:public BasePanel
{
public:
	SelectRolePanel();
	~SelectRolePanel();
	static SelectRolePanel* create();
	virtual bool init();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
	void initLeft(int tag=0);
	void initRight(int tag=0);
	void menucallback(CCObject* pSender);
	void closeCallBack(CCObject* pSender);

	int m_iCurSelectType;//当前查看的页面
	bool m_bisSelf;//是否是自己的页面
	CCNode* m_pLeftNode;
	CCNode* m_pRightNode;
	CCMenuItemImage* m_pCurSelectBtn;

	bool m_bTouchInPos;
	int m_iLeftTag;
	int m_iRightTag;
	enum MyEnum
	{
		Role_Sub_Panel,
		Stone_Sub_Panel,
		Pet_Sub_Panel,
		AttrLayer,
		PetSkillLayer,
	};
};


#endif//__SelectRolePanel_H__