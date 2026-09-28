#include "ItemBindListPanel.h"
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


ItemBindListPanel::ItemBindListPanel()
	:mList(NULL)
	,mCurrentIndex(0)
{

}

ItemBindListPanel::~ItemBindListPanel()
{

}

bool ItemBindListPanel::init()
{
	if (!CPTipsSub::init())
	{
		return false;
	}

	UserItemData* data = GameData::s_user->getUserItemData();
	if (!data) return false;
	if (data->userItems.empty()) return false;

	return initUI();

	return true;
}

bool ItemBindListPanel::initUI()
{
	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::COMMON, "floatBoard");
	addChild(board);
	setContentSize(board->getContentSize());

	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "ItemBindListTitle");
	addChild(titleLabel);

	// desc
	CCLabelTTF *descLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "ItemBindListDesc");
	addChild(descLabel);

	//
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "ItemBindList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "ItemBindListItem");
	mList = CPItemComponents::create(listSize, new CPLayoutGrid(5,itemSize, true));
	mList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "ItemBindList"));
	addChild(mList);

	ItemOnList();
	if (mList->getItemCount() <= 0) return false;
	mList->setCurrentIndex(mCurrentIndex);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *ConfirmBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "ItemBindListConfirm");
	ConfirmBtn->setTarget(this, menu_selector(ItemBindListPanel::onconfirm)); 
	menu->addChild(ConfirmBtn);
	
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "floatClose");
	closeBtn->setTarget(this, menu_selector(ItemBindListPanel::onClose)); 
	menu->addChild(closeBtn);

	return true;
}

int ItemBindListPanel::pos2sid(int pos)
{
	int sid = 0;
	const UserItems& items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::const_iterator it = items.begin(); it!=items.end(); it++)
	{
		CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "juBaoPenBox");
		UserItem* pItem=(UserItem*)it->second;
		if (pos == pItem->position)
		{
			sid = pItem->sid;
			break;
		}
	}
	return sid;
}

void ItemBindListPanel::onList( CCObject *target )
{
	const int index = mList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
	}
	CCNode* item = mList->getItem(index);
	if (!item) return;
	int pos = (int)item->getUserData();
	int sid = pos2sid(pos);
//	UserItem* Itemdata = GameData::getUserItemData()->;
	ItemTooltip *tips = ItemTooltip::create();
	tips->setTooltipContentbysid(sid);
	tips->setPositionY(-60);
	addChild(tips);
}

void ItemBindListPanel::ItemOnList()
{
	const UserItems& items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::const_iterator it = items.begin(); it!=items.end(); it++)
	{
		CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "juBaoPenBox");
		UserItem* pItem=(UserItem*)it->second;
		int pos = pItem->position;
		if (pItem->position < 0 && pItem->data[ItemEquip::Item_Bind] == 0 && pItem->category==ItemCate_Equip && 
			pItem->type != ItemType_Equip_Wings && pItem->type != ItemType_Equip_Magic_Weapon && 
			pItem->type != ItemType_Equip_Foot && pItem->type != ItemType_Equip_Fashion)
		{
			CCSprite *icon = LayoutData::getItemIcon(pItem->sid);
			icon->setPosition(LayoutData::getCenter(item->getContentSize()));
			item->setTag(pos);
			item->setUserData((void*)pos);
			item->addChild(icon);
			item->setTarget(this, menu_selector(ItemBindListPanel::onList));
			mList->addItem(item);
		}
	}
}

void ItemBindListPanel::onconfirm( CCObject *target )
{
	const int index = mList->getCurrentIndex();
	if (index < 0) return;
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
	}
	CCNode* item = mList->getItem(index);
	if (!item) return;
	int pos = (int)item->getUserData();
	FuncData::sendFuncMsgWithID(21,SystemData::getLayoutValue("×°±¸°ó¶¨·û"),pos,1);
}

void ItemBindListPanel::onClose( CCObject *target )
{
	close();
}
