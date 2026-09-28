#ifndef __CONFIRM_PROMPT__
#define __CONFIRM_PROMPT__

#include "ext/BasePanel.h"

//创建一个弹出的提示框
//提示的内容和按钮的内容作为参数传进来
//点击按钮产生的事件也作为参数传进来

class ConfirmPrompt : public BasePanel
{
public:
	//有两个选择按钮的确认提示框。
	static ConfirmPrompt* create(const std::string& strTips, const std::string& strLeftBtn, int nLeftEvent, const std::string& strRightBtn, int nRightEvent);
	//只有一个确认按钮的提示框。
	static ConfirmPrompt* create(const std::string& strTips, const std::string& strBtn, int nEvent);
public:
	bool init(const std::string& strTips, const std::string& strLeftBtn, int nLeftEvent, const std::string& strRightBtn, int nRightEvent);
	bool init(const std::string& strTips, const std::string& strBtn, int nEvent);
	//初始化背景图片和标题头图片
	bool initBackGroud();
	//按钮回调，发出事件
	void callback(CCObject* pSender);
	//关闭回调
	void closeCallBack(CCObject* pSender);
};


#endif//__CONFIRM_PROMPT__