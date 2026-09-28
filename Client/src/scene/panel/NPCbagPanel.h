#ifndef __NPCbagPanel_H__
#define __NPCbagPanel_H__

// Show bag panel

#include "GeneralMenuListener.h"
#include "userdata/UserItemData.h"
#include "cocos2d.h"
#include "ext/basepanel.h"
#include "scene/panel/functionPanel/BagPanel.h"
USING_NS_CC;

class NPCbagPanel : public BasePanel
{
public:
	NPCbagPanel();
	virtual ~NPCbagPanel();

	CREATE_FUNC(NPCbagPanel);
	//static NPCbagPanel* create();
	virtual bool init();

	virtual void closeCallBack(CCObject* pSender);

private:
	void menucallback(CCObject* pSender);
	void initRightMenu(int tag);
	void initLeftMenu();
	enum MyEnum
	{
		e_PetBag	=1,
		e_RoleBag	=2,
	};

	GeneralMenu* m_pRightMenu;
	GeneralMenu* m_pBtnMenu;
	int m_iCurRightType;
	BagPanel* m_leftBag;
	
};

#endif
