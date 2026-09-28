#include "TopMergeServerPanel.h"
#include "ActivityModule.h"

#include "userdata/LayoutData.h"


TopMergeServerPanel::TopMergeServerPanel()
{

}

TopMergeServerPanel::~TopMergeServerPanel()
{

}

bool TopMergeServerPanel::init()
{
	if (!MenuListPanel::init())
	{
		return false;
	}

	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "");
	addChild(title);

	return true;
}

const std::string TopMergeServerPanel::dataTableName()
{
	return "";
}

void TopMergeServerPanel::onSwitch( int tag )
{
	CCNode *subPanel = NULL;
	switch (tag)
	{
	case panel_czdhk:
		break;
	case panel_czdbp:
		break;
	case panel_djdbp:
		break;
	case panel_zldbp:
		break;
	case panel_sczb:
		break;
	case panel_smsd:
		break;
	}

	if (subPanel)
	{
		addPanel(subPanel);
	}
}
