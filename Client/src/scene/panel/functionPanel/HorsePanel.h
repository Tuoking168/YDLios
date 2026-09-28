#ifndef __HorsePanel_H__
#define __HorsePanel_H__

// Show character panel,idle animation,equipments,name,level...etc

#include "cocos2d.h"
#include "ext/basepanel.h"
#include "userdata/UserPetData.h"
#include "ext/CCTabelViewEx.h"
#include "event/IEventListener.h"
#include "PartPanel.h"
USING_NS_CC;

class CPItemComponents;
class HorsePanel : public BasePanel, public IEventListener
{
public:
	HorsePanel();
	virtual ~HorsePanel();
	CREATE_FUNC(HorsePanel);
	//static Horsepanel* create();
	virtual bool init();
	virtual void handleEvent(int channel);

	void onCPEvent(const std::string &eventName);
private:
	void MenuEquipCallBack(CCObject* pSender);
	void MenuPeiYangCallBack( CCObject* pSender );
	void MenuHeadCallBack( CCObject* pSender );
	void MenuShangmaCallBack( CCObject* pSender );
	void MenuXiamaCallBack( CCObject* pSender );

	void postMsg();
	void initExp();
	void initHorseEquip();
	void initHorseModel(int idx);
	void initHorseHead();
	void showRideButtons();

	void update(float dt);
	void buttoncheck();
	void updateRightAttr();
	bool checkVcoin();
	bool checkHonor();
	void addLevelUpEffect();
	void initAll();

	void levelUp(int tag);
	void AddExp1(int tag);
	void AddExp10(int tag);
	void AddExp50(int tag);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	
private:
	static HorsePanel* horsepanel;
	GeneralMenu* m_pMainMenu;
	GeneralMenu* m_pEquipMenu;
	/*CCLabelTTF* m_pHonorLabel;*/
	CCLabelTTF* m_pVcoinLabel;
	CCLabelTTF* m_pMabianCnt;
	CCLabelTTF* m_pName;
	bool		m_bIsInitOver;

	CCLabelTTF* m_pHorseStateLabel;
	CPItemComponents *m_pList;
	CCScale9Sprite* m_pExppoint;

	enum MyEnum
	{
		TAG_HORSE_MODEL,
		TAG_Left,
		TAG_Right,
		PET_Combat,//³öÕ½
		PET_Sleep,//ÐÝÏ¢
		PET_CloseBooth,
		PET_Lock,
		TAG_HORSE_SELECT_FRAME = 999,  // ????????????

		HORSE_RideHorse,
		HORSE_XiaMa,
		HORSE_AddExpOnce,
		HORSE_AddExp10,
		HORSE_AddExp50,
		HORSE_LevelUp,

		PET_Reborn,

		PET_SKILL_MONEY,
		PET_SKILL_ITEM,
		PET_SKILL_OUT,
		PET_SKILL_HIGHOUT,

	};
};

#endif