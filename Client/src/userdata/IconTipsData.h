#ifndef __IconTipsData_H__
#define __IconTipsData_H__

#include "stdafx.h"
#include "cocos2d.h"

struct IconData
{
	int icontag;
	int icondata;
};

struct ForgetRewardData
{
	int endtime;
	std::string str;
};

struct MailData
{
	int idx;
	std::string title;
	std::string content;
	std::string gift;
};

enum IconTips
{
	T_addfriend,
	T_inviteguild,
	T_forgetreward,
	T_findmaster,
	T_findapprentice,
	T_itemendure,
	T_shortmedicinal,
	T_mining,
	T_perpareactivity,
	T_cansecondsactivity,
	T_trade,
	T_team,
	T_bagfull,
	T_perpareboss,
	T_itembroken,
	T_reborntips,
	T_hollowitem,
	T_rubbish,
	T_boothsell,
	T_mail,
	T_Max,
};
using namespace cocos2d;
class IconTipsData
{
public:
	static std::vector<int> icontips_list;	

	static std::map<int,ForgetRewardData> forgettips_map;	

	static std::map<int,MailData> mail_map;	

	static std::vector<IconData> icontips_icondata;	


	static void initorclear();

	static bool m_isInit;

	static bool getIconArray(int tag,int data);
	static void setIconArray(int tag,int data,bool flag);

	static int getIconCnt();
	static void setIconCnt(int cnt);

	static int getHollowIID();
	static void setHollowIID(int iid);

	static void addMailData(int idx,std::string str);
	static void removeMailData(int idx);
	static std::string getMailTitleStr(int idx);
	static std::string getMailContentStr(int idx);
	static std::string getMailGiftStr(int idx);

	static void addForgetGiftData(int idx,int data,std::string str);
	static void removeForgetGiftData(int idx);
	static std::string getForgetGiftStr(int idx);
	static void checkForgetGiftTime();

	static bool needShowSubWelfare(int index);
	static bool needShowWelfare();
	static void setShowSubWelfare(int index, bool needShow);
	typedef std::map<std::pair<int, int>, bool> IconArrayData;
	static IconArrayData m_theIconArrayData;

	static int m_iOverEventid;
	static int m_iDoingEventid;
	static int m_iWillEventid;
	static bool m_bClickActivity;
	
private:
	static int m_iIconCnt;
	static int m_iHollowIID;
	static int s_iShowWelfare;
};


#endif//__Emigrated_DATA_H__