#include "SelectRolePanel.h"
#include "userdata/SystemData.h"
#include "ext/GeneralMenu.h"
#include "scene/panel/functionPanel/CharacterPanel.h"
#include "scene/panel/functionPanel/AttributePanel.h"
#include "scene/panel/functionPanel/SoulStonePanel.h"

std::string btnstr[2]={
	"selectRolePanel_left_text1","selectRolePanel_left_text2"
};


SelectRolePanel::SelectRolePanel():
	m_bisSelf(false),
	m_iCurSelectType(0),
	m_pLeftNode(NULL),
	m_pRightNode(NULL),
	m_pCurSelectBtn(NULL),
	m_iLeftTag(-1),
	m_iRightTag(-1),
	m_bTouchInPos(true)
{
}

SelectRolePanel::~SelectRolePanel()
{
}

SelectRolePanel* SelectRolePanel::create()
{
	SelectRolePanel* Panel = new SelectRolePanel();
	if(Panel && Panel->init())
	{
		return Panel;
	}
	if (Panel)
	{
		delete Panel;
	}
	return NULL;
}

bool SelectRolePanel::init()//查看他人信息界面ui
{
	m_nHeight=SystemData::getLayoutValue("selectRolePanel_size.h");
	m_nWidth=SystemData::getLayoutValue("selectRolePanel_size.w");
	addCover(SystemData::getLayoutPoint("selectRolePanel_pos"));
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));


	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	addChild(pMenu);
	int btntag[2]={
		Role_Sub_Panel,Stone_Sub_Panel 
	};
	//加载左侧的按钮
	for (int i=0;i<2;i++)
	{
		CCMenuItemImage* pItem=SystemData::getMenuItemImageByPlist("selectRolePanel_left_btn");
		pItem->setScaleX(1.2f);
		pItem->runAction(CCRotateBy::create(0,-90));
		pItem->setPosition(SystemData::getLayoutPoint(btnstr[i]));
		pItem->setTag(btntag[i]);
		pItem->setTarget(this,menu_selector(SelectRolePanel::menucallback));
		pMenu->addChild(pItem);

		CCLabelTTF* pLabel=SystemData::getLabelTTF(btnstr[i]);
		pLabel->setColor(ccWHITE);
		pLabel->setFontSize(20);
		pLabel->setPosition(SystemData::getLayoutPoint(btnstr[i]));
		pLabel->setDimensions(CCSizeMake(22,0));
		pMenu->addChild(pLabel);

		if (i==0)
		{
			pItem->selected();
			m_pCurSelectBtn=pItem;
		}
	}

	m_pLeftNode=CCNode::create();
	m_pLeftNode->setAnchorPoint(CCPointZero);
	m_pLeftNode->setPosition(SystemData::getLayoutPoint("selectRolePanel_left_pos"));
	addChild(m_pLeftNode);

	m_pRightNode=CCNode::create();
	m_pRightNode->setAnchorPoint(CCPointZero);
	m_pRightNode->setPosition(SystemData::getLayoutPoint("selectRolePanel_right_pos"));
	addChild(m_pRightNode);

	initLeft(m_iCurSelectType);

	//关闭按钮
	GeneralMenu* pMenu1=GeneralMenu::create();
	pMenu1->setPosition(CCPointZero);
	pMenu1->setAnchorPoint(CCPointZero);
	addChild(pMenu1);

	CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("selectRolePanel_close");
	pClose->setPosition(SystemData::getLayoutPoint("selectRolePanel_close"));
	pClose->setTarget(this,menu_selector(SelectRolePanel::closeCallBack));
	pMenu1->addChild(pClose);

	return true;
}

bool SelectRolePanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	CCRect rect=CCRectMake(SystemData::getLayoutPoint("selectRolePanel_pos").x,SystemData::getLayoutPoint("selectRolePanel_pos").y,m_nWidth,m_nHeight);
	if (rect.containsPoint( this->convertToNodeSpace(pos)))
	{
		m_bTouchInPos=true;
	}
	else
	{
		m_bTouchInPos=false;
	}
	return true;
}

void SelectRolePanel::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void SelectRolePanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	CCRect rect=CCRectMake(SystemData::getLayoutPoint("selectRolePanel_pos").x,SystemData::getLayoutPoint("selectRolePanel_pos").y,m_nWidth,m_nHeight);
	if (!rect.containsPoint( this->convertToNodeSpace(pos)))
	{
		if (!m_bTouchInPos)
		{
			this->removeFromParent();
		}
	}
}

void SelectRolePanel::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void SelectRolePanel::initLeft(int tag)
{
	if (m_iLeftTag==tag)
	{
		return;
	}
	m_pLeftNode->removeAllChildren();
	int righttag=0;
	BasePanel* pPanel=NULL;
	switch (tag)
	{
	case Role_Sub_Panel:
		pPanel=CharacterPanel::create(false);
		pPanel->setAnchorPoint(CCPointZero);
		pPanel->setPosition(ccp(-8,-8));
		righttag=AttrLayer;
		break;
	case Stone_Sub_Panel:
		pPanel=SoulStonePanel::create(false);
		pPanel->setAnchorPoint(CCPointZero);
		pPanel->setPosition(ccp(-8,-8));
		righttag=AttrLayer;
		break;
	case Pet_Sub_Panel:
		break;
	default:
		break;
	}

	if(pPanel)
	{
		m_iLeftTag=tag;
		m_pLeftNode->addChild(pPanel);
		initRight(righttag);
	}
}

void SelectRolePanel::initRight(int tag)
{
	if (m_iRightTag==tag)
	{
		return;
	}
	m_pRightNode->removeAllChildren();
	BasePanel* pPanel=NULL;
	switch (tag)
	{
	case AttrLayer:
		pPanel=AttributePanel::create(false);
		pPanel->setAnchorPoint(CCPointZero);
		pPanel->setPosition(CCPointZero);
		break;
	case PetSkillLayer:
		break;
	default:
		break;
	}

	if(pPanel)
	{
		m_iRightTag=tag;
		m_pRightNode->addChild(pPanel);
	}
}

void SelectRolePanel::menucallback( CCObject* pSender )
{
	if (m_pCurSelectBtn)
	{
		m_pCurSelectBtn->unselected();
	}
	CCMenuItemImage* pItem=dynamic_cast<CCMenuItemImage*>(pSender);
	if (pItem)
	{
		int tag=pItem->getTag();
		initLeft(tag);
		pItem->selected();
		m_pCurSelectBtn=pItem;
	}
}

void SelectRolePanel::closeCallBack( CCObject* pSender )
{
	this->removeFromParent();
}
