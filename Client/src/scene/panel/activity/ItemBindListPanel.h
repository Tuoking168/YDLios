#ifndef __ItemBindListPanel_h__
#define __ItemBindListPanel_h__

#include "controls/CPTips.h"
#include "cocos2d.h"

using namespace cocos2d;

class CPItemComponents;
class ItemBindListPanel : public CPTipsSub
{
public:
	ItemBindListPanel();
	~ItemBindListPanel();
	CREATE_FUNC(ItemBindListPanel);
	bool init();

private:
	bool initUI();
	void ItemOnList();
	void onList(CCObject *target);
	void onconfirm(CCObject *target);
	void onClose(CCObject *target);
	int pos2sid(int pos);
	
	CCMenuItem *getListItem(int index);

private:
	CPItemComponents *mList;

	int mCurrentIndex;
};
#endif //__ItemBindListPanel_h__