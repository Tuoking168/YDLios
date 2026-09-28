#ifndef __IconTip_PANEL_H__
#define __IconTip_PANEL_H__


#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
#include "event/IEventListener.h"
USING_NS_CC_EXT;

class GeneralMenu;

//---------------------------------------------------------/
class CCMenuItemImageEx : public CCMenuItemImage
{
public:
	CCMenuItemImageEx();
	~CCMenuItemImageEx();

	static CCMenuItemImageEx *create( const std::string& key );
	bool  initbyplist(const std::string& key);
public:
	void setExData(int dataX, int dataY, int dataZ);
	int getDataX();
	int getDataY();
	int getDataZ();

private:
	int mDataX;
	int mDataY;
	int mDataZ;
};

class IconTipPanel : public BasePanel, public IEventListener
{
public:
	IconTipPanel();
	~IconTipPanel();
	virtual bool init();
	static IconTipPanel* create();

	virtual void handleEvent(int channel);

	void onCPEvent(const std::string &eventName);

	void removeIcon(int tag,int data=0);
private:
	void addIcon(int tag,int data=0);
	void refreshList();
	void menucallback(CCObject* pSender);
	CCMenuItemImageEx* createIcon(int tag,int data);

	void initCheckList();

	GeneralMenu* m_pMainMenu;

private:
	bool IsBagFull();
	void CheckItemEndure();
	bool CheckMedicine();
	bool CheckRebornReq();
	int  CheckHasHollowItem();
	bool CheckIsSellOut();
	void CheckHasRelationApply();

	bool CheckRubishEquip();
	bool isMineScene();
	bool equipedMineTools();
	bool getMineToolsInBag(int &iid, int &sid);

	int getItemEndure();

private:
	void showBossTips(int id);
	enum MyEnum
	{
		boss_tips_panel,
	};
};

//----------------------------------------------------------------------------------------------------//

class BossTipsPanel: public BasePanel
{
public:
	BossTipsPanel();
	~BossTipsPanel();
	virtual bool init(int id);
	static BossTipsPanel* create(int id);

	void updatebossid(int id);
private:
	void initUI();
	void close(CCObject* pSender);
	void closeself();

	void clickShoes(CCObject* pSender);
	void clickName(CCObject* pSender);
	void clickboss(CCObject* pSender);
private:
	int m_iBossId;
	int m_iBoosSid;
	CCMenuItemFont *mapNameBtn;
};

class CopyNotifyTipPanel: public BasePanel
{
public:
	CopyNotifyTipPanel();
	~CopyNotifyTipPanel();
	virtual bool init();
	CREATE_FUNC(CopyNotifyTipPanel);

private:
	void initUI();
	void initCopyDesc();
	void close(CCObject* pSender);
	void clickShoes(CCObject* pSender);

private:
	int copyID;
	CCLabelTTF* m_textDesc;
	CCLabelTTF* m_copyName;
	CCLabelTTF* m_recLvl;
	CCLabelTTF* m_recBattel;

};

#endif//__Target_PANEL_H__