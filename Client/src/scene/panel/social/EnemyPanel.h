#ifndef __ENEMY_PANEL_H__
#define __ENEMY_PANEL_H__

/*
	≥»ÀΩÁ√Ê
	@auth shixing
*/
#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum ENEMY_BUTTON_TAG
{
	ENEMY_BUTTON_TAG_NULL=0,
	ENEMY_BUTTON_TAG_TRACK,
};

class EnemyPanel : public BasePanel, public IEventListener
{
public:
	EnemyPanel();
	~EnemyPanel();

	bool init();
	void onEnter();
	CREATE_FUNC(EnemyPanel);

protected:
	GeneralMenu* m_pMainMenu;
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

private:
	static CCMenuItem *getRightBtn(int index);
	
	void refresh();
	void onClickListItem(CCObject *target);
	void addListItem(const std::string &name, const char gender, const char clazz, const int level);
	void addListFinish();
	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mRightBtnMenu;
	CPItemComponents *mEnemyList;

	int mCurrentIndex;
	int mEnemyListOffset;
};

#endif
