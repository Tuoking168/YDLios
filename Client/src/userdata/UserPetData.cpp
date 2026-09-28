#include "UserPetData.h"
#include "ErrorDefinition.h"
#include "EntityDefinition.h"
#include "CCPlatformMacros.h"
#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "MsgPet.h"
#include "module/UserDataModule.h"
#include "userdata/HeroData.h"
#include "userdata/UserData.h"
#include "userdata/BoothData.h"
#include "userdata/luadata/LuaData.h"
#include "script/LuaWrapper.h"


UserPetData::UserPetData():
	m_it(userpets.begin()),
	honortips(false),
	vcointips(false)
{
}


UserPetData::~UserPetData()
{
}

void UserPetData::addPet( UserPet* userpet )
{
	userpets[userpet->iid]=userpet;
}

UserPet* UserPetData::getPetByIid( int iid )
{
	std::map<int, UserPet*>::iterator it = userpets.find(iid);
	//m_it=it;
	if(it == userpets.end())
	{
		return NULL;
	}
	return it->second;
}

UserPet* UserPetData::getFirstPet()
{
	std::map<int, UserPet*>::iterator it = userpets.begin();
	//m_it=it;
	if(it == userpets.end())
	{
		return NULL;
	}
	return it->second;
}

UserPet* UserPetData::getNextPet()
{

	if (userpets.size()==0)
	{
		return NULL;
	}
	m_it++;
	if (m_it==userpets.end())
	{
		m_it--;
	}
	return m_it->second;
}

UserPet* UserPetData::getLastPet()
{
	if (userpets.size()==0)
	{
		return NULL;
	}
	if (m_it!=userpets.begin())
	{
		m_it--;
	}
	
	return m_it->second;
}

UserPet* UserPetData::getCurrentPet()
{
	/*if (userpets.size()==0)
	{
		return NULL;
	}
	UserPet* p = getCurrentCombatPet();
	if (p)
	{
		return p;
	}
	return getFirstPet();*/
	if (userpets.size()==0)
	{
		return NULL;
	}
	if (m_it==userpets.end())
	{
		m_it= userpets.begin();
	}
	return m_it->second;
}

UserPet* UserPetData::getCurrentCombatPet()
{
	std::map<int, UserPet*>::iterator it = userpets.begin();
	for (it;it!=userpets.end();it++)
	{
		UserPet* pPet = it->second;
		if (pPet->exdata[Entity::attr_pet_state] == Entity::pet_on)
		{
			//m_it=it;
			return pPet;
		}
	}
	return NULL;
}

int UserPetData::getPetCount()
{
	return userpets.size();
}

UserPet* UserPetData::getPetByNum( int num )
{
	if (num>userpets.size())
	{
		return NULL;
	}
	
	std::map<int, UserPet*>::iterator it = userpets.begin();
	for (it;it!=userpets.end();it++)
	{
		num--;
		if (num==0)
		{
			return it->second;
		}
	}
	return NULL;
}

int UserPetData::getPetNumByIid( int iid )
{
	int n=0;
	std::map<int, UserPet*>::iterator it = userpets.begin();
	for (it;it!=userpets.end();it++)
	{		
		if (iid==it->first)
		{
			return n;
		}
		n++;
	}
	return n;
}

void UserPetData::rmvPetByiid( int iid )
{
	std::map<int, UserPet*>::iterator it = userpets.begin();
	for (it;it!=userpets.end();it++)
	{		
		if (iid==it->first)
		{
			userpets.erase(it);
			break;
		}
	}
}

void UserPetData::clear()
{
	UserPets::iterator petIt = userpets.begin();
	while (petIt != userpets.end())
	{
		CC_SAFE_DELETE(petIt->second);
		petIt++;
	}
	userpets.clear();

	UserPetEgg::iterator eggIt = userpetegg.begin();
	while (eggIt != userpetegg.end())
	{
		CC_SAFE_DELETE(eggIt->second);
		eggIt++;
	}
	userpetegg.clear();
}

