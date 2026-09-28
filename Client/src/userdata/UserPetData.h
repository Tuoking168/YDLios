#ifndef __USER_Pet_DATA_H__
#define __USER_Pet_DATA_H__

#include <string>
#include <vector>
#include <map>
#include "PetDefinition.h"
#include "CombatDefinition.h"
#include "EntityDefinition.h"

// DataModel of User Items
struct UserPet
{
	int iid;
	int sid;
	int lvl;
	int exp;
	std::string name;
	int state;
	int  data[Combat::prop_Normal_End];	
	int  exdata[Entity::attr_pet_end];	
};
typedef std::map<int,UserPet*> UserPets;
typedef std::map<int,UserPet*> UserPetEgg;

class UserPetData
{
public:
	UserPetData();
	~UserPetData();
	void		addPet(UserPet* userpet);	
	UserPet*	getPetByIid(int iid);
	UserPet*    getFirstPet();
	int			getPetCount();
	UserPet*    getPetByNum(int num);
	int		    getPetNumByIid(int iid);
	void		rmvPetByiid(int iid);
	void		clear();

	UserPet*    getCurrentCombatPet();
	int		canBooth();

	UserPet*	initCurrentPet();
	//void		setCurrentPet(int num);
	UserPet*    getNextPet();
	UserPet*    getLastPet();
	UserPet*    getCurrentPet();
	int			getCurrentNum();

	void		addPetEgg(UserPet* userpet,int id);
	UserPet*    getPetEggInfo(int id);
	void		rmvPetEggByid(int id);

	int			getPetAdvanceCnt(UserPet* pPet);
	UserPet*    addNewPetEgg(int id);
public:
	UserPets	   userpets;
	UserPetEgg	   userpetegg;
	std::map<int, UserPet*>::iterator m_it;

	bool honortips;
	bool vcointips;
};

#endif