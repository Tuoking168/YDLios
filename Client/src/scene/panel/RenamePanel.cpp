#include "RenamePanel.h"
#include "MainUIModule.h"

#include "scene/LoginHelper.h"

#include "event/CPEventHelper.h"

#include "userdata/LayoutData.h"
#include "Userdata/StaticData.h"
#include "MsgPlayer.h"
#include "network/HandleMessage.h"


namespace RenameType
{
	enum
	{
		player = 0,
		guild = 1,
	};
}

static int getNameMaxLen( int renameType )
{
	int ret = 0;
	if (renameType == RenameType::guild)
	{
		StaticData::getGlobalData("guildNameMaxLen", ret);
	}
	else
	{
		StaticData::getGlobalData("roleNameMaxLen", ret);
	}
	return ret;
}

/////////////RenamePanel/////////////////////////////////////////////
RenamePanel::RenamePanel()
	:mInputBox(NULL)
	,mRenameType(RenameType::player)
{

}

RenamePanel::~RenamePanel()
{

}

bool RenamePanel::init()
{
	if (!CPTipsSub::init())
	{
		return false;
	}

	mRenameType = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
	if (mRenameType != RenameType::player
		&& mRenameType != RenameType::guild)
	{
		CCLog(">>>Error: RenamePanel, unkown rename type: %d", mRenameType);
		return false;
	}
	
	initUI();

	return true;
}

void RenamePanel::initUI()
{
	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::COMMON, "floatBoard");
	addChild(board);
	setContentSize(board->getContentSize());

	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::MAIN_UI, "renamePanelTitle");
	addChild(titleLabel);

	// note
	CCLabelTTF *noteLable = LayoutData::getLabelTTF(CPModuleName::MAIN_UI, "renamePanelNote");
	addChild(noteLable);

	// input box
	mInputBox = LayoutData::getEditBox(CPModuleName::COMMON, "floatInput");
	mInputBox->setInputMode(kEditBoxInputModeSingleLine);
	mInputBox->setTouchPriority(kCCMenuHandlerPriority);
	mInputBox->setMaxLength(getNameMaxLen(mRenameType));
	addChild(mInputBox);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "floatClose");
	closeBtn->setTarget(this, menu_selector(RenamePanel::onClose));
	menu->addChild(closeBtn);

	CCMenuItemImage *confirmBtn = LayoutData::getMenuItemLabelImage(CPModuleName::COMMON, "floatConfirm");
	confirmBtn->setTarget(this, menu_selector(RenamePanel::onConfirm));
	menu->addChild(confirmBtn);

	CCMenuItemImage *cancelBtn = LayoutData::getMenuItemLabelImage(CPModuleName::COMMON, "floatCancel");
	cancelBtn->setTarget(this, menu_selector(RenamePanel::onCancel));
	menu->addChild(cancelBtn);
}

void RenamePanel::onConfirm( CCObject *target )
{
	std::string outStr;
	if (LoginHelper::testCreateName(mInputBox->getText(), outStr))
	{
		MsgReNameRequest* msg = new MsgReNameRequest;
		msg->type = mRenameType;
		msg->newname = outStr;
		HandleMessage::sendMessage(msg);
	}
	
	close();
}

void RenamePanel::onCancel( CCObject *target )
{
	close();
}

void RenamePanel::onClose( CCObject *target )
{
	close();
}
