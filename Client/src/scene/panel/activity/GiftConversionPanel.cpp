#include "GiftConversionPanel.h"
#include "ActivityModule.h"
#include "MsgActivity.h"

#include "scene/panel/functionPanel/ItemTooltip.h"

#include "controls/CPChecker.h"
#include "controls/CPRichText.h"

#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/SystemData.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "utils/RichTextUtils.h"

#include "network/HandleMessage.h"
#include "logic/platform/IPlatform.h"


GiftConversionPanel::GiftConversionPanel()
	:mChecker(NULL)
{

}

GiftConversionPanel::~GiftConversionPanel()
{

}

bool GiftConversionPanel::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}

	initUI();

	return true;
}

void GiftConversionPanel::initUI()
{
	// title
	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "giftConversionTitle");
	addChild(title);

	// board
	CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "giftConversionBoard");
	addChild(board);

	CCScale9Sprite *subBoard = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "giftConversionSubBoard");
	addChild(subBoard);

	CCScale9Sprite *topBoard = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "giftConversionTopBoard");
	addChild(topBoard);

	CCScale9Sprite *bottomBoard = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "giftConversionBottomBoard");
	addChild(bottomBoard);

	// img
	CCSprite *img = LayoutData::getSprite(CPModuleName::ACTIVITY, "giftConversionImg");
	addChild(img);

	// gift icon
	CCSprite *giftIcon = LayoutData::getSprite(CPModuleName::ACTIVITY, "giftConversionGiftIcon");
	addChild(giftIcon);

	// items
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	int itemCount = 0;
	StaticData::getActivationGiftItemCount(itemCount);
	const int perLine = LayoutData::getInt(CPModuleName::ACTIVITY, "giftConversionPerLine");
	const CCPoint &ptFirst = LayoutData::getPoint(CPModuleName::ACTIVITY, "giftConversionFirst");
	const CCSize &offset = LayoutData::getSize(CPModuleName::ACTIVITY, "giftConversionOffset");
	int sid = 0, count = 0;
	for (int i = 0; i < itemCount; i++)
	{
		sid = 0;
		count = 0;
		StaticData::getActivationGiftItemData(i + 1, sid, count);
		CCMenuItemImage *btn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "giftConversionGiftItem");
		btn->setTarget(this, menu_selector(GiftConversionPanel::onItem));
		btn->setPositionX(ptFirst.x + offset.width * (i % perLine));
		btn->setPositionY(ptFirst.y - offset.height * (i / perLine));
		menu->addChild(btn, 0, sid);

		CCSprite *icon = LayoutData::getItemIcon(sid, count);
		icon->setPositionX(btn->getContentSize().width/2);
		icon->setPositionY(btn->getContentSize().height/2);
		btn->addChild(icon);
	}

	// get button
	CCMenuItemImage *getBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "giftConversionGet");
	getBtn->setTarget(this, menu_selector(GiftConversionPanel::onGetGift));
	menu->addChild(getBtn);

	// recharge button
	CCMenuItemImage *rechargeBtn = SystemData::getMenuItemImageByPlist("shop.hqdhm");
	rechargeBtn->setTarget(this, menu_selector(GiftConversionPanel::onRecharge));
	const float gap = 20.0f;
	float rechargeX = getBtn->getPositionX()
		+ getBtn->getContentSize().width * 0.5f
		+ gap
		+ rechargeBtn->getContentSize().width * 0.5f;
	rechargeBtn->setPosition(ccp(rechargeX - 30.0f, getBtn->getPositionY() - 20.0f));
	rechargeBtn->setScale(0.75f);
	menu->addChild(rechargeBtn);

	// note label
	CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "giftConversionNote");
	addChild(noteLabel);

	// desc label
	CCLabelTTF *descLabel1 = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "giftConversionDesc1");
	addChild(descLabel1);

	CCLabelTTF *descLabel2 = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "giftConversionDesc2");
	addChild(descLabel2);

	const std::string &richStr = LayoutData::getString(CPModuleName::ACTIVITY, "giftConversionDesc");
	CPRichText *descLabel3 = RichTextUtils::getRichText(richStr, descLabel1->getFontSize());
	descLabel3->setPositionX(descLabel1->getPositionX());
	descLabel3->setPositionY(2 * descLabel1->getPositionY() - descLabel2->getPositionY());
	addChild(descLabel3);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void GiftConversionPanel::onItem( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int sid = node->getTag();
		if (sid > 0)
		{
			ItemTooltip *tips = ItemTooltip::create();
			tips->setTooltipContentbysid(sid);
			tips->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "giftConversionItemTips"));
			addChild(tips);
		}
	}
}

