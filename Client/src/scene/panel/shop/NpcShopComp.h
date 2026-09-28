#ifndef __NPC_SHOP_COMP_H__
#define __NPC_SHOP_COMP_H__

#include "ext/BasePanel.h"

class NpcShopPanel;
class BagPanel;

class NpcShopComp : public BasePanel
{
public:
	NpcShopComp();
	~NpcShopComp();
	bool init();
	CREATE_FUNC(NpcShopComp);

private:
	void hide();
	void tabCallback(CCObject* pSender);
	void bottomBtnCallback(CCObject* pSender);
	void setBagVisibility(bool visible);
	void setPetBagVisibility(bool visible);
	void setEquipedVisibility(bool visible);
	enum NpcShopCompTag
	{
		TAG_NPC_COMP_BAG,
		TAG_NPC_COMP_PET_BAG,
		TAG_NPC_COMP_EQUIPTED,
		TAG_SHOP_FIX,
		TAG_SHOP_FIXALL,
		TAG_SHOP_SELL,
	};
protected:
	NpcShopPanel*	m_pNpcShopPanel;
	BagPanel*		m_pBagPanel;
	BagPanel*	    m_pPetBagPanel;
	BagPanel*		m_pRoleBagPanel;
	CCMenuItem*		m_pBagTab;
	CCMenuItem*		m_pPetBagTab;
	CCMenuItem*		m_pEquipedTab;
public:
	static int _s_state;
};

#endif//__NPC_SHOP_COMP_H__