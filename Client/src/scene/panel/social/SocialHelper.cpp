#include "SocialHelper.h"
#include "ErrorDefinition.h"
#include "RelationshipDefinition.h"
#include "MsgRelationship.h"

#include "dialog/AddFriendConfirmDialog.h"
#include "dialog/AddMasterConfirmDialog.h"
#include "dialog/AddApprenticeConfirmDialog.h"

#include "userdata/HeroData.h"
#include "userdata/socialdata/SocialData.h"

#include "network/HandleMessage.h"
#include "network/MsgListener.h"

#include "event/CPEventHelper.h"


SocialHelper::SocialHelper()
{
}


SocialHelper::~SocialHelper()
{
}

int SocialHelper::requestRelationsData(int type)
{
	CCLog("___SocialHelper requestRelationsData...");
	MsgRelationListRequest *msg = new MsgRelationListRequest;
	msg->type = type;
	HandleMessage::sendMessage(msg);
	return 0;
}

int SocialHelper::addFriend(const int pid, const std::string &name)
{
	CCLog("___SocialHelper addFriend...");

	if(pid == 0 && name.length() == 0)
	{
		return Error::SOCIAL_NAME_EMPTY;
	}
	CCLog("___SocialHelper addFriend pid:%d", pid);
	CCLog("___SocialHelper addFriend name:%s", name.c_str());
	
	if (pid == HeroData::getPID())
	{
		CPEventHelper::uiNotify("SocialHelper::addFriend", "", Error::ThisIsYourself);
		return 0;
	}

	if (SocialData::isFriend(pid))
	{
		CPEventHelper::uiNotify("SocialHelper::addFriend", "", Error::SOCIAL_ALREADY_FRIEND);
		return 0;
	}
	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_FRIEND;
	msg->step = RelationshipDefinition::SOCIAL_OP_REQUEST;
	//msg->oid = Opcode::SOCIAL_OP_ADD_FRIEND;
	msg->pid = pid;
	msg->name = name;
	HandleMessage::sendMessage(msg);
	return 0;
}

int SocialHelper::requestAddFriend(const int pid, const std::string &name)
{
	CCLog("___SocialHelper requestAddFriend...");
	CCLog("___SocialHelper requestAddFriend pid:%d", pid);
	if (pid == HeroData::getPID())
	{
		CPEventHelper::uiNotify("SocialHelper::requestAddFriend", "", Error::ThisIsYourself);
		return 0;
	}

	if (SocialData::isFriend(pid))
	{
		CPEventHelper::uiNotify("SocialHelper::requestAddFriend", "", Error::SOCIAL_ALREADY_FRIEND);
		return 0;
	}
	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_FRIEND;
	msg->step = RelationshipDefinition::SOCIAL_OP_REQUEST;
	msg->pid = pid;
	msg->name = name;
	HandleMessage::sendMessage(msg);
	return 0;
}

int SocialHelper::agreeAddFriend()
{
	CCLog("___SocialHelper agreeAddFriend...");

	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_FRIEND;
	msg->step = RelationshipDefinition::SOCIAL_OP_RESPONSE + RelationshipDefinition::SOCIAL_OP_AGREE*10;
	msg->pid = SocialData::apprenticePid;
	msg->name = "";
	HandleMessage::sendMessage(msg);

	SocialData::rmvFriendData(SocialData::apprenticePid);

	SocialData::apprenticePid = -1;
	SocialData::apprenticeName = "";
	return 0;
}

int SocialHelper::refuseAddFriend()
{
	CCLog("___SocialHelper refuseAddFriend...");

	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_FRIEND;
	msg->step = RelationshipDefinition::SOCIAL_OP_RESPONSE + RelationshipDefinition::SOCIAL_OP_REFUSE*10;
	msg->pid = SocialData::apprenticePid;
	msg->name = "";
	HandleMessage::sendMessage(msg);
	SocialData::rmvFriendData(SocialData::apprenticePid);

	SocialData::apprenticePid = -1;
	SocialData::apprenticeName = "";
	return 0;

}
int SocialHelper::deleteRelation(const int pid, const int type)
{
	CCLog("___SocialHelper deleteRelation...");

	CCLog("___SocialHelper deleteRelation pid:%d", pid);
	
	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = type;
	msg->step = RelationshipDefinition::SOCIAL_OP_REQUEST + RelationshipDefinition::SOCIAL_OP_DELETE*10;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);

	SocialData::delPid = -1;
	SocialData::delName = "";
	SocialData::delType = -1;
	return 0;
}

int SocialHelper::requestAddMaster(const int pid)
{
	CCLog("___SocialHelper requestAddMaster...");
	CCLog("___SocialHelper requestAddMaster pid:%d", pid);
	if (pid == HeroData::getPID())
	{
		CPEventHelper::uiNotify("SocialHelper::requestAddMaster", "", Error::ThisIsYourself);
		return 0;
	}

	if (SocialData::isMaster(pid))
	{
		CPEventHelper::uiNotify("SocialHelper::requestAddMaster", "", Error::SOCIAL_ALREADY_MASTER);
		return 0;
	}
	if (SocialData::isApprentice(pid))
	{
		CPEventHelper::uiNotify("SocialHelper::requestAddApprentice", "", Error::SOCIAL_ALREADY_APPRENTICE);
		return 0;
	}
	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_MASTER;
	msg->step = RelationshipDefinition::SOCIAL_OP_REQUEST;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);
	return 0;
}

