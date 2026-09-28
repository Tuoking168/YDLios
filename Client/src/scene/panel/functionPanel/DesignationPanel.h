#ifndef __Designation_PANEL_H__
#define __Designation_PANEL_H__

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "userdata/activitydata/EmigratedData.h"
#include "ext/CCTabelViewEx.h"
#include "event/IEventListener.h"
#include "scene/panel/FullScreenPanel.h"
#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
USING_NS_CC_EXT;


//----------------------------------------------------------------------------------------------------------------------------
class Design : public CCLayer , public IEventListener
{
public:
	CREATE_FUNC(Design);
	Design();
	~Design();

	void onEnter();
	void onCPEvent(const std::string &eventName);

private:
	bool init();
	void initUI();
	void initLeftList();
	void onClick( CCObject *pSender );
	void showRight( CCObject *pSender );
	void refresh( int tag );
	void refreshLeftlist(int index);
	void addHeadName();
	void cancelHeadName();
	void refreshTime();

	CCLayer *listLayer;
	CCLayer *propertyLayer;
	CCLayer *descLayer;
	CPItemComponents *btnItemList;
	GeneralMenu* topNode;
	CCNode* downNode;
	CCMenuItemImage* btn;
	CCLabelTTF* btnLabel ;
	CCMenuItemSprite* currentBtn;

	CCLabelTTF* m_pTime;
	CCLabelTTF* time_label;
	int m_iOddTime;
	int durationgene;
	int currentIndex;
	enum MyEnum
	{
		tag_peidai = 1,
		tag_quxiao = 2,
		tag_notOwn = 3,
	};
};

#endif