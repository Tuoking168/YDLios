
#include "CCMenuItemFontEx.h"
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
//CCMenuItemLabelEx
//
const ccColor3B& CCMenuItemLabelEx::getDisabledColor()
{
	return m_tDisabledColor;
}
void CCMenuItemLabelEx::setDisabledColor(const ccColor3B& var)
{
	m_tDisabledColor = var;
}
CCNode *CCMenuItemLabelEx::getLabel()
{
	return m_pLabel;
}
void CCMenuItemLabelEx::setLabel(CCNode* var)
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

CCMenuItemLabelEx * CCMenuItemLabelEx::itemWithLabel(CCNode*label, CCObject* target, SEL_MenuHandler selector)
{
	return CCMenuItemLabelEx::create(label, target, selector);
}

CCMenuItemLabelEx * CCMenuItemLabelEx::create(CCNode*label, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItemLabelEx *pRet = new CCMenuItemLabelEx();
	pRet->initWithLabel(label, target, selector);
	pRet->autorelease();
	return pRet;
}

CCMenuItemLabelEx* CCMenuItemLabelEx::itemWithLabel(CCNode *label)
{
	return CCMenuItemLabelEx::create(label);
}

CCMenuItemLabelEx* CCMenuItemLabelEx::create(CCNode *label)
{
	CCMenuItemLabelEx *pRet = new CCMenuItemLabelEx();
	pRet->initWithLabel(label, NULL, NULL);
	pRet->autorelease();
	return pRet;
}

bool CCMenuItemLabelEx::initWithLabel(CCNode* label, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItem::initWithTarget(target, selector);
//	m_fOriginalScale = 1.0f;
	m_tColorBackup = ccWHITE;
	m_tDisabledColor = ccc3(126,126,126);
	this->setLabel(label);
	return true;
}

CCMenuItemLabelEx::~CCMenuItemLabelEx()
{
}

void CCMenuItemLabelEx::setString(const char * label)
{
	dynamic_cast<CCLabelProtocol*>(m_pLabel)->setString(label);
	this->setContentSize(m_pLabel->getContentSize());
}

void CCMenuItemLabelEx::activate()
{
	if(isEnabled())
	{
		this->stopAllActions();
//		this->setScale( m_fOriginalScale );
		CCMenuItem::activate();
	}
}

void CCMenuItemLabelEx::selected()
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

void CCMenuItemLabelEx::unselected()
{
	// subclass to change the default action
	if(isEnabled())
	{
		CCMenuItem::unselected();
		dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(m_tColorBackup);
	}
}

void CCMenuItemLabelEx::setEnabled(bool enabled)
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

void CCMenuItemLabelEx::setOpacity(GLubyte opacity)
{
	dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setOpacity(opacity);
}

GLubyte CCMenuItemLabelEx::getOpacity()
{
	return dynamic_cast<CCRGBAProtocol*>(m_pLabel)->getOpacity();
}

void CCMenuItemLabelEx::setColor(const ccColor3B& color)
{
	dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(color);
}

const ccColor3B& CCMenuItemLabelEx::getColor()
{
	return dynamic_cast<CCRGBAProtocol*>(m_pLabel)->getColor();
}


//
//CCMenuItemFontEx
//
void CCMenuItemFontEx::setFontSize(unsigned int s)
{
	_fontSize = s;
}

unsigned int CCMenuItemFontEx::fontSize()
{
	return _fontSize;
}

void CCMenuItemFontEx::setFontName(const char *name)
{
	if( _fontNameRelease )
	{
		_fontName.clear();
	}
	_fontName = name;
	_fontNameRelease = true;
}

const char * CCMenuItemFontEx::fontName()
{
	return _fontName.c_str();
}

CCMenuItemFontEx * CCMenuItemFontEx::itemWithString(const char *value, CCObject* target, SEL_MenuHandler selector)
{
	return CCMenuItemFontEx::create(value, target, selector);
}

CCMenuItemFontEx * CCMenuItemFontEx::create(const char *value, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItemFontEx *pRet = new CCMenuItemFontEx();
	pRet->initWithString(value, target, selector);
	pRet->autorelease();
	return pRet;
}

CCMenuItemFontEx * CCMenuItemFontEx::itemWithString(const char *value)
{
	return CCMenuItemFontEx::create(value);
}

CCMenuItemFontEx * CCMenuItemFontEx::create(const char *value)
{
	CCMenuItemFontEx *pRet = new CCMenuItemFontEx();
	pRet->initWithString(value, NULL, NULL);
	pRet->autorelease();
	return pRet;
}

bool CCMenuItemFontEx::initWithString(const char *value, CCObject* target, SEL_MenuHandler selector)
{
	CCAssert( value != NULL && strlen(value) != 0, "Value length must be greater than 0");

	m_strFontName = _fontName;
	m_uFontSize = _fontSize;

	CCLabelTTF *label = CCLabelTTF::create(value, m_strFontName.c_str(), (float)m_uFontSize);
	if (CCMenuItemLabelEx::initWithLabel(label, target, selector))
	{
		// do something ?
	}
	return true;
}

void CCMenuItemFontEx::recreateLabel()
{
	CCLabelTTF *label = CCLabelTTF::create(dynamic_cast<CCLabelProtocol*>(m_pLabel)->getString(), 
		m_strFontName.c_str(), (float)m_uFontSize);
	this->setLabel(label);
}

void CCMenuItemFontEx::setFontSizeObj(unsigned int s)
{
	m_uFontSize = s;
	recreateLabel();
}

unsigned int CCMenuItemFontEx::fontSizeObj()
{
	return m_uFontSize;
}

void CCMenuItemFontEx::setFontNameObj(const char* name)
{
	m_strFontName = name;
	recreateLabel();
}

const char* CCMenuItemFontEx::fontNameObj()
{
	return m_strFontName.c_str();
}
NS_CC_END