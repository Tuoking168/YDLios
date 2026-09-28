#include "DTextField.h"  
//#include "esun/eutils/ELog.h"  
//#include "cayman2/Format/Format.h"  
//#include "cayman2/AdviceBack/AdviceBack.h"  


static int _calcCharCount(const char * pszText)  
{  
	int n = 0;  
	char ch = 0;  
	while ((ch = *pszText))  
	{  
		CC_BREAK_IF(! ch);  

		if (0x80 != (0xC0 & ch))  
		{  
			++n;  
		}  
		++pszText;  
	}  
	return n;  
}  

bool DTextField::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)  
{  

	return true;  

}  
void DTextField::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)  
{  
	CCPoint  touch =pTouch->getLocationInView();  
	touch = CCDirector::sharedDirector()->convertToGL(touch);  
	CCRect rect=this->boundingBox();  
	//CCLog("Origin:(%f,%f) Size:(%f,%f)\n",rect.origin.x,rect.origin.y,rect.size.width,rect.size.height);  
	m_isTouchHandled=rect.containsPoint(touch);//CCRect::CCRectContainsPoint(rect, touch);  
	if(m_isTouchHandled)  
	{  
		this->attachWithIME();  
		//CCLog("Touched the TEXTFIELD");     
		if(m_isTouchedFun==true)  
			touchedEventExecut();  
	}  
	else  
	{  
		this->detachWithIME();  
	}  

}  

DTextField * DTextField::DTextFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)  
{         
	DTextField *pRet = new DTextField();  
	if(pRet && pRet->initWithPlaceHolder("", dimensions, alignment, fontName, fontSize))  
	{  
		pRet->autorelease();  
		if (placeholder)  
		{  
			pRet->setPlaceHolder(placeholder);  
		}  
		return pRet;  
	}  
	CC_SAFE_DELETE(pRet);  


	return NULL;  
}  
DTextField * DTextField::DTextFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize)  
{  
	DTextField *pRet = new DTextField();  
	if(pRet && pRet->initWithString("", fontName, fontSize))  
	{  
		pRet->autorelease();  
		if (placeholder)  
		{  
			pRet->setPlaceHolder(placeholder);  
		}  
		return pRet;  
	}  
	CC_SAFE_DELETE(pRet);  
	return NULL;  
}  
void DTextField::onEnter()  
{  
	CCSize size=CCDirector::sharedDirector()->getWinSize();  
	CCPoint myPos=this->getPosition();  
	CCSize mySize = this->getContentSize();  
	m_keyboardOffset=size.height/2+20;  
	if((myPos.y-mySize.height)<m_keyboardOffset)  
		m_isLowSide=true;  
	flags = 0;  
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-100,false);  
}  
void DTextField::onExit()  
{  
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
	this->detachWithIME();  
	m_isTouchedFun=false;  
}  

void DTextField::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)  
{  
	//CCLog("keyboardWillShow");  
	if(m_isLowSide&&this->m_isTouchHandled)  
		parentLayerUpMove();  
}  
void DTextField::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)  
{  
	//CCLog("keyboardWillHide");      
	if(m_isLowSide)  
		parentLayerBackMove();  
}  

void DTextField::parentLayerUpMove()  
{  
	CCNode*parent= this->getParent();  
	if(parent)  
	{  
		parent->stopAllActions();  
		CCSize size = CCDirector::sharedDirector()->getWinSize();  
		CCPoint myPos = this->getPosition();  
		CCMoveTo *move_up=CCMoveTo::create(0.35f,ccp(0,m_keyboardOffset-myPos.y/2));  
		parent->runAction(move_up);  

	}  
}  
void DTextField::parentLayerBackMove()  
{  
	CCNode*parent= this->getParent();  
	if(parent)  
	{  
		parent->stopAllActions();  
		CCSize size = CCDirector::sharedDirector()->getWinSize();  
		CCMoveTo *move_up=CCMoveTo::create(0.35f,ccp(0,0));  
		parent->runAction(move_up);  
	}  
}  
void DTextField::setString(const char *text)  
{  
	//string str=getString();  
	CC_SAFE_DELETE(m_pInputText);     

	if (text)  
	{  
		m_pInputText = new std::string(text);  
	}   
	else   
	{  
		m_pInputText = new std::string;  
	}  



	// if there is no input text, display placeholder instead  
	if (! m_pInputText->length())  
	{  
		CCLabelTTF::setString(m_pPlaceHolder->c_str());  
	}  
	else if(!m_isPassWord)  
	{  
		if(!m_isMove)  
			CCLabelTTF::setString(m_pInputText->c_str());  
		//else  
		//  FieldMove(m_pInputText);  
	}else  
	{     
		int len_now=m_pInputText->length();  
		string passWord(len_now,'*');  
		CCLabelTTF::setString(passWord.c_str());  
	}  
	m_nCharCount = _calcCharCount(m_pInputText->c_str());  
}  

