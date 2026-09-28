#ifndef __RenamePanel_h__
#define __RenamePanel_h__

#include "cocos2d.h"
#include "controls/CPTips.h"
#include "GUI/CCEditBox/CCEditBox.h"

using namespace cocos2d;

class RenamePanel : public CPTipsSub
{
public:
	RenamePanel();
	~RenamePanel();
	CREATE_FUNC(RenamePanel);
	bool init();

private:
	void initUI();

	void onConfirm(CCObject *target);
	void onCancel(CCObject *target);
	void onClose(CCObject *target);

private:
	extension::CCEditBox *mInputBox;
	int mRenameType;
};
#endif //__RenamePanel_h__