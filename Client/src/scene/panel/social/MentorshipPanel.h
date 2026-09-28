#ifndef __MENTORSHIP_PANEL_H__
#define __MENTORSHIP_PANEL_H__

/*
	师徒界面
	@auth shixing
*/
#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum MENTORSHIP_BUTTON_TAG
{
	MENTORSHIP_BUTTON_TAG_NULL=0,
	MENTORSHIP_BUTTON_TAG_MASTER,
	MENTORSHIP_BUTTON_TAG_APPRENTICE,
	//MENTORSHIP_BUTTON_TAG_PICHAT,
	MENTORSHIP_BUTTON_TAG_CHAT,
	MENTORSHIP_BUTTON_TAG_CALL,
	MENTORSHIP_BUTTON_TAG_MQUIT,
	MENTORSHIP_BUTTON_TAG_MLIST,
	MENTORSHIP_BUTTON_TAG_AQUIT,
	MENTORSHIP_BUTTON_TAG_ALIST,
};

class MentorshipPanel : public BasePanel, public IEventListener
{
public:
	MentorshipPanel();
	~MentorshipPanel();

	bool init();
	void onEnter();
	CREATE_FUNC(MentorshipPanel);

protected:
	GeneralMenu* m_pMainMenu;
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

	GeneralMenu* m_pDialogMenu;// 弹出页面

private:
	static CCMenuItem *getRightBtn(int index);
	
	void refresh();
	void onClickListItem(CCObject *target);
	void addListUI();
	void addListItem(const std::string &name, const char gender, const char clazz, const int level);
	void addListFinish();
	void addMBottomButton();
	void addABottomButton();
	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mRightBtnMenu;
	CPItemComponents *mMentorshipList;

	int mCurrentIndex;
	int mCurrentListType;
	int mMentorshipListOffset;
};

#endif
