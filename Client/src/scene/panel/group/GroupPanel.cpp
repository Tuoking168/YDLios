#include "GroupPanel.h"
#include "userdata/SystemData.h"

GroupPanel::GroupPanel()
	: m_pGroupTable(NULL)
{

}

GroupPanel::~GroupPanel()
{

}

bool GroupPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	

	return true;
}

void GroupPanel::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}

void GroupPanel::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}

void GroupPanel::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{

}

cocos2d::CCSize GroupPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	static CCSize size = SystemData::getLayoutSize("group.cell");
	return size;
}

cocos2d::extension::CCTableViewCell* GroupPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	return NULL;
}

unsigned int GroupPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 0;
}

void GroupPanel::callback( CCObject* pSender )
{

}