void GiftConversionPanel::onRecharge( CCObject *target )
{
	CPPlatform->pay(0);
}

void GiftConversionPanel::onGetGift( CCObject *target )
{
	GiftConversionInputPanel *inputPanel = GiftConversionInputPanel::create();
	inputPanel->setHandler(this, inputpanel_selector(GiftConversionPanel::onGetGiftByKey));
	CPTips *tips = CPTips::create(inputPanel);
	tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
	addChild(tips);
}

void GiftConversionPanel::onGetGiftByKey( const std::string &key )
{
	if (!key.empty())
	{
		mChecker->start();
		MsgGetGiftByCodeRequest *msg = new MsgGetGiftByCodeRequest;
		msg->code = key;
		HandleMessage::sendMessage(msg);
	}
}

void GiftConversionPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageGetGiftByCodeResponse")
		{
			mChecker->stop();
		}
	}
}

//////////GiftConversionInputPanel//////////////////////////////////////////////
GiftConversionInputPanel::GiftConversionInputPanel()
	:mInputBox(NULL)
	,mTarget(NULL)
	,mHandleFunc(NULL)
{

}

GiftConversionInputPanel::~GiftConversionInputPanel()
{

}

bool GiftConversionInputPanel::init()
{
	if (!CPTipsSub::init())
	{
		return false;
	}

	initUI();

	return true;
}

void GiftConversionInputPanel::setHandler( CCObject *target, SEL_InputPanel func )
{
	mTarget = target;
	mHandleFunc = func;
}

void GiftConversionInputPanel::initUI()
{
	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::COMMON, "floatBoard");
	addChild(board);
	setContentSize(board->getContentSize());

	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "giftConversionInputTitle");
	addChild(titleLabel);

	// note
	CCLabelTTF *noteLable = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "giftConversionInputNote");
	addChild(noteLable);

	// input box
	mInputBox = LayoutData::getEditBox(CPModuleName::COMMON, "floatInput");
	mInputBox->setInputMode(kEditBoxInputModeSingleLine);
	mInputBox->setTouchPriority(kCCMenuHandlerPriority);
	addChild(mInputBox);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "floatClose");
	closeBtn->setTarget(this, menu_selector(GiftConversionInputPanel::onClose));
	menu->addChild(closeBtn);

	CCMenuItemImage *confirmBtn = LayoutData::getMenuItemLabelImage(CPModuleName::COMMON, "floatConfirm");
	confirmBtn->setTarget(this, menu_selector(GiftConversionInputPanel::onConfirm));
	menu->addChild(confirmBtn);

	CCMenuItemImage *cancelBtn = LayoutData::getMenuItemLabelImage(CPModuleName::COMMON, "floatCancel");
	cancelBtn->setTarget(this, menu_selector(GiftConversionInputPanel::onCancel));
	menu->addChild(cancelBtn);
}

void GiftConversionInputPanel::onConfirm( CCObject *target )
{
	if (mTarget && mHandleFunc)
	{
		(mTarget->*mHandleFunc)(mInputBox->getText());
	}
	close();
}

void GiftConversionInputPanel::onCancel( CCObject *target )
{
	close();
}

void GiftConversionInputPanel::onClose( CCObject *target )
{
	close();
}
