#ifndef __GiftConversionPanel_h__
#define __GiftConversionPanel_h__


#include "scene/panel/FullScreenPanel.h"
#include "controls/CPTips.h"

class CPChecker;
class GiftConversionPanel : public FullScreenPanel
{
public:
	GiftConversionPanel();
	~GiftConversionPanel();
	CREATE_FUNC(GiftConversionPanel);
	bool init();

private:
	void initUI();

	void onItem(CCObject *target);
	void onGetGift(CCObject *target);
	void onRecharge(CCObject *target);
	void onGetGiftByKey(const std::string &key);

	void onCPEvent(const std::string &eventName);

private:
	CPChecker *mChecker;
};

///////////GiftConversionInputPanel//////////////////////////////////////////
#include "GUI/CCEditBox/CCEditBox.h"
class GiftConversionInputPanel : public CPTipsSub
{
public:
	GiftConversionInputPanel();
	~GiftConversionInputPanel();
	CREATE_FUNC(GiftConversionInputPanel);
	bool init();

public:
	void setHandler(CCObject *target, SEL_InputPanel func);

private:
	void initUI();

	void onConfirm(CCObject *target);
	void onCancel(CCObject *target);
	void onClose(CCObject *target);

private:
	extension::CCEditBox *mInputBox;
	CCObject *mTarget;
	SEL_InputPanel mHandleFunc;
};

#endif //__GiftConversionPanel_h__