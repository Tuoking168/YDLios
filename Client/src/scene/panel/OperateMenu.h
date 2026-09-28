#ifndef __Operate_Menu_h__
#define __Operate_Menu_h__

#include "cocos2d.h"
USING_NS_CC;


class OperateMenu : public CCLayer
{
public:
	enum OperateType
	{
		Operate_Type_Team,
		Operate_Type_Player,
		Operate_Type_Guild,
	};
public:
	OperateMenu();
	~OperateMenu();
	void onEnter();
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	bool init(int type);
	static OperateMenu* create(int type);

public:
	void setPlayerID(int pid);
	void setPlayerName(const std::string &name);

private:
	void initMenu(std::string *keyList, int *tagList, int count);

	void callback(CCObject* pSender);
	void sendpostTrade(int pid);
	void sendpostCheck(int pid);

	bool checkCanTrade();

private:
	int m_nType;
	int mPlayerID;
	CCRect m_rect;
	std::string mPlayerName;
};


#endif//__Oerate_Menu_h__