int SocialHelper::requestAddApprentice(const int pid)
{
	CCLog("___SocialHelper requestAddApprentice...");
	CCLog("___SocialHelper requestAddApprentice pid:%d", pid);
	if (pid == HeroData::getPID())
	{
		CPEventHelper::uiNotify("SocialHelper::requestAddApprentice", "", Error::ThisIsYourself);
		return 0;
	}

	if (SocialData::isApprentice(pid))
	{
		CPEventHelper::uiNotify("SocialHelper::requestAddApprentice", "", Error::SOCIAL_ALREADY_APPRENTICE);
		return 0;
	}
	if (SocialData::isMaster(pid))
	{
		CPEventHelper::uiNotify("SocialHelper::requestAddApprentice", "", Error::SOCIAL_ALREADY_MASTER);
		return 0;
	}
	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_APPRENTICE;
	msg->step = RelationshipDefinition::SOCIAL_OP_REQUEST;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);
	return 0;
}

int SocialHelper::agreeAddMaster()
{
	CCLog("___SocialHelper agreeAddMaster...");

	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_MASTER;
	msg->step = RelationshipDefinition::SOCIAL_OP_RESPONSE + RelationshipDefinition::SOCIAL_OP_AGREE*10;
	msg->pid = SocialData::apprenticePid;
	msg->name = "";
	HandleMessage::sendMessage(msg);

	SocialData::rmvMarsterData(SocialData::apprenticePid);
	SocialData::apprenticePid = -1;
	SocialData::apprenticeName = "";
	return 0;
}

int SocialHelper::refuseAddMaster()
{
	CCLog("___SocialHelper refuseAddMaster...");

	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_MASTER;
	msg->step = RelationshipDefinition::SOCIAL_OP_RESPONSE + RelationshipDefinition::SOCIAL_OP_REFUSE*10;
	msg->pid = SocialData::apprenticePid;
	msg->name = "";
	HandleMessage::sendMessage(msg);
	SocialData::rmvMarsterData(SocialData::apprenticePid);

	SocialData::apprenticePid = -1;
	SocialData::apprenticeName = "";
	return 0;
}

int SocialHelper::agreeAddApprentice()
{
	CCLog("___SocialHelper agreeAddApprentice...");

	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_APPRENTICE;
	msg->step = RelationshipDefinition::SOCIAL_OP_RESPONSE + RelationshipDefinition::SOCIAL_OP_AGREE*10;
	msg->pid = SocialData::masterPid;
	msg->name = "";
	HandleMessage::sendMessage(msg);
	SocialData::rmvApprenticeData(SocialData::masterPid);

	SocialData::masterPid = -1;
	SocialData::masterName = "";
	return 0;
}

int SocialHelper::refuseAddApprentice()
{
	CCLog("___SocialHelper refuseAddApprentice...");

	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_APPRENTICE;
	msg->step = RelationshipDefinition::SOCIAL_OP_RESPONSE + RelationshipDefinition::SOCIAL_OP_REFUSE*10;
	msg->pid = SocialData::masterPid;
	msg->name = "";
	HandleMessage::sendMessage(msg);
	SocialData::rmvApprenticeData(SocialData::masterPid);

	SocialData::masterPid = -1;
	SocialData::masterName = "";
	return 0;
}

int SocialHelper::requestAddCouple(const int pid, const std::string &name)
{
	CCLog("___SocialHelper requestAddCouple...");
	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_COUPLE;
	msg->step = RelationshipDefinition::SOCIAL_OP_REQUEST;
	msg->pid = pid;
	msg->name = name;
	HandleMessage::sendMessage(msg);
	return 0;
}

int SocialHelper::agreeAddCouple()
{
	CCLog("___SocialHelper agreeAddCouple...");

	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_COUPLE;
	msg->step = RelationshipDefinition::SOCIAL_OP_RESPONSE + RelationshipDefinition::SOCIAL_OP_AGREE*10;
	msg->pid = SocialData::bridegroomPid;
	msg->name = "";
	HandleMessage::sendMessage(msg);

	//SocialData::bridegroomPid = -1;
	//SocialData::bridegroomName = "";
	return 0;
}

int SocialHelper::refuseAddCouple()
{
	CCLog("___SocialHelper refuseAddCouple...");

	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_COUPLE;
	msg->step = RelationshipDefinition::SOCIAL_OP_RESPONSE + RelationshipDefinition::SOCIAL_OP_REFUSE*10;
	msg->pid = SocialData::bridegroomPid;
	msg->name = "";
	HandleMessage::sendMessage(msg);

	//SocialData::bridegroomPid = -1;
	//SocialData::bridegroomName = "";
	return 0;
}

int SocialHelper::addEnemy(const int pid)
{
	CCLog("___SocialHelper addEnemy...");

	if(pid == 0)
	{
		return Error::SOCIAL_NAME_EMPTY;
	}
	CCLog("___SocialHelper addEnemy pid:%d", pid);
	if (pid == HeroData::getPID())
	{
		CPEventHelper::uiNotify("SocialHelper::addEnemy", "", Error::ThisIsYourself);
		return 0;
	}

	if (SocialData::isEnemy(pid))
	{
		CPEventHelper::uiNotify("SocialHelper::addEnemy", "", Error::SOCIAL_ALREADY_ENEMY);
		return 0;
	}
	MsgRelationOperateRequest *msg = new MsgRelationOperateRequest;
	msg->type = RelationshipDefinition::SOCIAL_TYPE_ENEMY;
	msg->step = RelationshipDefinition::SOCIAL_OP_REQUEST;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);
	return 0;
}

int SocialHelper::findPlayer( int pid )
{
	MsgRelationFindingRequest* msg = new MsgRelationFindingRequest;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);
	return 0;
}

//-----------------------------------------------------------------------------------//
