#ifndef __DONATE_KEYBOARD_H__
#define __DONATE_KEYBOARD_H__

#include "ext/BasePanel.h"

class DonateKeyBoard : public BasePanel
{
public:
	DonateKeyBoard();
	~DonateKeyBoard();
	void onEnter();
	void onExit();
	//init the board elements
	bool init(int curValue,int MaxValue);
	//create an instance of the keyboard and 
	static DonateKeyBoard* create(int curValue,int MaxValue);

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

	CCObject *m_pListener;
	SEL_MenuHandler m_pfnSelector;
};

#endif//__DONATE_KEYBOARD_H__