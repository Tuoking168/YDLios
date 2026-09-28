#ifndef __SpiderPanel_PANEL_H__
#define __SpiderPanel_PANEL_H__

#include "ext/PartPanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "event/IEventListener.h"
#include "userdata/UserItemData.h"
USING_NS_CC_EXT;


class SpecialBagPanel : public PartPanel
{
public:
	static SpecialBagPanel* create(int interfacetype);
	SpecialBagPanel();
	~SpecialBagPanel();
	bool init(int interfacetype);
private:
	void closecallback(CCObject* pSender);
	void menucallback(CCObject* pSender);
	void updateBag( int type );
	void reloadRightButton();
	void updateList( int tag );
private:
	GeneralMenu* m_pMenu;
	int m_iCurType;
	int m_iInterFaceType;

	enum MyEnum
	{
		bag_panel,
	};
};
#endif//__SpiderPanel_PANEL_H__