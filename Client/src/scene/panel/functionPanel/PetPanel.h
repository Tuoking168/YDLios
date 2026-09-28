#ifndef __Pet_PANEL_H__
#define __Pet_PANEL_H__

// Show character panel,idle animation,equipments,name,level...etc

#include "cocos2d.h"
#include "ext/basepanel.h"
#include "userdata/UserPetData.h"
#include "ext/CCTabelViewEx.h"
#include "event/IEventListener.h"
#include "PartPanel.h"
USING_NS_CC;


class PetPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate, public IEventListener
{
public:
	PetPanel();
	virtual ~PetPanel();
	CREATE_FUNC(PetPanel);
	//static PetPanel* create();
	virtual bool init();
	virtual void handleEvent(int channel);

	void onCPEvent(const std::string &eventName);
private:
	virtual void initPetBase();
	virtual void initPetAnimation();
	void MenuCallBack(CCObject* pSender);
	void postMsg();
	void initExp();
	void initHPandSPEED();
	void initPetInfo();
	void initPetBtn();
	void update(float dt);
	void buttoncheck();
	void updateRightAttr();
	bool  checkVcoin();
	bool  checkHonor();
	void addLevelUpEffect();
	void initAll();
	void petlock();
	void initStatusWords();

	void useHonorToUp(int tag);
	void useVcoinToUp(int tag);
	void oneKeyUp(int tag);
	void lockpet(int tag);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	static PetPanel* petPanel;
	GeneralMenu* m_pMainMenu;
	CCLabelTTF* m_pHonorLabel;
	CCLabelTTF* m_pVcoinLabel;
	CCLabelTTF* m_pCntXiangquan;
	UserPet*    m_pUserPet;
	CCTableViewEx* m_pTabelView;
	int			m_iCurPage;
	bool		m_bIsInitOver;
	CCLabelTTF* m_pPetStateLabel;

	enum MyEnum
	{
		TAG_Left,
		TAG_Right,
		PET_Combat,//³öÕ½
		PET_Sleep,//ÐÝÏ¢
		PET_CloseBooth,
		PET_Lock,
		PET_HonorUP,
		PET_VcoinUP,

		PET_OneKeyUp,
		PET_Reborn,

		PET_SKILL_MONEY,
		PET_SKILL_ITEM,
		PET_SKILL_OUT,
		PET_SKILL_HIGHOUT,

	};
};

#endif