#ifndef __SoulStone_PANEL_H__
#define __SoulStone_PANEL_H__

// Show character panel,idle animation,equipments,name,level...etc

#include "GeneralMenuListener.h"
#include "CommonPanel.h"
#include "userdata/UserItemData.h"
#include "cocos2d.h"
#include "ext/basepanel.h"
#include "event/IEventListener.h"
USING_NS_CC;

struct UserItem;
class ItemTooltip;
class SoulStonePanel : public BasePanel, public IEventListener
{
public:
	SoulStonePanel();
	virtual ~SoulStonePanel();
	static SoulStonePanel* create(bool isSelf=true);
	virtual bool init(bool isSelf);

	virtual void handleEvent(int channel);
	virtual bool    isPosInThisPanel(int pos){ return (pos < 0&& pos>=ItemPosition_Equip_Max);}
	void		    insertItem( UserItem* userItem, int pos );
	virtual CCPoint getItemPosition(int pos);
	virtual bool	getItemVisible(int pos){return true;}
	virtual void	itemClickCallBack(CCObject* pSender);
	void            showEnd();
	void onCPEvent(const std::string &eventName);


	int			 m_nPrePos;
private:
	static SoulStonePanel* characterPanel;
	GeneralMenu* m_menu;
	ItemTooltip* tooltip;
	int	         m_size;
	CCSprite*    m_pSprite;
	bool m_bIsSelf;

	static const int ITEM_UNUSE_POS = -1000;

	void initInterface(int pos);
	void initEquipSlot();

	enum MyEnum
	{
		TAG_MainSoulStone=100,
	};
};


//-------------------------------------------------------//

class SoulStoneMainPanel : public BasePanel, public IEventListener
{
public:
	SoulStoneMainPanel();
	virtual ~SoulStoneMainPanel();
	static SoulStoneMainPanel* create(int pos,bool isSelf);
	virtual bool init(int postype,bool isSelf);
	virtual void handleEvent(int channel);

public:
	void MenuCallBack(CCObject* pSender);
	void insertSoulStone(int postype);
	void ItemCallBack(CCObject* pSender);
	//	int  getStoneLvl(std::string itemname);
	virtual void	showTooltip(int tag);
	bool			isDoubleClickItem(int pos);
	virtual void	singleClickCallback( float dt );
	void onCPEvent(const std::string &eventName);
public:
	int	m_iNearPos;//最近的格子如果没有空格子则是最后一个
	GeneralMenu* m_menu;
	int m_posType;
	bool m_bIsSelf;
	int				m_nPrePos;
	float			m_nPreTime;
	bool			m_bDoubleClick;
	CCNode*	m_pImage;
private:
	CCLabelTTF * pGrade;

	int getStoneGrade();
};


#endif