#include "PanLongEquipPanel.h"
#include "ActivityModule.h"
#include "EntityDefinition.h"

#include "scene/panel/functionPanel/ItemTooltip.h"

#include "controls/CPItemComponents.h"

#include "logic/ItemOperator.h"

#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/FuncData.h"
#include "userdata/HeroData.h"
#include "userdata/UserData.h"
#include "userdata/UserItemData.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "MsgItem.h"
#include "network/HandleMessage.h"

#include "utils/StringUtils.h"


PanLongEquipPanel::PanLongEquipPanel()
	:mList(NULL)
	,mCurrentIndex(0)
{

}

PanLongEquipPanel::~PanLongEquipPanel()
{

}

bool PanLongEquipPanel::init()
{
	if (!CPTipsSub::init())
	{
		return false;
	}

	initUI();

	return true;
}

void PanLongEquipPanel::initUI()
{
	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::COMMON, "floatBoard");
	addChild(board);
	setContentSize(board->getContentSize());

	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "PanLongEquipTitle");
	addChild(titleLabel);

	// desc
	CCLabelTTF *descLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "PanLongEquipDesc");
	addChild(descLabel);

	//
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "PanLongEquipList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "PanLongEquipListItem");
	mList = CPItemComponents::create(listSize, new CPLayoutGrid(5,itemSize, true));
	mList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "PanLongEquipList"));
	addChild(mList);

	const int itemCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "PanLongItemCnt");
	for (int i = 0; i < itemCnt; i++)
	{
		CCMenuItem *item = getListItem(i);
		item->setTarget(this, menu_selector(PanLongEquipPanel::onList));
		mList->addItem(item);
	}
	mList->setCurrentIndex(mCurrentIndex);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *buyBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "PanLongEquipBuy");
	buyBtn->setTarget(this, menu_selector(PanLongEquipPanel::onBuy)); 
	menu->addChild(buyBtn);
	

	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "floatClose");
	closeBtn->setTarget(this, menu_selector(PanLongEquipPanel::onClose)); 
	menu->addChild(closeBtn);
}

void PanLongEquipPanel::onList( CCObject *target )
{
	const int index = mList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
	}

	std::string str = "";
	if(HeroData::getGender()==UserData::SEX_MALE)
	{
		str = "PanLongItemNan";
	}
	else
	{
		str = "PanLongItemNv";
	}

	const std::string &key = str + StringUtils::toString(mCurrentIndex);
	const int sid = LayoutData::getInt(CPModuleName::ACTIVITY, key);
	ItemTooltip *tips = ItemTooltip::create();
	tips->setTooltipContentbysid(sid);
	tips->setPositionY(-60);
	addChild(tips);
}

void PanLongEquipPanel::onBuy( CCObject *target )
{
	std::string str = "";
	if(HeroData::getGender()==UserData::SEX_MALE)
	{
		str = "PanLongItemNan";
	}
	else
	{
		str = "PanLongItemNv";
	}

	const std::string &key = str + StringUtils::toString(mCurrentIndex);
	const int sid = LayoutData::getInt(CPModuleName::ACTIVITY, key);

	FuncData::sendFuncMsgWithID(16,SystemData::getLayoutValue("ÅÍÁúÐíÔ¸ºÐ"),sid,1);
}

void PanLongEquipPanel::onClose( CCObject *target )
{
	close();
}

CCMenuItem * PanLongEquipPanel::getListItem( int index )
{
	std::string str = "";
	if(HeroData::getGender()==UserData::SEX_MALE)
	{
		str = "PanLongItemNan";
	}
	else
	{
		str = "PanLongItemNv";
	}
	const std::string &key = str + StringUtils::toString(index);
	const int sid = LayoutData::getInt(CPModuleName::ACTIVITY, key);
	CCMenuItemImage *ret = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "juBaoPenBox");

	CCSprite *icon = LayoutData::getItemIcon(sid);
	icon->setPosition(LayoutData::getCenter(ret->getContentSize()));
	ret->addChild(icon);

	return ret;
}
