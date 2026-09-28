#include "BoothsellNotify.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "NotificationModule.h"
#include "userdata/BoothData.h"
#include "userdata/StaticData.h"
#include "scene/panel/IconTipPanel.h"
#include "userdata/IconTipsData.h"

BoothsellNotify::BoothsellNotify():
	descLayer(NULL)
{

}

BoothsellNotify::~BoothsellNotify()
{

}

BoothsellNotify* BoothsellNotify::create( int idx )
{
	BoothsellNotify* characterPanel = new BoothsellNotify();
	if(characterPanel && characterPanel->init(idx))
	{
		characterPanel->autorelease();
		return characterPanel;
	}

	if (characterPanel)
	{
		delete characterPanel;
	}
	return NULL;
}

bool BoothsellNotify::init(int idx)
{
	if(!CCLayer::init())
	{
		return false;
	}
	initUI();
	initSellDesc(idx);
	return true;
}

void BoothsellNotify::initUI()
{
	CCScale9Sprite* bkg=SystemData::getScale9SpriteByPlist("sellnotify_tip",SystemData::getLayoutValue("sellnotify_tip.w"),SystemData::getLayoutValue("sellnotify_tip.h")); 
	bkg->setAnchorPoint(CCPointZero);
	bkg->setPosition(SystemData::getLayoutPoint("sellnotify_tip_pos"));
	addChild(bkg);

	descLayer = CCLayer::create();
	descLayer->setAnchorPoint(CCPointZero);
	descLayer->setPosition(bkg->getPosition());
	descLayer->setContentSize(CCSizeMake(SystemData::getLayoutValue("sellnotify_tip.w"),SystemData::getLayoutValue("sellnotify_tip.h")));
	addChild(descLayer);

	m_nHeight=bkg->getContentSize().width;
	m_nWidth=bkg->getContentSize().height;
	addCover();

	this->setContentSize(CCSizeMake(m_nWidth,m_nHeight));

	CCMenu* cp=CCMenu::create();
	cp->setAnchorPoint(CCPointZero);
	cp->setPosition(CCPointZero);
	descLayer->addChild(cp);

	CCScale9Sprite * normalsprite = LayoutData::getScale9Sprite(CPModuleName::COMMON,"norm");
	CCScale9Sprite * selectsprite = LayoutData::getScale9Sprite(CPModuleName::COMMON,"sel"); 

	CCMenuItemSprite* pBtn=CCMenuItemSprite::create(normalsprite,selectsprite);
	pBtn->setTarget(this,menu_selector(BoothsellNotify::close));
	pBtn->setPosition(ccp(bkg->getContentSize().width/2,25));
	cp->addChild(pBtn);

	CCLabelTTF* pLbl=SystemData::getLabelTTF("panel_QueDing_label");
	pLbl->setFontSize(14);
	pLbl->setColor(ccWHITE);
	pLbl->setPosition(pBtn->getPosition()); 
	descLayer->addChild(pLbl);
}

void BoothsellNotify::initSellDesc(int idx)
{
	sd = BoothData::getSellData(idx);
	if(sd.sid)
	{
		int sid = sd.sid;
		int price = sd.price;
		int type = sd.type;
		std::string name = "";
		CCString* pStr = NULL;
		StaticData::getItemName(sid,name);
		name = SystemData::getLayoutString("sellnotify_label1")+name;
		CCLabelTTF* label1 = CCLabelTTF::create(name.c_str(),"",15);
		label1->setAnchorPoint(ccp(0,1.0));
		label1->setDimensions(CCSizeMake(descLayer->getContentSize().width-10,0));
		label1->setPosition(ccp(3,90));

		descLayer->addChild(label1);
		pStr = CCString::create("");
		if (type == 2)
		{
			pStr=CCString::createWithFormat(SystemData::getLayoutString("sellnotify_label2").c_str(),price);
		}
		if (type == 3)
		{
			pStr=CCString::createWithFormat(SystemData::getLayoutString("sellnotify_label3").c_str(),price);
		}
		CCLabelTTF* label2 = CCLabelTTF::create(pStr->getCString(),"",15);
		label2->setAnchorPoint(ccp(0,1.0));
		label2->setDimensions(CCSizeMake(descLayer->getContentSize().width-10,0));
		label2->setPosition(ccp(3,70));
		descLayer->addChild(label2);
	}
}

void BoothsellNotify::close( CCObject* pSender )
{
//	BoothData::clearSellData();
	this->removeFromParent();
}




