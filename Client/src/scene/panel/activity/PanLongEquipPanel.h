#ifndef __PanLongEquipPanel_h__
#define __PanLongEquipPanel_h__

#include "controls/CPTips.h"
#include "cocos2d.h"

using namespace cocos2d;

class CPItemComponents;
class PanLongEquipPanel : public CPTipsSub
{
public:
	PanLongEquipPanel();
	~PanLongEquipPanel();
	CREATE_FUNC(PanLongEquipPanel);
	bool init();

private:
	void initUI();

	void onList(CCObject *target);
	void onBuy(CCObject *target);
	void onClose(CCObject *target);

	CCMenuItem *getListItem(int index);

private:
	CPItemComponents *mList;

	int mCurrentIndex;
};
#endif //__PanLongEquipPanel_h__