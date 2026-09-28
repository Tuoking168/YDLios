#ifndef __BoothData_H__
#define __BoothData_H__

#include "stdafx.h"
#include "cocos2d.h"
#include "MsgPet.h"

using namespace cocos2d;

struct sellData 
{ 
	int sid; 
	int price;
	int type;
};

class BoothData
{
public:
	static std::string getBoothAD();
	static void setBoothAD(std::string str);

	static void SetBoothPetIid(int petiid);
	static int getBoothPetIid();


	static bool getTradeLockState();
	static void setTradeLockState(bool flag);

	static bool getTradeOtherLockState();
	static void setTradeOtherLockState(bool flag);

	static bool getIsHigh();
	static void setIsHigh(bool flag);

	static int  addSellData(int sid,int price,int type);
	static void rmvSellData(int idx);
	static sellData getSellData(int idx);
	static void clearSellData();
	static std::map<int,sellData> getSellDataMap();
	static std::vector< MarketWords > getWords();
	static void setWords(std::vector< MarketWords > w);

private:
	static std::string m_sSlefBoothAD;
	static bool m_bTradeLock;
	static bool m_bTradeOtherLock;

	static bool m_bisHigh;

	static std::map<int,sellData> m_mSellData;
	static int m_iSellDataIndex;

	static std::vector< MarketWords > words;
};


#endif//__BoothData_H__