int UserPetData::canBooth()
{
	int rvt=Error::Unknown;

	int lastPetIid = BoothData::getBoothPetIid();
	std::map<int, UserPet*>::iterator lastit = userpets.find(lastPetIid);
	if ( lastit!= userpets.end())
	{
		if (lastit->second->state==Entity::pet_market)
		{
			rvt=Error::Success;
		}
		if (lastit->second->lvl>=10 && lastit->second->state==Entity::pet_sleep)
		{
			/*MsgMarketSelectPetRequest* req=new MsgMarketSelectPetRequest;
			req->petid=lastit->second->iid;
			HandleMessage::sendMessage(req);*/
			BoothData::SetBoothPetIid( lastit->second->iid );
			rvt=Error::Success;
		}
	}
	if (rvt==Error::Success)
	{
		return rvt;
	}

	if (userpets.size()==0)
	{
		rvt=Error::pe_not_pet;
	}
	std::map<int, UserPet*>::iterator it = userpets.begin();
	for (it;it!=userpets.end();it++)
	{		
		if (it->second->state==Entity::pet_market)
		{
			rvt=Error::Success;
			break;
		}
		if (it->second->lvl>=10 && it->second->state==Entity::pet_sleep)
		{
			/*MsgMarketSelectPetRequest* req=new MsgMarketSelectPetRequest;
			req->petid=it->second->iid;
			HandleMessage::sendMessage(req);*/
			BoothData::SetBoothPetIid( it->second->iid );
			rvt=Error::Success;
			break;
		}
		else if(it->second->lvl<10)
		{
			rvt=Error::pe_not_enoughlvl;
		}
		else if(it->second->lvl>=10 && it->second->state!=Entity::pet_sleep)
		{
			rvt=Error::pe_is_combat;
		}
	}
	return rvt;
}

void UserPetData::addPetEgg( UserPet* userpet ,int id)
{
	userpetegg[id]=userpet;
}

UserPet* UserPetData::getPetEggInfo( int id )
{
	std::map<int, UserPet*>::iterator it = userpetegg.find(id);
	if(it == userpetegg.end())
	{
		if (id<0)
		{
			return addNewPetEgg(id);
		}
		return NULL;
	}
	return it->second;
}

void UserPetData::rmvPetEggByid( int id )
{
	std::map<int, UserPet*>::iterator it = userpetegg.find(id);
	if(it != userpetegg.end())
	{
		UserPet* p  = it->second;
		userpetegg.erase(it);
		delete p;
	}
}

UserPet* UserPetData::initCurrentPet()
{
	std::map<int, UserPet*>::iterator it = userpets.begin();
	m_it=it;
	if(m_it == userpets.end())
	{
		return NULL;
	}
	return m_it->second;
}

int UserPetData::getCurrentNum()
{
	int num = 0;
	std::map<int, UserPet*>::iterator it = userpets.begin();
	for (it;it!=userpets.end();it++)
	{
		if (m_it->first == it->first)
		{
			return num;
		}
		num++;
	}
	return 0;
}

int UserPetData::getPetAdvanceCnt( UserPet* pPet )
{
	if (pPet)
	{
		int advancetype = pPet->exdata[Entity::attr_pet_ex_prop_type];
		int count= 0;
		int n=0;
		for (int b=0;b<3;b++)
		{
			int c=(int)((int)advancetype >> (8*b) & 255);
			if(c!=0)
			{
				count++;
			}
		}
		return count;
	}
	return 0;
}

UserPet* UserPetData::addNewPetEgg( int id )
{
	std::map<int, UserPet*>::iterator it = userpetegg.find(id);
	if(it != userpetegg.end())
	{
		return it->second;
	}

	int petsid = 0;
	Lua::instance()->push(id);		
	Lua::instance()->call("ItemCheckPetSid", 1, 1) ;
	Lua::instance()->pop(petsid);
	UserPet* newPet = new UserPet;
	newPet->iid = id;
	newPet->sid = petsid;
	LuaData::getProp(LuaData::PET,newPet->sid,"",newPet->name);
	newPet->lvl = 0;
	newPet->exp = 0;
	for (int i= Combat::prop_Start;i< Combat::prop_Normal_End;i++)
	{
		newPet->data[i]=0;
	}
	for (int i=Entity::attr_pet_start;i<Entity::attr_pet_end;i++)
	{
		newPet->exdata[i]=0;
	}

	int attrcnt = 0;
	LuaData::getProp_size("gdPetAddAttr",newPet->lvl,"attr",attrcnt);
	for (int i = 0;i<attrcnt;i++)
	{
		int type = 0;
		int data = 0;
		LuaData::getProp("gdPetAddAttr",newPet->lvl,"attr",i+1,"type",type);
		LuaData::getProp("gdPetAddAttr",newPet->lvl,"attr",i+1,"data",data);
		newPet->data[type] = data;
	}

	addPetEgg(newPet,id);
	return newPet;
}

