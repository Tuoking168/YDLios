#include "BoothData.h"
#include "MsgPet.h"
#include "module/UserDataModule.h"
#include "userdata/HeroData.h"
#include "userdata/UserData.h"
#include "userdata/BoothData.h"
#include "network/HandleMessage.h"

std::string BoothData::m_sSlefBoothAD = "";


std::string BoothData::getBoothAD()
{
	return BoothData::m_sSlefBoothAD;
}

void BoothData::setBoothAD( std::string str )
{
	BoothData::m_sSlefBoothAD = str;
}

void BoothData::SetBoothPetIid( int petiid )
{
	MsgMarketSelectPetRequest* req=new MsgMarketSelectPetRequest;
	req->petid=petiid;
	HandleMessage::sendMessage(req);
	UserData::setIntData(HeroData::getPID(),CPUserData::LAST_BOOTHPET,petiid);
	UserData::saveData();
}

int BoothData::getBoothPetIid()
{
	int petiid = UserData::getIntData(HeroData::getPID(),CPUserData::LAST_BOOTHPET);
	return petiid;
}


bool BoothData::m_bTradeLock = false;

bool BoothData::getTradeLockState()
{
	return m_bTradeLock;
}

void BoothData::setTradeLockState( bool flag )
{
	BoothData::m_bTradeLock = flag;
}

bool BoothData::m_bTradeOtherLock = false;

bool BoothData::getTradeOtherLockState()
{
	return BoothData::m_bTradeOtherLock;
}

void BoothData::setTradeOtherLockState( bool flag )
{
	BoothData::m_bTradeOtherLock = flag;
}

bool BoothData::m_bisHigh = false;

bool BoothData::getIsHigh()
{
	return m_bisHigh;
}

void BoothData::setIsHigh( bool flag )
{
	m_bisHigh = flag;
}


int BoothData::m_iSellDataIndex = 0;

std::map<int,sellData> BoothData::m_mSellData;

int BoothData::addSellData( int sid,int price,int type )
{
	m_iSellDataIndex++;
	sellData sd;
	sd.sid = sid;
	sd.price = price;
	sd.type = type;
	m_mSellData[m_iSellDataIndex] = sd;
	return m_iSellDataIndex;
}

void BoothData::rmvSellData( int idx )
{
	std::map<int,sellData>::iterator it= m_mSellData.find(idx);
	if (it!=m_mSellData.end())
	{
		m_mSellData.erase(it);
	}
}

void BoothData::clearSellData()
{
	m_mSellData.clear();
}

sellData BoothData::getSellData( int idx )
{
	sellData sd;
	sd.price = 0;
	sd.type = 0;
	sd.sid = 0;
	std::map<int,sellData>::iterator it= m_mSellData.find(idx);
	if (it!=m_mSellData.end())
	{
		return it->second;
	}
	return sd;
}

std::map<int,sellData> BoothData::getSellDataMap()
{
	return m_mSellData;
}

std::vector<MarketWords> BoothData::words;

std::vector< MarketWords > BoothData::getWords()
{
	return words;
}

//¥Ê∑≈¡Ù—‘ ˝æ›
void BoothData::setWords( std::vector< MarketWords > w )
{
	words.clear();
	std::vector<MarketWords>::iterator it;
	for (it=w.begin();it!=w.end();it++)
	{
		MarketWords word;
		word.content = it->content;
		word.name = it->name;
		word.time = it->time;
		words.push_back(word);
	}	
}
