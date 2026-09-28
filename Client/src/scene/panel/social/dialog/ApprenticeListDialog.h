#ifndef __APPRENTICE_LIST_DIALOG_H__
#define __APPRENTICE_LIST_DIALOG_H__

/*
	高徒列表对话框
	@auth shixing
*/
#include "DialogLayer.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum APPRENTICE_LIST_BUTTON_TAG
{
	APPRENTICE_LIST_BUTTON_TAG_CLOSE=0,
	APPRENTICE_LIST_BUTTON_TAG_CONFIRM,
	APPRENTICE_LIST_BUTTON_TAG_CANCEL,
};

class ApprenticeListDialog : public DialogLayer, public IEventListener
{
public:
	ApprenticeListDialog();
	~ApprenticeListDialog();

	virtual bool onInitDialog();
	CREATE_FUNC(ApprenticeListDialog);

protected:
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

	void showErrorMessage(int errorCode);
private:
	CPItemComponents *mApprenticeList;

	int mCurrentIndex;
	int mApprenticeListOffset;

	void addListUI();
	void addListItem(const std::string &name, const char gender, const char clazz, const int level);
	void addListFinish();
	void onClickListItem(CCObject *target);

	void onCPEvent(const std::string &eventName);
};

#endif
