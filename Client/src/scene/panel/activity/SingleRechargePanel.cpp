#include "SingleRechargePanel.h"
#include "ActivityModule.h"
#include "ErrorDefinition.h"

#include "controls/CPChecker.h"
#include "controls/CPItemComponents.h"

#include "ext/CCFlashAnimation.h"

#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/SystemData.h"
#include "userdata/ActivityData.h"
#include "userdata/FuncData.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "utils/StringUtils.h"


const int SINGLE_RECHARGE_FUNC_ID = 10;

SingleRechargePanel::SingleRechargePanel()
	:mChecker(NULL)
	,mRewards(NULL)
	,mRefreshLayer(NULL)
	,mGetBtn(NULL)
	,mCurrentIndex(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

SingleRechargePanel::~SingleRechargePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool SingleRechargePanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}	

	initUI();
	refreshDesc();
	refreshBtnState();

	return true;
}

void SingleRechargePanel::initUI()
{
	// board
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "singleRechargePanelBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "singleRechargePanelBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}	

	// rewards
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "singleRechargePanelList");
	const int itemPerLine = LayoutData::getInt(CPModuleName::ACTIVITY, "singleRechargePerLine");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "singleRechargeBianKuangInterval");
	mRewards = CPItemComponents::create(listSize, new CPLayoutGrid(itemPerLine, itemSize, true));
	mRewards->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "singleRechargePanelList"));		

    int bkcnt = 0;
	StaticData::getSingleRechargeTableLength(bkcnt);

	for (int i = 0; i < bkcnt; i++)
	{		
		mRewards->addItem(getRewardItem(i));
	} 	
	mRewards->setCurrentIndex(mCurrentIndex);
	addChild(mRewards);

	//left board
	CCScale9Sprite *leftLineImg = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "singleRechargePanelLeftLineImg");
	addChild(leftLineImg);	

	CCLabelTTF *leftLineLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "singleRechargePanelLeftLineLabel");
	addChild(leftLineLabel);

	//right board
	CCScale9Sprite *rightLineImg = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "singleRechargePanelRightLineImg");
	addChild(rightLineImg);

	CCLabelTTF *rightLineLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "singleRechargePanelRightLineLabel");
	addChild(rightLineLabel);

	CCScale9Sprite *rightImg = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "singleRechargePanelRightImg");
	addChild(rightImg);

	CCLabelTTF *explain=LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"singleRechargePanelExplainLabel");
	addChild(explain);

	// refresh layer
	mRefreshLayer = CCLayer::create();
	addChild(mRefreshLayer);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	mGetBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "singleRechargePanelBtn");
	mGetBtn->setTarget(this, menu_selector(SingleRechargePanel::onGetReward));	
	menu->addChild(mGetBtn);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void SingleRechargePanel::refreshDesc()
{
	mRefreshLayer->removeAllChildren();

	std::string wordStr = "";	
	int wingID = mCurrentIndex + 1;		
		
	StaticData::getSingleRechargeLabelData(wingID, wordStr);
	CCLabelTTF *leftLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "singleRechargePanelLeftDescLabel");
	leftLabel->setString(wordStr.c_str());
	leftLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
	mRefreshLayer->addChild(leftLabel);

	std::string info = "";
	StaticData::getSingleRechargeLabelDesc(wingID,info);
	CCLabelTTF *rightLabel1 = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "singleRechargePanelRightDescLabel1");	
	rightLabel1->setString(info.c_str());
	rightLabel1->setHorizontalAlignment(kCCTextAlignmentLeft);
	mRefreshLayer->addChild(rightLabel1);

	std::string wingProperty = "";
	StaticData::getSingleRechargeLabelProperty(wingID, wingProperty);
	CCLabelTTF *rightLabel2 = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "singleRechargePanelRightDescLabel2");	
	rightLabel2->setString(wingProperty.c_str());
	rightLabel2->setHorizontalAlignment(kCCTextAlignmentLeft);
	mRefreshLayer->addChild(rightLabel2);

	//动画
	int articleID = 0;
	std::string itemAnim = "";
	StaticData::getSingleRechargeArticleID(wingID, articleID);
	StaticData::getItemAnim(articleID, itemAnim);

	itemAnim = "weapon/" + itemAnim + "_0";
	CCFlashAnimation *flashAnim = SystemData::getAnimation(itemAnim);
	CCSprite *animSprite = CCSprite::create();
	if(flashAnim)
	{
		animSprite->runAction(CCRepeatForever::create(flashAnim->getAnimate(0)));
	}	
	const CCPoint &animPoint = LayoutData::getPoint(CPModuleName::ACTIVITY, "singleRechargePanelAnimPoint");
	animSprite->setPosition(animPoint);
	
	mRefreshLayer->addChild(animSprite);
}

void SingleRechargePanel::refreshBtnState()
{
	const int giftID = ActivityData::getSingleRechargeReward(mCurrentIndex + 1);
	mGetBtn->setEnabled(giftID > 0);
}

void SingleRechargePanel::onItem( CCObject *target )
{
	CCNode *item = dynamic_cast<CCNode *>(target);
	if (item)
	{
		const int index = item->getTag();
		if (index != mCurrentIndex)
		{
			mCurrentIndex = index;			
			refreshDesc();
			refreshBtnState();
		}
	}
}

void SingleRechargePanel::onGetReward( CCObject *target )
{
	const int giftID = ActivityData::getSingleRechargeReward(mCurrentIndex + 1);
	if (giftID > 0)
	{
		FuncData::sendFuncMsgWithID(SINGLE_RECHARGE_FUNC_ID, giftID);
	}
	else
	{
		CPEventHelper::uiNotify("SingleRechargePanel", "", Error::InvalidGift);
	}
}

CCMenuItem * SingleRechargePanel::getRewardItem( int index )
{
	std::string wordStr = "";
	std::string wordSubStr = "";
	int articleID = 0;
	const int indexID = index + 1;
	
	StaticData::getSingleRechargeArticleID(indexID,articleID);
	StaticData::getItemName(articleID, wordStr);
	size_t iPos = wordStr.find("(");
	wordSubStr = wordStr.substr(0, iPos);
	
	CCMenuItem *imgBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "singleRechargePanelImgBtn");
	CCLabelTTF *imgLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "singleRechargePanelImgLabel");	
	imgLabel->setString(wordSubStr.c_str());	
	imgBtn->setTarget(this,menu_selector(SingleRechargePanel::onItem));
	imgBtn->addChild(imgLabel);
	
	CCSprite *articleImg = LayoutData::getItemIcon(articleID);	
	CCPoint centerPoint = LayoutData::getCenter(imgBtn->getContentSize());//获得item的中点
	articleImg->setPosition(centerPoint); 
	imgBtn->addChild(articleImg);
	
	return imgBtn;
}

void SingleRechargePanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "MsgFuncDataOperatorResponse")
		{
			mChecker->stop();
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageFuncDataNotify")
		{
			if (FuncData::getCurFuncID() == SINGLE_RECHARGE_FUNC_ID)
			{
				refreshBtnState();
			}
		}
	}

}
