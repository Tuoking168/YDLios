#ifndef _SettingProtectPanel_H_
#define _SettingProtectPanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
USING_NS_CC_EXT;


enum SettingPro
{
	Slow_HP,
	Fast_HP,
	Slow_MP,
	Fast_MP,
	Home_Set,
	Item_Endure,
	SS_Special,
	MyEnum_Max,

};

class SettingProtectPanel :
	public BasePanel
{
public:
	SettingProtectPanel(void);
	~SettingProtectPanel(void);
	static SettingProtectPanel* create();
	virtual bool init();
	void onEnter();
	void onExit();

	virtual void    handleEvent(int channel);
private:
	void menucallback(CCObject* pSender);
	void changelifecallback(CCObject* pSender);
	void openprocallback(CCObject* pSender);
	void changesecondscallback(CCObject* pSender);
	void changeitem( CCNode* pNode);
	void clickboxitem( CCNode* pNode);
	void initUpPanel();
	void initDownPanel();

	void saveUserDate();
	CCLayer* getItemSetting(int tag);
	CCLayer* getSSSpecial();

	enum MyEnum
	{

		LabelValue	=	100,
	};

	int taglist[MyEnum_Max];

	struct setData
	{
		bool m_open;
		int  m_life;
		int  m_itemSid;
		int  m_seconds;
	};
	typedef std::map<int,setData> setDataMap;
	setDataMap m_setData;

	CCNode* m_CurNode;
	int m_iCurClickBoxID;
};

#endif//_SettingProtectPanel_H_