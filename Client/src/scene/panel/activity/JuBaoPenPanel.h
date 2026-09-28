#ifndef __JuBaoPenPanel_h__
#define __JuBaoPenPanel_h__

#include "controls/CPTips.h"
#include "event/IEventListener.h"
#include "cocos2d.h"

using namespace cocos2d;

class CPItemComponents;
class JuBaoPenPanel : public CPTipsSub, public IEventListener
{
public:
	JuBaoPenPanel();
	~JuBaoPenPanel();
	CREATE_FUNC(JuBaoPenPanel);
	bool init();

private:
	void initUI();
	void refresh();

	void onList(CCObject *target);
	void onBuy(CCObject *target);
	void onRecharge(CCObject *target);
	void onClose(CCObject *target);

	CCMenuItem *getListItem(int index);

	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mList;
	CCMenuItemImage *mBuyBtn;
	CCNode *mNotVipNote;

	int mCurrentIndex;
};
#endif //__JuBaoPenPanel_h__