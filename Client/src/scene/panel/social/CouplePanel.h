#ifndef __COUPLE_PANEL_H__
#define __COUPLE_PANEL_H__

/*
	°éÂÂ½çÃæ
	@auth shixing
*/
#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum COUPLE_BUTTON_TAG
{
	COUPLE_BUTTON_TAG_NULL=0,
	COUPLE_BUTTON_TAG_CHAT,
	//COUPLE_BUTTON_TAG_PICHAT,
	COUPLE_BUTTON_TAG_CALL,
	COUPLE_BUTTON_TAG_DIVORCE,
};

class CouplePanel : public BasePanel, public IEventListener
{
public:
	CouplePanel();
	~CouplePanel();

	bool init();
	void onEnter();
	CREATE_FUNC(CouplePanel);

protected:
	GeneralMenu* m_pMainMenu;
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

private:
	static CCMenuItem *getRightBtn(int index);
	
	void refresh();
	void onClickListItem(CCObject *target);
	void addListUI();
	void addListItem(const std::string &name, const char gender, const char clazz, const int level);
	void addListFinish();
	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mRightBtnMenu;
	CPItemComponents *mCoupleList;

	int mCurrentIndex;
	int mCoupleListOffset;
};

#endif
