#ifndef __CHARACTER_PANEL_H__
#define __CHARACTER_PANEL_H__

// Show character panel,idle animation,equipments,name,level...etc

#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "event/IEventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
USING_NS_CC_EXT;

struct UserItem;
class HeroModel;
class ItemTooltip;


enum EquipPosIndex
{
	Pos_Necklace   =1, // ????
	Pos_Weapon     =2, // ????
	Pos_Huanwu     =3, // ????
	Pos_Bracelet_1 =4, // ????
	Pos_Ring_1     =5, // ???
	Pos_Jewel      =6, // ???
	Pos_Fashion    =7, // ??
	Pos_Wing       =8, // ???
	Pos_Belt       =9, // ????
	Pos_Shoes      =10, // ????
	Pos_Ring_2     =11, // ???
	Pos_Bracelet_2 =12, // ????
	Pos_Clothes    =13, // ????
	Pos_Medal      =14, // ???
	Pos_Helmet     =15, // ???
	Pos_Stuff      =16, // ????
	Pos_Foot      =17, // ??
	Pos_Yuanshen    =18, // ???
	Pos_Shenqi1      =19, // ????
	Pos_Shenqi2      =20, // ????
	Pos_Shenqi3      =21, // ????
	Pos_Shenqi4      =22, // ????
	Pos_Shenqi5      =23, // ????
	Pos_Shenqi6     =24, // ????
	Equip_Total    =24
};
                                                              
class CharacterPanel : public BasePanel, public IEventListener
{
public:
	CharacterPanel();
	virtual ~CharacterPanel();
	static CharacterPanel* create(bool isSelf=true);
	virtual bool init(bool isSelf);
	virtual void handleEvent(int channel);

	virtual bool    isPosInThisPanel(int pos){ return (pos < 0 && pos>=-Equip_Total);}
	void		    insertItem( UserItem* userItem, int pos );
	virtual CCPoint getItemPosition(int pos);
	virtual bool	getItemVisible(int pos){return true;}
	virtual void	itemClickCallBack(CCObject* pSender);
	virtual void	singleClickCallback( float dt );
	virtual void    turnFaceLeftCallBack(CCObject* pSender);
	virtual void    turnFaceRightCallBack(CCObject* pSender);
	virtual void	showTooltip(int tag);
	void            showEnd();

	bool			isDoubleClickItem(int pos);

	void			initHeroModel();
	void			hideFashionCB(CCObject* pSender);
	void			hideWeaponCB(CCObject* pSender);
	
    virtual void    turnshenqi(CCObject* pSender);//------????

	void onCPEvent(const std::string &eventName);
	
	

private:
	static CharacterPanel* characterPanel;
	CCScale9Sprite* m_bkg;          // ????
    CCSprite* m_plong;              // ?????????
    CCSprite* m_rolebkg;            // ?????????
	CCLabelTTF *mNameLabel;
	GeneralMenu* m_menu;
	GeneralMenu* m_itemmenu;
	GeneralMenu* m_RWmenu;
	GeneralMenu* wuxingpanl;
	GeneralMenu* m_FuWenMenu;


	ItemTooltip* tooltip;
	HeroModel*	 m_heroModel;
	int	         m_size;
	CCSprite*	 m_pSelectBorder;

	

	int			 m_nPrePos;
	float		 m_nPreTime;
	bool		 m_bDoubleClick;
	static const int ITEM_UNUSE_POS = -1000;

	bool m_bIsSelf;
	bool m_bInArtifactMode;
	bool m_bEquipRefreshScheduled; // delayed equip refresh already scheduled // ????????????????

	void initCharacter();
	void initEquipSlot();
	void initBaseInfo();
	void refreshEquipSlot();
};

#endif