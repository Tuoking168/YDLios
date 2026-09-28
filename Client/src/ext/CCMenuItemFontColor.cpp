
#include "CCMenuItemFontColor.h"
#include "actions/CCActionInterval.h"
#include "label_nodes/CCLabelTTF.h"
#include "script_support/CCScriptSupport.h"
#include <stdarg.h>
#include <cstring>
#include "cocos2d.h"

NS_CC_BEGIN

static unsigned int _fontSize = kCCItemSize;
static std::string _fontName = "Marker Felt";
static bool _fontNameRelease = false;

const unsigned int    kCurrentItem = 0xc0c05001;
const unsigned int    kZoomActionTag = 0xc0c05002;

const unsigned int    kNormalTag = 0x1;
const unsigned int    kSelectedTag = 0x2;
const unsigned int    kDisableTag = 0x3;

//
//CCMenuItemLabelColor
//
const ccColor3B& CCMenuItemLabelColor::getDisabledColor()
{
	return m_tDisabledColor;
}
void CCMenuItemLabelColor::setDisabledColor(const ccColor3B& var)
{
	m_tDisabledColor = var;
}
CCNode *CCMenuItemLabelColor::getLabel()
{
	return m_pLabel;
}
void CCMenuItemLabelColor::setLabel(CCNode* var)
{
	if (var)
	{
		addChild(var);
		var->setAnchorPoint(ccp(0, 0));
		setContentSize(var->getContentSize());
	}

	if (m_pLabel)
	{
		removeChild(m_pLabel, true);
	}

	m_pLabel = var;
}

CCMenuItemLabelColor * CCMenuItemLabelColor::itemWithLabel(CCNode*label, CCObject* target, SEL_MenuHandler selector)
{
	return CCMenuItemLabelColor::create(label, target, selector);
}

CCMenuItemLabelColor * CCMenuItemLabelColor::create(CCNode*label, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItemLabelColor *pRet = new CCMenuItemLabelColor();
	pRet->initWithLabel(label, target, selector);
	pRet->autorelease();
	return pRet;
}

CCMenuItemLabelColor* CCMenuItemLabelColor::itemWithLabel(CCNode *label)
{
	return CCMenuItemLabelColor::create(label);
}

CCMenuItemLabelColor* CCMenuItemLabelColor::create(CCNode *label)
{
	CCMenuItemLabelColor *pRet = new CCMenuItemLabelColor();
	pRet->initWithLabel(label, NULL, NULL);
	pRet->autorelease();
	return pRet;
}

bool CCMenuItemLabelColor::initWithLabel(CCNode* label, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItem::initWithTarget(target, selector);
//	m_fOriginalScale = 1.0f;
	m_tColorBackup = ccWHITE;
	m_tDisabledColor = ccc3(126,126,126);
	this->setLabel(label);
	return true;
}

CCMenuItemLabelColor::~CCMenuItemLabelColor()
{
}

void CCMenuItemLabelColor::setString(const char * label)
{
	dynamic_cast<CCLabelProtocol*>(m_pLabel)->setString(label);
	this->setContentSize(m_pLabel->getContentSize());
}

void CCMenuItemLabelColor::activate()
{
	if(isEnabled())
	{
		this->stopAllActions();
//		this->setScale( m_fOriginalScale );
		CCMenuItem::activate();
	}
}

void CCMenuItemLabelColor::selected()
{
	// subclass to change the default action
	if(isEnabled())
	{
		CCMenuItem::selected();

		CCAction *action = getActionByTag(kZoomActionTag);
		if (action)
		{
			this->stopAction(action);
		}
		m_tColorBackup = dynamic_cast<CCRGBAProtocol*>(m_pLabel)->getColor();
		dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(m_tDisabledColor);
	}
}

void CCMenuItemLabelColor::unselected()
{
	// subclass to change the default action
	if(isEnabled())
	{
		CCMenuItem::unselected();
		dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(m_tColorBackup);
	}
}

void CCMenuItemLabelColor::setEnabled(bool enabled)
{
	if( isEnabled() != enabled ) 
	{
		if(enabled == false)
		{
			m_tColorBackup = dynamic_cast<CCRGBAProtocol*>(m_pLabel)->getColor();
			dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(m_tDisabledColor);
		}
		else
		{
			dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(m_tColorBackup);
		}
	}
	CCMenuItem::setEnabled(enabled);
}

void CCMenuItemLabelColor::setOpacity(GLubyte opacity)
{
	dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setOpacity(opacity);
}

GLubyte CCMenuItemLabelColor::getOpacity()
{
	return dynamic_cast<CCRGBAProtocol*>(m_pLabel)->getOpacity();
}

void CCMenuItemLabelColor::setColor(const ccColor3B& color)
{
	dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(color);
}

const ccColor3B& CCMenuItemLabelColor::getColor()
{
	return dynamic_cast<CCRGBAProtocol*>(m_pLabel)->getColor();
}


//
//CCMenuItemFontColor
//
void CCMenuItemFontColor::setFontSize(unsigned int s)
{
	_fontSize = s;
}

unsigned int CCMenuItemFontColor::fontSize()
{
	return _fontSize;
}

void CCMenuItemFontColor::setFontName(const char *name)
{
	if( _fontNameRelease )
	{
		_fontName.clear();
	}
	_fontName = name;
	_fontNameRelease = true;
}

const char * CCMenuItemFontColor::fontName()
{
	return _fontName.c_str();
}

CCMenuItemFontColor * CCMenuItemFontColor::itemWithString(const char *value, CCObject* target, SEL_MenuHandler selector)
{
	return CCMenuItemFontColor::create(value, target, selector);
}

CCMenuItemFontColor * CCMenuItemFontColor::create(const char *value, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItemFontColor *pRet = new CCMenuItemFontColor();
	pRet->initWithString(value, target, selector);
	pRet->autorelease();
	return pRet;
}

CCMenuItemFontColor * CCMenuItemFontColor::itemWithString(const char *value)
{
	return CCMenuItemFontColor::create(value);
}

CCMenuItemFontColor * CCMenuItemFontColor::create(const char *value)
{
	CCMenuItemFontColor *pRet = new CCMenuItemFontColor();
	pRet->initWithString(value, NULL, NULL);
	pRet->autorelease();
	return pRet;
}

bool CCMenuItemFontColor::initWithString(const char *value, CCObject* target, SEL_MenuHandler selector)
{
	CCAssert( value != NULL && strlen(value) != 0, "Value length must be greater than 0");

	m_strFontName = _fontName;
	m_uFontSize = _fontSize;

	CCLabelTTF *label = CCLabelTTF::create(value, m_strFontName.c_str(), (float)m_uFontSize);
	if (CCMenuItemLabelColor::initWithLabel(label, target, selector))
	{
		// do something ?
	}
	return true;
}

void CCMenuItemFontColor::recreateLabel()
{
	CCLabelTTF *label = CCLabelTTF::create(dynamic_cast<CCLabelProtocol*>(m_pLabel)->getString(), 
		m_strFontName.c_str(), (float)m_uFontSize);
	this->setLabel(label);
}

void CCMenuItemFontColor::setFontSizeObj(unsigned int s)
{
	m_uFontSize = s;
	recreateLabel();
}

unsigned int CCMenuItemFontColor::fontSizeObj()
{
	return m_uFontSize;
}

void CCMenuItemFontColor::setFontNameObj(const char* name)
{
	m_strFontName = name;
	recreateLabel();
}

const char* CCMenuItemFontColor::fontNameObj()
{
	return m_strFontName.c_str();
}
NS_CC_END