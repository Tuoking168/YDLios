#include "scene/panel/FullScreenPanel.h"
#include "event/IEventListener.h"

class CPItemComponents;
class  VipPanel: public FullScreenPanel
{
public:
	 VipPanel();
	~ VipPanel();
	CREATE_FUNC(VipPanel);

	bool init();

private:
	void initUI();
    void initTopFrame();	
	void initBottomFrame();
	
	void refereshBottomImg();
	void refereshTopImg();
	void refereshBottomBtn();

	void onLeftBtn(CCObject *target);
	void onRightBtn(CCObject *target);
	void onRechargeBtn(CCObject *target);
	void onCPEvent(const std::string &eventName);

private:
	CCNode *mRechargeNode;
	CCNode *mNode;	
	
	CPItemComponents *mItemList;
	CCMenuItem *mLeftBtn;
	CCMenuItem *mRightBtn;
	CCLabelTTF *mPageLabel;

	int mPage;		
};

