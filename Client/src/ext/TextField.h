#ifndef __TEXT_FIELD__
#define __TEXT_FIELD__

#include "cocos2d.h"
#include "CCLayerEx.h"
#include "CCTextFieldEX.h"
using namespace cocos2d;


class TextField : public CCLayerEx
{	
public:
	// 构造函数，6个参数分别为：宽度，高度，对齐方式，字体名称，字体大小，字体颜色。
	TextField(float fContentWidth, float fContentHeight,
				cocos2d::CCTextAlignment eAlignment = kCCTextAlignmentLeft,
				const char* pszFontName = "Arial",
				float fFontSize = 20.0f,
				const cocos2d::ccColor3B& fontColor = cocos2d::ccBLACK);
	~TextField();

	static TextField* create(float fContentWidth, float fContentHeight,
		cocos2d::CCTextAlignment eAlignment = kCCTextAlignmentLeft,
		const char* pszFontName = "Arial",
		float fFontSize = 20.0f,
		const cocos2d::ccColor3B& fontColor = cocos2d::ccBLACK);

   virtual bool init();

   bool hasFocus()const;
	
   // 设为激活状态。
   void setFocus();

   // 关闭文本框的输入状态。
   void setLoseFocus();

   // 设置可最大容纳字符数。
   void setLimitFontCount(int limit);

   // 设置密码框模式。
   void setIsPassWord(bool isPsd);

   // 是否显示边框。
   void setIsShowBoard(bool isShow);

   // 返回文本框内容。
   const char* getText();

   // 设置文本框内容。
   void setText(const char *text);

   static bool hasFocusTextField();
protected:
	// 判断点击事件及位置。
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	
	CCTextFieldEx *textField;
	CCPoint  beginPoint;
	float width;
	float height;
	bool isPassWord;

	static TextField* _s_current_focus;
};

#endif