void DTextField::setString( const char *label,CCTextAlignment Alignment )  
{  
	/*
	if (m_string)  
	{  
		delete m_string;  
		m_string = NULL;  
	}  
	*/
	//m_string = new std::string(label);  
	m_string = label;

	CCTexture2D *texture;  
	if( CCLabelTTF::m_tDimensions.equals(CCSizeZero)  )  
	{  
		texture = new CCTexture2D();  
		texture->initWithString(label, CCLabelTTF::m_pFontName->c_str(), CCLabelTTF::m_fFontSize);  
	}  
	else  
	{  
		texture = new CCTexture2D();  
		//texture->initWithString(label, CCLabelTTF::m_tDimensions, Alignment, CCLabelTTF::m_pFontName->c_str(), CCLabelTTF::m_fFontSize);  
		texture->initWithString(label,CCLabelTTF::m_pFontName->c_str(), CCLabelTTF::m_fFontSize,CCLabelTTF::m_tDimensions,Alignment,kCCVerticalTextAlignmentCenter);
	}  
	this->setTexture(texture);  
	texture->release();  

	CCRect rect = CCRectZero;  
	rect.size = CCLabelTTF::m_pobTexture->getContentSize();  
	this->setTextureRect(rect);  
}  
void DTextField::setTouchedEvent(CCObject* SelectorTarget,  
								 SEL_CallFunc selector,bool isTargeted)  
{  
	m_selectorTarget=SelectorTarget;  
	m_selector=selector;  
	m_isTouchedFun=isTargeted;  
}  

void DTextField::touchedEventExecut()  
{  
	if (m_selector&&m_isTouchedFun) {  
		(m_selectorTarget->*m_selector)();  
	}  
}  



void DTextField::deleteBackward()  
{         
	string front = getString();  
	CCTextFieldTTF::deleteBackward();  

	if (m_isMove &&(!m_isPassWord))  
	{  
		if(stringLen >=1)  
			stringLen--;  
		string str =getString();  
		CCTexture2D* delet = new CCTexture2D;  
		delet->initWithString(str.c_str(),"",20);  
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
		int n = front.length() - str.length();  
		if( n>=3)  
			flags-=n/3;  

		if(delet->getContentSize().width - flags*10 < FieldWidth)  
#else  
		if(delet->getContentSize().width < FieldWidth)  
#endif  
		{  
			this->setPosition(Front);  
			CCLabelTTF::setString(str.c_str());  
		}else{  

			this->setString(str.c_str(),kCCTextAlignmentRight);  
		}  
		CC_SAFE_DELETE(delet);  

		if(IsUpdate&& pSend){  
			//____droid________
			//AdviceBack* tmp =(AdviceBack*)pSend;  
			//tmp->upDateCount();  
		}  

	}  
}  
void DTextField::insertText( const char * text, int len )  
{  

	if (getStringLengthLimit()>=0)  
	{  
		string str=getString();  
		if(str.size()>=getStringLengthLimit())  
		{  
			return;  
		}  
	}  
	std::string sInsert(text, len);  

	// insert \n means input end  
	int nPos = sInsert.find('\n');  
	if ((int)sInsert.npos != nPos)  
	{  
		len = nPos;  
		sInsert.erase(nPos);  
	}  

	if (len > 0)  
	{  
		if (m_pDelegate && m_pDelegate->onTextFieldInsertText(this, sInsert.c_str(), len))  
		{  
			// delegate doesn't want insert text  
			return;  
		}  

		m_nCharCount += _calcCharCount(sInsert.c_str());  

		if(m_isMove)  
			FieldMove(sInsert);  
		else{  
			std::string sText(*m_pInputText);  
			sText.append(sInsert);  
			setString(sText.c_str());  
		}  
	}  
	if ((int)sInsert.npos == nPos) {  
		return;  
	}  

	// '\n' has inserted,  let delegate process first  
	if (m_pDelegate && m_pDelegate->onTextFieldInsertText(this, "\n", 1))  
	{  
		return;  
	}  


	// if delegate hasn't process, detach with ime as default  
	detachWithIME();  
}  


void DTextField::FieldMove( string insertText)  
{  
	int n = insertText.length();//StringFormat::CountUTF8(insertText);  

	if(( stringLen+n ) > len)  
		return ;  
	else{  
		m_pInputText->append(insertText);  
		stringLen = stringLen+n;  
	}  
	//if(IsUpdate&& pSend){  //更新计数器  
	//  AdviceBack* tmp =(AdviceBack*)pSend;  
	//  tmp->upDateCount();   
	//}  
	CCTexture2D* test = new CCTexture2D;  
	test->initWithString(m_pInputText->c_str(),"",20);  
	int lens = test->getContentSize().width ;  
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	if(insertText.length() >= 3)  
	{  
		flags+= insertText.length()/3;  
	}  
	if((lens-flags*12) > FieldWidth)  
#else  
	if(lens > FieldWidth)  
#endif  
	{  
		this->setPosition(Last);  
		this->setString(m_pInputText->c_str(),kCCTextAlignmentRight);  
	}  
	else  
		this->setString(m_pInputText->c_str(),kCCTextAlignmentLeft);  
	CC_SAFE_DELETE(test);  

} 