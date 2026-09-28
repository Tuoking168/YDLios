#ifndef __SYSTEM_SETTING_H__
#define __SYSTEM_SETTING_H__

#include "scene/panel/guide/GuidePanel.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class SystemSetting : public BaseNotePanel
{
public:
	SystemSetting();
	~SystemSetting();
	bool init();
	CREATE_FUNC(SystemSetting);
	void onEnter();
private:
	void initUI();
	void onClick(CCObject *target);
};

class AccountInfo : public CCLayer
{
public:
	AccountInfo();
	~AccountInfo();
	virtual bool init();
	CREATE_FUNC(AccountInfo);
	virtual void onEnter();
private:
	void initUI();
	void initUsDesc();
	void initButton();
	void onClick(CCObject *target);
	void onClose(CCObject *target);

	std::string userName;
	std::string userPwd;
};

#endif//__SYSTEM_SETTING_H__