#ifndef __NUMBER_KEYBOARD_H__
#define __NUMBER_KEYBOARD_H__

#include "ext/BasePanel.h"
#include "userdata/UserItemData.h"


typedef void (CCObject::*SEL_NumberPanel)(int);
#define numberpanel_selector(_SELECTOR) (SEL_NumberPanel)(&_SELECTOR)
class NumberBoard : public BasePanel
{
public:
	NumberBoard();
	~NumberBoard();
	void onEnter();
	void onExit();
	//init the board elements
	bool init(int* pValue, int MaxValue, int eventtype, int price);
	bool init(int defaultValue, int maxValue, int price);
	
public:
	static NumberBoard* create(int* pValue, int MaxValue, int eventtype, int price);
	static NumberBoard* create(int defaultValue, int maxValue, int price);

	void setCurLabelStr(std::string str);
	void setHandler(CCObject *target, SEL_NumberPanel func);

protected:
	//call back when you input a number
	void touchCallback(CCObject* pSender);
	//call back when you are sure about the result and want to close the keyboard
	void confirmCallback(CCObject* pSender);
	//close call back, when you want to cancel the input and close the keyboard
	void closeCallback(CCObject* pSender);
	//delete one number you had inputed
	void deleteCallback(CCObject* pSender);
	//set the max number you can buy
	void maxCallback(CCObject* pSender);
	//increase callback,increase the input number by one if its not bigger max numumber
	void increaseCallback(CCObject* pSender);
	//decrease callback,decrease the input number by one if big than zero
	void decreaseCallback(CCObject* pSender);
	//show the input
	void showInput();

	void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
protected:
	int* m_pValue;//the final value which must be a rational value
	int mValue;
	int m_nMaxValue;//the max value you can buy with all of you gold
	CCLabelTTF* m_pShowNum;//shown number on the input frame
	CCLabelTTF* m_pShowMoney;//money that will cost
	int m_nEventType;//the event type of the call back
	int m_nCurPrice;//the price of the selected item
	CCLabelTTF* m_pCurLabel;
	CCObject *mTarget;
	SEL_NumberPanel mHandleFunc;
};

class NumberKeyBoard : public BasePanel
{
public:
	NumberKeyBoard();
	~NumberKeyBoard();
	void onEnter();
	void onExit();

	bool init(int curValue,int MaxValue);
	bool init(int curValue,int MaxValue,int sid);
	static NumberKeyBoard* create(int curValue,int MaxValue);
	static NumberKeyBoard* create(int curValue,int MaxValue,int tag,int iid,int str);

	bool init(int defaultValue, int maxValue, int price ,int sid);
	static NumberKeyBoard* create(int defaultValue, int vType, int price ,int sid);

	void setCurLabelStr(std::string str);

	void setChangeHandler(CCObject *rec, SEL_MenuHandler selector);
	int getCurNum();
protected:
	//call back when you input a number
	void touchCallback(CCObject* pSender);
	//call back when you are sure about the result and want to close the keyboard
	void confirmCallback(CCObject* pSender);
	//close call back, when you want to cancel the input and close the keyboard
	void closeCallback(CCObject* pSender);
	//delete one number you had inputed
	void deleteCallback(CCObject* pSender);
	//set the max number you can buy
	void maxCallback(CCObject* pSender);
	//increase callback,increase the input number by one if its not bigger max numumber
	void increaseCallback(CCObject* pSender);
	//decrease callback,decrease the input number by one if big than zero
	void decreaseCallback(CCObject* pSender);
	//show the input
	void showInput();

	void handleChanged();

	void loadItemIcon(int sid);
	void showTooltip(CCMenuItem* pImage);
	void itemCallBack(CCObject* pSender);

	void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

protected:
	int m_pValue;//the final value which must be a rational value
	int m_nMaxValue;//the max value you can buy with all of you gold
	CCLabelTTF* m_pShowNum;//shown number on the input frame
	CCLabelTTF* m_pShowMoney;//money that will cost
	//int m_nEventType;//the event type of the call back
	//int m_nCurPrice;//the price of the selected item
	CCLabelTTF* m_pCurLabel;

	int m_nCurPrice;
	int m_nSid;
	int m_nType;

	CCObject *m_pListener;
	SEL_MenuHandler m_pfnSelector;
	int m_UserIid;
};


#endif//__NUMBER_KEYBOARD_H__