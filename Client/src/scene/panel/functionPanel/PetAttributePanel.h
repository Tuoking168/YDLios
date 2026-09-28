#ifndef __PetAttribute_PANEL_H__
#define ___PetAttribute_PANEL_H__

// avatar PetAttribute panel

#include "CommonPanel.h"
#include "event/EventListener.h"
#include "ext/GeneralMenuListener.h"
#include "ext/GeneralMenu.h"
#include "ext/CCTabelViewEx.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "userdata/UserPetData.h"
#include "ext/PartPanel.h"
#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CCTableViewEx;
class PetAttributePanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	PetAttributePanel();
	virtual ~PetAttributePanel();
	virtual bool init();
	CREATE_FUNC(PetAttributePanel);
	virtual void handleEvent(int channel);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
		
	
public:
	CC_PROPERTY(CCLayer*, m_pMainMenu,MainMenu);
	virtual void updateList();


protected:
	GeneralMenu* m_pTopMenu;
	GeneralMenu* m_pBottomMenu;
	CCTableViewEx *pTabelView;

	int mHeight;


};

//----------------------------------------------------------------------------------//


class PetBaseMenu:public CCLayer
{
public:
	PetBaseMenu();
	virtual ~PetBaseMenu();
	CREATE_FUNC(PetBaseMenu);
	virtual bool init();
	virtual void initFirstPart();
	virtual void initSecondPart();
	virtual void initThirdPart();


private:
	void menuCallBack(CCObject* pSender);

	enum MyEnum
	{
		tag_advance,
		tag_speattr,
	};
protected:
	GeneralMenu* m_pFirstMenu;
	GeneralMenu* m_pSecondMenu;
	GeneralMenu* m_pThirdMenu;	
	int mHeight;
	int m_iCurrentPetiid;
	UserPet* m_pPet;
};


////////////////////////////////////////////////////////////////////////////////////////
//进阶属性

class PetAdvancedPanel : public PartPanel,public IEventListener
{
public:
	PetAdvancedPanel();
	virtual ~PetAdvancedPanel();
	CREATE_FUNC(PetAdvancedPanel);
	virtual bool init();
private:
	void initInfo();
	void blockCallBack(CCObject* pSender);
	void menuCallBack(CCObject* pSender);
	void checkAdvanceCnt();
	void onCPEvent(const std::string &eventName);
	void ItemCallBack(CCObject* pSender);
private:
	int m_iAttrCnt;
	CCMenu* m_pMenu;
	bool m_bBlock[3];
	bool m_bVcoin;
	CCLabelTTF* m_pLabelVcoin;
	enum MyEnum
	{
		tag_cancel = 0,
		tag_change,
		tag_vcoin = 100,
	};
};



////////////////////////////////////////////////////////////////////////////////////////
//极品属性

class PetSpeAttrPanel : public PartPanel,public IEventListener
{
public:
	PetSpeAttrPanel();
	virtual ~PetSpeAttrPanel();
	CREATE_FUNC(PetSpeAttrPanel);
	//static PetSpeAttrPanel* create();
	virtual bool init();
private:
	void blockCallBack(CCObject* pSender);
	void menuCallBack(CCObject* pSender);
	void initInfo();
	void ItemCallBack(CCObject* pSender);
	void onCPEvent(const std::string &eventName);

private:
	bool m_bBlock;
	bool m_bVcoin;
	CCMenu* m_pMenu;
	CCSprite* pSprite;
	CCLabelTTF* m_pLabelVcoin;
	enum tagSpe
	{
		tag_cancel = 0,
		tag_change,
		tag_vcoin,
	};
};

//宠物转生界面
class CPItemComponents;
class PetReborn : public PartPanel , public IEventListener
{
public:
	PetReborn();
	~PetReborn();
	CREATE_FUNC(PetReborn);
	virtual bool init();

	static UserPet* getPet();
	static void setPet(UserPet* userPet);

private:
	void initUI();
	void initPetDesc();
	void initButton();
	void initItemPet();
	void initPetLabel(std::string str,CCPoint p , int tag);
	void onreborn(CCObject* pSender);
	void close(CCObject* pSender);
	void itemClickCallBack(CCObject* pSender);
	void onList(CCObject *target);
	void onCPEvent(const std::string &eventName);

private:
	GeneralMenu* m_pTopList;
	static UserPet* m_pUserPet;
	UserPet* m_pUserPet2;
//	UserPet* m_pets[4];
	UserPets	userpets;
	CCLabelTTF* rebornDesc;
	CCLabelTTF* hasNo;
	CPItemComponents *mList;
	int mCurrentIndex;
	std::map<int,UserPet*> m_Pets;

	enum MyEnum
	{
		Tag_name1 = 0,
		Tag_name2,
		Tag_name3,
		Tag_name4,
		Tag_Max,
	};
};

#endif