#include "CPText.h"
#include "cocos2d.h"

using namespace cocos2d;

CPText::CPText()
{

}

CPText::~CPText()
{

}

CPText * CPText::create( int width, int height,int defaultnum/*=0*/ )
{
	CPText *ret = new CPText;
	if (ret && ret->initWithData(width, height, defaultnum))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool CPText::initWithData( int width, int height,int defaultnum )
{
	if (CCNode::init())
	{
		m_iWidth=width;
		m_iHeight=height;
		m_DefaultNum = defaultnum;
		CCLayer* pLayer=CCLayer::create();
		pLayer->setPosition(CCPointZero);
		addChild(pLayer);

		CCMenu* pMenu=CCMenu::create();
		pMenu->setPosition(CCPointZero);
		addChild(pMenu);

		m_pMenuItem=CCMenuItemImage::create();
		/*CCScale9Sprite* pNormal = CCScale9Sprite::create(file.c_str());
		if(pNormal)
		{
			pNormal->setContentSize(CCSizeMake(m_iWidth,m_iHeight));
			m_pMenuItem->setNormalImage(pNormal);
		}
		CCScale9Sprite* pSelected = CCScale9Sprite::create(file_sel.c_str());
		if(pSelected)
		{
			pSelected->setContentSize(CCSizeMake(m_iWidth,m_iHeight));
			m_pMenuItem->setSelectedImage(pSelected);	
		}*/

		char str[32];
		sprintf(str,"%d",m_DefaultNum);
		m_pLabel=CCLabelTTF::create(std::string(str).c_str(),"",14);
		return true;
	}
	return false;
}


void CPText::setHandler( cocos2d::CCObject *target, cocos2d::SEL_MenuHandler func )
{
	mTarget = target;
	mHandleFunc = func;
}

void CPText::setDefaultNum( int num )
{
	m_DefaultNum=num;
	if (m_pLabel)
	{
		char str[32];
		sprintf(str,"%d",m_DefaultNum);
		m_pLabel->setString(std::string(str).c_str());
	}
}

int CPText::getDefaultNum()
{
	return m_DefaultNum;
}

void CPText::onClick( cocos2d::CCObject *target )
{
	if (mTarget && mHandleFunc)
	{
		(mTarget->*mHandleFunc)(this);
	}
}

void CPText::setLabelStyle( const std::string &fontName, float fontSize, const cocos2d::ccColor3B &color )
{
	if (m_pLabel)
	{
		m_pLabel->setFontName(fontName.c_str());
		m_pLabel->setFontSize(fontSize);
		m_pLabel->setColor(color);
	}
}
