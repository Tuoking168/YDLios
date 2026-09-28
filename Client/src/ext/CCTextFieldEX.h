#ifndef __TEXT_FIELD_EX__
#define __TEXT_FIELD_EX__

#include "cocos2d.h"
#include "CCTextFieldTTF.h"
using namespace cocos2d;


/** 
  * @brief 带光标的输入框
  */
class CCTextFieldEx : public cocos2d::CCTextFieldTTF
{
public:

	/**
	 * @brief 生成一个带光标的输入框 
	 * @param [in] fContentWidth 输入框的宽
	 * @param [in] fContentHeight 输入框的高
	 * @param [in] eAlignment 字体对齐方式，默认值：左对齐
	 * @param [in] pszFontName 字体名，默认值：Arial
	 * @param [in] fFontSize 字体大小，默认值：20.0f
	 * @param [in] fontColor 输入框的字体颜色，默认值：黑色
	 * @retval CCTextFieldEx* 带光标的输入框对象指针
	 * @retval NULL 生成失败
	 */
	static CCTextFieldEx* textFieldWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::CCTextAlignment eAlignment = kCCTextAlignmentLeft, const char* pszFontName = "Arial", float fFontSize = 20.0f, const cocos2d::ccColor3B& fontColor = cocos2d::ccBLACK);


	/** 
	 * @brief 初始化带光标的输入框 
	 * @param [in] fContentWidth 输入框的宽
	 * @param [in] fContentHeight 输入框的高
	 * @param [in] eAlignment 字体对齐方式
	 * @param [in] pszFontName 字体名
	 * @param [in] fFontSize 字体大小
	 * @param [in] fontColor 输入框的字体颜色
	 * @retval true 初始化成功
	 * @retval false 初始化失败
	 */
	bool initWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::CCTextAlignment eAlignment, const char* pszFontName, float fFontSize, const cocos2d::ccColor3B& fontColor);


	/** @brief 析构函数 */
	virtual ~CCTextFieldEx();


	/** @brief 更新光标 */
	virtual void updateCursor(float dt);


	/** @brief 添加输入框时的操作 */
	virtual void onEnter();


	/** @brief 移除输入框时的操作 */
	virtual void onExit();


	/**
     * @brief	 打开键盘、开始输入文本
     */
    virtual bool attachWithIME();


    /**
     * @brief	 结束输入文本、关闭键盘
     */
    virtual bool detachWithIME();


	/** 
	 * @brief 插入字符串
	 * @param [in] text 要插入的字符串
	 * @param [in] len 字符串长度
	 */
	virtual void insertText(const char * text, int len);


	/** 
	 * @brief 删除字符串
	 */
	virtual void deleteBackward();

	/**
	 * 返回密码框内容。
	 */
	virtual const char* getText(void);

	/**
	 * 设置文本框内容。。
	 */
	virtual void setText(const char *text);

	/**
	 * 设置是否为密码框，默认值为false
	 */
	virtual void setIsPassWord(bool isPsd);
	
	/**
	 * 设置是否为密码框，默认值为false
	 */
	virtual void setIsShowBoard(bool isShow);


protected:

	/** @brief 构造函数 */
	CCTextFieldEx();

	virtual void draw();

protected:

	std::string *m_pInputTextCopy;

	bool isPassWord;
	bool isShowBoard;

	/** 光标闪烁速度 */
	CC_SYNTHESIZE(float, m_fSpeed, Speed);

	/** 字数限制 */
	CC_SYNTHESIZE(int, m_nLimitFontCount, LimitFontCount);

	/** 输入完后受否隐藏字符串 */ 
	CC_SYNTHESIZE(bool, m_bIsHideTheTextAfterInput, IsHideTheTextAfterInput);

};

#endif //__TEXT_FIELD_EX__