#ifndef __MASTER_LIST_DIALOG_H__
#define __MASTER_LIST_DIALOG_H__

/*
	拜师列表对话框
	@auth shixing
*/
#include "DialogLayer.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum MASTER_LIST_BUTTON_TAG
{
	MASTER_LIST_BUTTON_TAG_CLOSE=0,
	MASTER_LIST_BUTTON_TAG_CONFIRM,
	MASTER_LIST_BUTTON_TAG_CANCEL,
};

class MasterListDialog : public DialogLayer, public IEventListener
{
public:
	MasterListDialog();
	~MasterListDialog();

	virtual bool onInitDialog();
	CREATE_FUNC(MasterListDialog);

protected:
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

	void showErrorMessage(int errorCode);
private:
	CPItemComponents *mMasterList;

	int mCurrentIndex;
	int mMasterListOffset;

	void addListUI();
	void addListItem(const std::string &name, const char gender, const char clazz, const int level);
	void addListFinish();
	void onClickListItem(CCObject *target);

	void onCPEvent(const std::string &eventName);
};

#endif
