#include "TextField.h"


TextField* TextField::_s_current_focus = NULL;


//------------------------构造函数-------------------------
TextField::TextField(float fContentWidth, float fContentHeight, cocos2d::CCTextAlignment eAlignment, const char* pszFontName, float fFontSize, const cocos2d::ccColor3B& fontColor)
{
	textField = CCTextFieldEx::textFieldWithWidthAndHeight(fContentWidth,
															fContentHeight,
															eAlignment,
															pszFontName,
															fFontSize,
															fontColor);
	width = fContentWidth;
	height = fContentHeight;
}


TextField* TextField::create( float fContentWidth, float fContentHeight, cocos2d::CCTextAlignment eAlignment /*= kCCTextAlignmentLeft*/, const char* pszFontName /*= "Arial"*/, float fFontSize /*= 20.0f*/, const cocos2d::ccColor3B& fontColor /*= cocos2d::ccBLACK*/ )
{
	TextField* pTextField = new TextField(fContentWidth, fContentHeight, eAlignment, pszFontName, fFontSize, fontColor);
	if(pTextField && pTextField->init())
	{
		pTextField->autorelease();
		return pTextField;
	}
	CCLog("Failed to create TextField!!");
	return NULL;
}

TextField::~TextField()
{
	setLoseFocus();
}

//--------------------------------------------------------
bool TextField::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		
		addChild(textField);
		textField->setIsHideTheTextAfterInput(false);
		bRet = true;
	} while (0);

	CCSize size;
	size.width = width;
	size.height = height;
	setContentSize(size);

	setTouchEnabled(true);
	return bRet;
}

bool TextField::hasFocus()const
{
	return this==_s_current_focus;
}

bool TextField::hasFocusTextField()
{
	return (_s_current_focus!=NULL);
}

//-------------------设置文本框处于激活状态------------------
void TextField::setFocus()
{
	if (_s_current_focus!=this)
	{
		if (_s_current_focus)
		{
			_s_current_focus->setLoseFocus();
		}
	}
	_s_current_focus = this;
	textField->attachWithIME();
}
//------------------关闭文本框的输入状态---------------------
void TextField::setLoseFocus()
{
	if (_s_current_focus==this)
	{
		_s_current_focus = NULL;
		textField->detachWithIME();
	}
}
//-----------------设置文本框容纳最多字符数------------------
void TextField::setLimitFontCount( int limit )
{
	textField->setLimitFontCount(limit);
}
//------------------设置文本框的密码模式--------------------
void TextField::setIsPassWord( bool isPsd )
{
	textField->setIsPassWord(isPsd);
}
//-------------------设置边框的显示-------------------------
void TextField::setIsShowBoard( bool isShow )
{
	textField->setIsShowBoard(isShow);
}
//----------------以下用于确定是否是点击事件--------------
bool TextField::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (! isVisible())
	{
		return false;
	}
	for (CCNode *c = m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}
	if (pTouch)
	{
		beginPoint = getParent()->convertTouchToNodeSpace(pTouch);

		CCPoint pos = this->getPosition();
		if((pos.x - width/2) < beginPoint.x && beginPoint.x < (pos.x + width/2) &&
			(pos.y - height/2) < beginPoint.y && beginPoint.y < (pos.y + height/2))
		{ 
			setFocus();
			return true;
		}
	}
	setLoseFocus();
	return false;
}

//-----------------返回文本框内容------------------------
const char* TextField::getText()
{
	return textField->getText();
}
//----------------设置文本框内容-------------------------
void TextField::setText( const char *text )
{
	textField->setText(text);
}