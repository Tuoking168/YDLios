#include "JuBaoPenPanel.h"
#include "ActivityModule.h"
#include "EntityDefinition.h"

#include "scene/panel/functionPanel/ItemTooltip.h"

#include "controls/CPItemComponents.h"

#include "logic/ItemOperator.h"

#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/FuncData.h"
#include "userdata/HeroData.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "utils/StringUtils.h"


JuBaoPenPanel::JuBaoPenPanel()
	:mList(NULL)
	,mBuyBtn(NULL)
	,mNotVipNote(NULL)
	,mCurrentIndex(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

JuBaoPenPanel::~JuBaoPenPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool JuBaoPenPanel::init()
{
	if (!CPTipsSub::init())
	{
		return false;
	}


	initUI();
	refresh();

	return true;
}

void JuBaoPenPanel::initUI()//聚宝盆ui
{
	// 创建容器节点
	CCNode* container = CCNode::create();
	container->setPosition(ccp(200, 60)); // 根据需要调整容器的位置
	addChild(container);
	
	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::COMMON, "floatBoard");
	container->addChild(board);
	setContentSize(board->getContentSize());

	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "juBaoPenTitle");
	container->addChild(titleLabel);

	// desc
	CCLabelTTF *descLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "juBaoPenDesc");
	container->addChild(descLabel);

	CCLabelTTF *xiaoLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "juBaoPenXiao");
	container->addChild(xiaoLabel);

	CCLabelTTF *daLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "juBaoPenDa");
	container->addChild(daLabel);

	//
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "juBaoPenList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "juBaoPenListItem");
	mList = CPItemComponents::create(listSize, new CPLayoutList(itemSize, false));
	mList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "juBaoPenList"));
	container->addChild(mList);

	const int itemCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "juBaoPenItemCnt");
	for (int i = 0; i < itemCnt; i++)
	{
		CCMenuItem *item = getListItem(i);
		item->setTarget(this, menu_selector(JuBaoPenPanel::onList));
		mList->addItem(item);
	}
	mList->setCurrentIndex(mCurrentIndex);

	// not vip note
	mNotVipNote = CCNode::create();
	container->addChild(mNotVipNote);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	container->addChild(menu);

	mBuyBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "juBaoPenBuy");
	mBuyBtn->setTarget(this, menu_selector(JuBaoPenPanel::onBuy));
	menu->addChild(mBuyBtn);

	CCMenuItemImage *rechargeBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "juBaoPenRecharge");
	rechargeBtn->setTarget(this, menu_selector(JuBaoPenPanel::onRecharge));
	menu->addChild(rechargeBtn);
	
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "floatClose");
	closeBtn->setTarget(this, menu_selector(JuBaoPenPanel::onClose));
	menu->addChild(closeBtn);
}

void JuBaoPenPanel::refresh()
{
	const int vipLevel = HeroData::getProp(Entity::attr_vip_level);
	mBuyBtn->setEnabled(vipLevel > 0);

	mNotVipNote->removeAllChildren();
	if (vipLevel <= 0)
	{
		CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "juBaoPenNotVip");
		mNotVipNote->addChild(noteLabel);
	}
}

void JuBaoPenPanel::onList( CCObject *target )
{
	const int index = mList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
	}

	const int needviplvl[2] = {1, 3};
	const int vipLevel = HeroData::getProp(Entity::attr_vip_level);
	if (mCurrentIndex == 0 || mCurrentIndex == 1)
	{
		mBuyBtn->setEnabled((vipLevel >= needviplvl[mCurrentIndex]));
	}

	const std::string &key = "juBaoPenItem" + StringUtils::toString(mCurrentIndex);
	const int sid = LayoutData::getInt(CPModuleName::ACTIVITY, key);
	ItemTooltip *tips = ItemTooltip::create();
	tips->setTooltipContentbysid(sid);
	addChild(tips);
}

void JuBaoPenPanel::onBuy( CCObject *target )
{
	int cost = 0;
	const std::string &key = "juBaoPenCost" + StringUtils::toString(mCurrentIndex + 1);
	StaticData::getGlobalData(key, cost);
	if (ItemOperator::testGoldEnough(cost))
	{
		const int JU_BAO_PEN_FUNC_ID = 15;
		FuncData::sendFuncMsgWithID(JU_BAO_PEN_FUNC_ID, mCurrentIndex + 1);
	}
}

void JuBaoPenPanel::onRecharge( CCObject *target )
{
	CPEventHelper::openPanel("RechargePanel");
}

void JuBaoPenPanel::onClose( CCObject *target )
{
	close();
}

CCMenuItem * JuBaoPenPanel::getListItem( int index )
{
	const std::string &key = "juBaoPenItem" + StringUtils::toString(index);
	const int sid = LayoutData::getInt(CPModuleName::ACTIVITY, key);
	CCMenuItemImage *ret = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "juBaoPenBox");

	CCSprite *icon = LayoutData::getItemIcon(sid);
	icon->setPosition(LayoutData::getCenter(ret->getContentSize()));
	ret->addChild(icon);

	return ret;
}

void JuBaoPenPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			const int propType = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (propType == Entity::attr_vip_level)
			{
				refresh();
			}
		}
	}
}
