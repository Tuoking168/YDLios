#include "CPTouchTip.h"
#include "userData/SystemData.h"
#include "userData/LayoutData.h"

//#include "ext/TouchCover.h"
//#include "ext/CCActionDestroy.h"
#include "controls/CPNodeHelper.h"

/////////////////////////////////////////////////¡™œµŒ“√«/////////////////////////////////
CPTouchTip::CPTouchTip()
:m_content(NULL)
,m_bg(NULL)
,m_anim(NULL)
{
    
}

CPTouchTip::~CPTouchTip()
{
    
}
void CPTouchTip::onEnter()
{
    CCLayer::onEnter();
}
bool CPTouchTip::init()
{
	if (!PartPanel::init())
	{
		return false;
	}
	initUI();
	
	return true;
}

void CPTouchTip::initUI()
{
    
	setContentSize(CCSizeMake(m_nWidth,m_nHeight));
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    
    m_bg = CCScale9Sprite::create("data-a/ui/unplist/normal_tips.png");
    if (!m_bg)
        return;
    
    m_bg->setAnchorPoint(ccp(0.5, 0.5));
    m_bg->setPosition(ccp(winsize.width/2, winsize.height/2));
    addChild(m_bg);
    
    m_content = CCLabelTTF::create("", "Arial", 28);
    m_content->setColor(ccWHITE);
    m_content->setAnchorPoint(ccp(0.5,0.5));
    
    m_bg->addChild(m_content);
    
    m_anim = LayoutData::getSprite(CPModuleName::COMMON, "wait");
	m_anim->setAnchorPoint(ccp(0.5,0.5));
	m_bg->addChild(m_anim);
    
    CCDelayTime *dt = CCDelayTime::create(0.1f);
	CCRotateBy *rb = CCRotateBy::create(0.0f, 30);
    m_anim->runAction(CCRepeatForever::create(CCSequence::create(dt, rb, NULL)));
    
    
}
void CPTouchTip::setString(std::string note)
{
    const float wid = 50.0f;
    CCLabelTTF* tmp = CCLabelTTF::create(note.c_str(), "Arial", 28);
    CCSize strSize = tmp->getContentSize();
    m_bg->setContentSize(CCSizeMake(strSize.width+wid,strSize.height+wid));
    m_content->setPosition(ccp(m_bg->getContentSize().width*0.5,m_bg->getContentSize().height*0.5));
    m_content->setString(note.c_str());
    
    m_anim->setPosition(ccp(wid, m_bg->getContentSize().height*0.5));
}
void CPTouchTip::close()
{
    CCLog("close CPTouchTip");
	//this->removeFromParent();
}
