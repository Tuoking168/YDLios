#ifndef __TOP_ACTIVITY_H__
#define __TOP_ACTIVITY_H__

#include "cocos2d.h"
#include "ext/BasePanel.h"
#include "cocos-ext.h"

#include "event/IEventListener.h"
#include "PartPanel.h"

USING_NS_CC_EXT;
enum huodong
{
	h_kaifuhuodong=100,
	h_kaifujingji,
	h_touzijihua,
	h_zhanshenshice,
	h_zhanlijingji,
	h_caishenchuangguan,
	h_xunbao,
	h_libaofengshang,
	h_meirihuoyue,
	h_jubaopen,
	h_chengbatianxia,
	h_hanghuizhengduozhan,
	h_yongshijingjichang,
	h_qunxiongzhulu,
	h_paihangbang,
	h_dilaotanxian,
	h_fentianxinggong,
	h_gongchengzhan,
	h_huangjiashouwei,
	h_huodonghuikui,

	f_begin	=150,
	f_shouchonglibao	=150,
	f_meirishouchong,
	f_leijichongzhi,
	f_nyuelibao,
	f_xianshidalibao,
	f_zaixianjiangli,
	f_meirigongzi,
	f_meiridenglu,
	f_shangxianguanzhu,
	f_danbichongzhi,
	f_xiaofeichoujiang	,
	f_hefuhuikui ,
	f_xingyundazhuanpan ,


	b_xiaozhushou		=200,
	b_xitongshezhi,
	b_kuaisubaitan,
	b_suishenshangdian,
	b_lianxiwomen,
	b_lianxigm,
	b_youxiluntan,
};

class TopActiviyMenu;
const int MaxTopIcon=20;
class TopActiviy : public CCLayer, public IEventListener
{
public:
	TopActiviy();
	~TopActiviy();
	bool init();
	CREATE_FUNC(TopActiviy);
	void closeMenu();
	void closeMenuInstant();
	
private:
	void initUI();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	void onClick(CCObject* pSender);
	void openMenu(int tag);

	void onCPEvent(const std::string &eventName);

	void onCheckActivityEffect();
	void onCheckWelfareEffect();
	void onCheckIsQuickPlayEffect();

	//
public:
	static void doOpenActivityBox(int tag);
	static void doOpenWelfareBox(int tag);
private:
	TopActiviyMenu* m_pMenu; 
	CCMenuItemImage* combinedrank;
	CCMenuItemImage* m_pCurItem;
	CCMenuItemImage *m_AutoBtn;
	int m_iCurTag;

	CCSprite* m_pEffect;
	CCMenu *mMenu;
	bool	m_bUP, m_bRight;
	int	m_nOX;

	enum MyEnum
	{
		effect_enum,
	};
};

class TopActiviyMenu : public BasePanel
{
public:
	TopActiviyMenu();
	~TopActiviyMenu();
	bool init();
	CREATE_FUNC(TopActiviyMenu);

	void onEnter();
	void onExit();

	void setMenuType(int tag);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	//
	int  geticonCnt();
	void closeself();
private:
	CCScale9Sprite* m_pBkg;
	GeneralMenu* m_pMainMenu;
	int m_iCurType;

	void initUI();
	void onClick(CCObject* pSender);
	void openBooth();
	void removeIcon(int enumid,int size);
	bool  checkShowWelfareEffect(int tag);
	std::string topstr[MaxTopIcon];
	int toptag[MaxTopIcon];
	int m_iiconCnt;
	
};


class ContactUs : public PartPanel
{
public:
	ContactUs();
	~ContactUs();
	CREATE_FUNC(ContactUs);
	virtual bool init();

private:
	void initUI();
	void initUsDesc();
	void initUsDescII();
	void initButton();
	void close(CCObject* pSender);
};


#endif//__TOP_ACTIVITY_H__