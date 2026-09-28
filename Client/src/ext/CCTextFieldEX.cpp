#include "CCTextFieldEx.h"

#define NO_FONT_COUNT_LIMIT -1

// 构造函数
CCTextFieldEx::CCTextFieldEx():
m_fSpeed(0.4f),
m_pInputTextCopy(new std::string),
m_nLimitFontCount(NO_FONT_COUNT_LIMIT)
{
	isPassWord = false;
	isShowBoard = false;
}


// 析构函数
CCTextFieldEx::~CCTextFieldEx()
{
	CC_SAFE_DELETE(m_pDelegate);
	CC_SAFE_DELETE(m_pInputTextCopy);
}


// 生成一个带光标的输入框
CCTextFieldEx* CCTextFieldEx::textFieldWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::CCTextAlignment eAlignment, const char* pszFontName, float fFontSize, const cocos2d::ccColor3B& fontColor)
{
	CCTextFieldEx* pTextField = new CCTextFieldEx;

	if (pTextField && pTextField->initWithWidthAndHeight(fContentWidth, fContentHeight, eAlignment, pszFontName, fFontSize, fontColor))
	{
		pTextField->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pTextField);
	}

	return pTextField;
}


// 初始化带光标的输入框
bool CCTextFieldEx::initWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::CCTextAlignment eAlignment, const char* pszFontName, float fFontSize, const cocos2d::ccColor3B& fontColor)
{
	do 
	{
		CCAssert(fContentWidth > 0.0f, "输入框的宽度必须大于零！");

		// 设置属性
		CCSize contentSize = CCSizeMake(fContentWidth, fContentHeight);
		CC_BREAK_IF(!CCTextFieldTTF::initWithString("", pszFontName, fFontSize, contentSize, eAlignment));
		this->setContentSize(contentSize);
		this->setColor(fontColor);

		return true;
	} while (0);
	
	return false;
}


// 更新光标
void CCTextFieldEx::updateCursor( float dt )
{
	static bool bIsCursorShowed = false;

	if (bIsCursorShowed)
	{
		std::string strText = this->getString();
		strText += "|";
		CCLabelTTF::setString(strText.c_str());
	}
	else
	{
		CCLabelTTF::setString(this->getString());
	}

	bIsCursorShowed = !bIsCursorShowed;
}


// 添加输入框时的操作
void CCTextFieldEx::onEnter()
{
	CCTextFieldTTF::onEnter();
}


// 移除输入框时的操作
void CCTextFieldEx::onExit()
{
	CCTextFieldTTF::onExit();
}


// 打开键盘、开始输入文本
bool CCTextFieldEx::attachWithIME()
{
	bool bResult = false;

	bResult = CCTextFieldTTF::attachWithIME();

	// 开始更新光标
	if (bResult)
	{
		std::string strText = this->getString();
		strText += "|";
		CCLabelTTF::setString(strText.c_str());
		this->schedule(schedule_selector(CCTextFieldEx::updateCursor), m_fSpeed);
	}

	this->setVisible(true);

	return bResult;
}


// 结束输入文本、关闭键盘
bool CCTextFieldEx::detachWithIME()
{
	bool bResult = false;

	bResult = CCTextFieldTTF::detachWithIME();

	// 停止更新光标
	if (bResult)
	{
		this->unschedule(schedule_selector(CCTextFieldEx::updateCursor));
	}

	// 如果支持离开时隐藏文字，那么...
	if (m_bIsHideTheTextAfterInput)
	{
		this->setVisible(false);
	}

	// 直接显示文本，以防光标停留
	CCLabelTTF::setString(this->getString());

	return bResult;
}

// 设置文本框内容。
void CCTextFieldEx::setText( const char *text )
{
	if (text)
	{
		if(isPassWord)
		{
			if (m_pInputTextCopy)
			{
				CC_SAFE_DELETE(m_pInputTextCopy);
			}
			m_pInputTextCopy = new std::string(text);
			if (m_pInputText)
			{
				delete m_pInputText;
				m_pInputText=NULL;
			}
			m_pInputText = new std::string(m_pInputTextCopy->length(),'*');
		}
		else
		{
			if (m_pInputText)
			{
				delete m_pInputText;
				m_pInputText=NULL;
			}
			m_pInputText = new std::string(text);
		}
		CCLabelTTF::setString(m_pInputText->c_str());
	}	
}

// 插入字符串
void CCTextFieldEx::insertText( const char * text, int len )
{
	if ((NO_FONT_COUNT_LIMIT == m_nLimitFontCount) || (m_pInputText->length() + len <= m_nLimitFontCount) )
	{
		CCTextFieldTTF::insertText(text, len);
	}
}


// 删除字符串
void CCTextFieldEx::deleteBackward()
{
	CCTextFieldTTF::deleteBackward();
}

// 返回密码框内容
const char* CCTextFieldEx::getText( void )
{
	if(isPassWord)
	{
		return m_pInputTextCopy->c_str();
	}
	else
	{
		return m_pInputText->c_str();
	}
}

// 设置文本框的密码状态
void CCTextFieldEx::setIsPassWord( bool isPsd )
{
	isPassWord = isPsd;
}

// 设置边框的显示。
void CCTextFieldEx::setIsShowBoard( bool isShow )
{
	isShowBoard = isShow;
}

// 实现密码框
void CCTextFieldEx::draw()
{
	if(isShowBoard)
	{
		// 绘制矩形区域
		CCTextFieldTTF::draw();

		CCPoint startPoint = CCPointZero;
		CCSize contentSize = this->getContentSize();
		CCPoint endPoint = CCPointMake(startPoint.x+contentSize.width, startPoint.y+contentSize.height);

		glLineWidth( 2.0f );
		//ccDrawColor4F(0.0f, 0.0f, 0.0f, 0.5f);
		ccDrawColor4F(1.0f, 1.0f, 1.0f, 0.5f);
		ccDrawLine( startPoint, CCPointMake(startPoint.x, endPoint.y) );
		ccDrawLine( startPoint, CCPointMake(endPoint.x, startPoint.y) );
		ccDrawLine( endPoint, CCPointMake(startPoint.x, endPoint.y));
		ccDrawLine( endPoint, CCPointMake(endPoint.x, startPoint.y));
		glLineWidth( 1.0f );
		ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
	}
	
	
	if (m_pDelegate && m_pDelegate->onDraw(this))
	{
		return;
	}
	if (m_pInputText->length())
	{
		if(isPassWord)
		{
			int length = m_pInputText->length();			
			if(m_pInputTextCopy->length() < length)
			{
				for(int i = length - m_pInputTextCopy->length(); i > 0; i--)
				{
					m_pInputTextCopy->push_back((*m_pInputText)[length - i]);
				}			
			}
			else
			{
				*m_pInputTextCopy = m_pInputTextCopy->substr(0,length);
			}
			if(m_pInputText)
			{
				delete m_pInputText;
			}
			m_pInputText = new std::string(length,'*');
		}		
		
		CCLabelTTF::draw();
		return;
	}
	else
	{
		m_pInputTextCopy->clear();
	}

	// draw placeholder
	ccColor3B color = getColor();
	setColor(m_ColorSpaceHolder);
	CCLabelTTF::draw();
	setColor(color);
}
