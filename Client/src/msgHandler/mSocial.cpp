#include "MsgMaster.h"
#include "RelationshipDefinition.h"
#include "event/EventDispatcher.h"
#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"

#include "userdata/socialdata/SocialData.h"
#include "scene/panel/social/SocialHelper.h"

void MsgMaster::HandleMessageRelationListResponse( IMsg *pMsg )
{
	CCLog("MessageRelationListResponse ------------------");
	MsgRelationListResponse *msg = dynamic_cast<MsgRelationListResponse *>(pMsg);
	if (!msg) return;

	// ???????????????
	if(msg->errcode == Error::Success)
	{
		std::string notifyName = "";
		switch ((int)msg->type)
		{
			case RelationshipDefinition::SOCIAL_TYPE_FRIEND:
				{
					SocialData::mFriends.clear();
					notifyName = "HandleMessageRelationListResponse";
				}
				break;
			case RelationshipDefinition::SOCIAL_TYPE_MASTER:
				{
					SocialData::mMasters.clear();
					notifyName = "HandleMessageMasterListResponse";
				}
				break;
			case RelationshipDefinition::SOCIAL_TYPE_APPRENTICE:
				{
					SocialData::mApprentices.clear();
					notifyName = "HandleMessageApprenticeListResponse";
				}
				break;
			case RelationshipDefinition::SOCIAL_TYPE_COUPLE:
				{
					SocialData::mCouples.clear();
					notifyName = "HandleMessageRelationListResponse";
				}
				break;
			case RelationshipDefinition::SOCIAL_TYPE_ENEMY:
				{
					SocialData::mEnemies.clear();
					notifyName = "HandleMessageRelationListResponse";
				}
				break;
			case RelationshipDefinition::SOCIAL_TYPE_MASTER_LIST:
				{
					SocialData::mMasterList.clear();
					notifyName = "HandleMessageRelationListResponse";
				}
				break;
			case RelationshipDefinition::SOCIAL_TYPE_APPRENTICE_LIST:
				{
					SocialData::mApprenticeList.clear();
					notifyName = "HandleMessageRelationListResponse";
				}
				break;
			default:
				break;
		}
		for (MsgRelationListResponse::RelationInfoList::iterator it = msg->relations.begin();it!=msg->relations.end();it++)
		{
			RelationInfo& info = *it;
			SocialData::RelationData data;
			data.pid = info.pid;
			data.name = info.name;
			data.gender = info.gender;
			data.clazz = info.clazz;
			data.level = info.level;
			
			switch ((int)msg->type)
			{
				case RelationshipDefinition::SOCIAL_TYPE_FRIEND:
					SocialData::mFriends.push_back(data);
					break;
				case RelationshipDefinition::SOCIAL_TYPE_MASTER:
					SocialData::mMasters.push_back(data);
					break;
				case RelationshipDefinition::SOCIAL_TYPE_APPRENTICE:
					SocialData::mApprentices.push_back(data);
					break;
				case RelationshipDefinition::SOCIAL_TYPE_COUPLE:
					SocialData::mCouples.push_back(data);
					break;
				case RelationshipDefinition::SOCIAL_TYPE_ENEMY:
					SocialData::mEnemies.push_back(data);
					break;
				case RelationshipDefinition::SOCIAL_TYPE_MASTER_LIST:
					SocialData::mMasterList.push_back(data);
					break;
				case RelationshipDefinition::SOCIAL_TYPE_APPRENTICE_LIST:
					SocialData::mApprenticeList.push_back(data);
					break;
				default:
					break;
			}
		}
		CPEventHelper::uiNotify(notifyName, "", msg->errcode);
	}
}

void MsgMaster::HandleMessageRelationOperateResponse( IMsg *pMsg )
{
	CCLog("HandleMessageRelationOperateResponse ------------------");
	MsgRelationOperateResponse *msg = dynamic_cast<MsgRelationOperateResponse *>(pMsg);
	if (!msg) return;

	if (msg->errcode!=Error::Success)
	{
		CPEventHelper::uiNotify("HandleMessageRelationOperateResponse", "", msg->errcode);
		return;
	}
  short type = msg->type;
  int step = msg->step;
  int msgtype = step%10;
  int result = step/10 ;
  int oid = 0;

  switch(type)
  {
case RelationshipDefinition::SOCIAL_TYPE_FRIEND:
		if (msgtype==RelationshipDefinition::SOCIAL_OP_REQUEST)
		{
			SocialData::apprenticePid = msg->data.pid;
			SocialData::apprenticeName = msg->data.name;
			SocialData::addFriendData(msg->data.pid,msg->data.name);
			CPEventHelper::msgNotify("UIShowSocialDialog","", Opcode::SOCIAL_OP_REQUEST_ADD_FRIEND_NOTIFY,msg->data.pid,0,0);
			oid = Opcode::SOCIAL_OP_ADD_FRIEND;
		}
		else if (msgtype==RelationshipDefinition::SOCIAL_OP_RESPONSE)
		{
			if (result==RelationshipDefinition::SOCIAL_OP_AGREE)
			{
				SocialData::notifyMsgKey = "agreeAddFriendNotify";
				SocialData::notifyMsgValue = msg->data.name;
				CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"SocialMsgNotifyDialog");
				CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
				// ???????????????
				SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_FRIEND);
				oid = Opcode::SOCIAL_OP_AGREE_ADD_FRIEND_NOTIFY;
			}
			else if (result ==RelationshipDefinition::SOCIAL_OP_REFUSE)
			{
				SocialData::notifyMsgKey = "refuseAddFriendNotify";
				SocialData::notifyMsgValue = msg->data.name;
				CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"SocialMsgNotifyDialog");
				CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
				oid = Opcode::SOCIAL_OP_REFUSE_ADD_FRIEND_NOTIFY;
			}
			else if (result == RelationshipDefinition::SOCIAL_OP_DELETE)
			{
				// ???????????????
				SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_FRIEND);
				oid = Opcode::SOCIAL_OP_DEL_FRIEND;
			}
		}
		break;
	case RelationshipDefinition::SOCIAL_TYPE_ENEMY:
		if (msgtype==RelationshipDefinition::SOCIAL_OP_RESPONSE)
		{
			SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_ENEMY);
			oid = Opcode::SOCIAL_OP_ADD_ENEMY;
		}
		break;
	case RelationshipDefinition::SOCIAL_TYPE_MASTER:
		if (msgtype==RelationshipDefinition::SOCIAL_OP_REQUEST)
		{
			SocialData::apprenticePid = msg->data.pid;
			SocialData::apprenticeName = msg->data.name;
			SocialData::addMasterData(msg->data.pid,msg->data.name);
			CPEventHelper::msgNotify("UIShowSocialDialog","", Opcode::SOCIAL_OP_REQUEST_ADD_MASTER_NOTIFY,msg->data.pid,0,0);
			oid = Opcode::SOCIAL_OP_ADD_MASTER;
		}
		else if (msgtype==RelationshipDefinition::SOCIAL_OP_RESPONSE)
		{
			if (result==RelationshipDefinition::SOCIAL_OP_AGREE)
			{
				SocialData::notifyMsgKey = "agreeAddMasterNotify";
				SocialData::notifyMsgValue = msg->data.name;
				CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"SocialMsgNotifyDialog");
				CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
				// ???????????????
				SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_MASTER);
				oid = Opcode::SOCIAL_OP_AGREE_ADD_MASTER_NOTIFY;
			}
			else if (result ==RelationshipDefinition::SOCIAL_OP_REFUSE)
			{
				SocialData::notifyMsgKey = "refuseAddMasterNotify";
				SocialData::notifyMsgValue = msg->data.name;
				CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"SocialMsgNotifyDialog");
				CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
				oid = Opcode::SOCIAL_OP_REFUSE_ADD_MASTER_NOTIFY;
			}
			else if (result == RelationshipDefinition::SOCIAL_OP_DELETE)
			{
				// ???????????????
				SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_MASTER);
				oid = Opcode::SOCIAL_OP_DEL_MASTER;
			}
		}
		break;
	case RelationshipDefinition::SOCIAL_TYPE_APPRENTICE:
		if (msgtype==RelationshipDefinition::SOCIAL_OP_REQUEST)
		{
			SocialData::masterPid = msg->data.pid;
			SocialData::masterName = msg->data.name;
			SocialData::addApprenticeData(msg->data.pid,msg->data.name);
			CPEventHelper::msgNotify("UIShowSocialDialog","", Opcode::SOCIAL_OP_REQUEST_ADD_APPRENTICE_NOTIFY,msg->data.pid,0,0);
			oid = Opcode::SOCIAL_OP_ADD_APPRENTICE;
		}
		else if (msgtype==RelationshipDefinition::SOCIAL_OP_RESPONSE)
		{
			if (result==RelationshipDefinition::SOCIAL_OP_AGREE)
			{
				SocialData::notifyMsgKey = "agreeAddApprenticeNotify";
				SocialData::notifyMsgValue = msg->data.name;
				CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"SocialMsgNotifyDialog");
				CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
				// ???????????????
				SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_APPRENTICE);
				oid = Opcode::SOCIAL_OP_AGREE_ADD_APPRENTICE_NOTIFY;
			}
			else if (result ==RelationshipDefinition::SOCIAL_OP_REFUSE)
			{
				SocialData::notifyMsgKey = "refuseAddApprenticeNotify";
				SocialData::notifyMsgValue = msg->data.name;
				CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"SocialMsgNotifyDialog");
				CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
				oid = Opcode::SOCIAL_OP_REFUSE_ADD_APPRENTICE_NOTIFY;
			}
			else if (result == RelationshipDefinition::SOCIAL_OP_DELETE)
			{
				// ???????????????
				SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_APPRENTICE);
				oid = Opcode::SOCIAL_OP_DEL_APPRENTICE;
			}
		}
		break;
	case RelationshipDefinition::SOCIAL_TYPE_COUPLE:
		if (msgtype==RelationshipDefinition::SOCIAL_OP_REQUEST)
		{
			if (msg->errcode == Error::Success)
			{
				// ???????????????????????????
				SocialData::bridegroomPid = msg->data.pid;
				SocialData::bridegroomName = msg->data.name;
				CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"ProposalConfirmDialog");
				CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
			}
			else
			{
				// ??????????????????/?????????????????????
				CPEventHelper::uiNotify("HandleMessageRelationOperateResponse", "", msg->errcode);
			}
			oid = Opcode::SOCIAL_OP_REQUEST_ADD_COUPLE_NOTIFY;
		}
		else if (msgtype==RelationshipDefinition::SOCIAL_OP_RESPONSE)
		{
			if (result==RelationshipDefinition::SOCIAL_OP_AGREE)
			{
				// ????????????
				SocialData::notifyMsgKey = "agreeAddCoupleNotify";
				SocialData::notifyMsgValue = msg->data.name;
				CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"SocialMsgNotifyDialog");
				CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
				// ???????????????
				SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_COUPLE);
				oid = Opcode::SOCIAL_OP_AGREE_ADD_COUPLE_NOTIFY;
			}
			else if (result ==RelationshipDefinition::SOCIAL_OP_REFUSE)
			{
				// ????????????
				SocialData::notifyMsgKey = "refuseAddCoupleNotify";
				SocialData::notifyMsgValue = msg->data.name;
				CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"SocialMsgNotifyDialog");
				CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
				oid = Opcode::SOCIAL_OP_REFUSE_ADD_COUPLE_NOTIFY;
			}
			else if (result == RelationshipDefinition::SOCIAL_OP_DELETE)
			{
				// ??????????????????
				SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_COUPLE);
				oid = Opcode::SOCIAL_OP_DEL_COUPLE;
			}
		}
		break;
		/*

	case Opcode::SOCIAL_OP_REQUEST_ADD_COUPLE_NOTIFY:
		{
			CCLog("HandleMessageRelationOperateResponse SOCIAL_OP_REQUEST_ADD_COUPLE_NOTIFY------------------");
			SocialData::bridegroomPid = msg->data.pid;
			SocialData::bridegroomName = msg->data.name;
			CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"ProposalConfirmDialog");
			CPEventHelper::uiNotify("UIShowSocialDialog","",0);
			CPEventHelper::msgNotify("UIShowSocialDialog","",msg->oid,msg->data.pid,0,0);
		}
		break;
	case Opcode::SOCIAL_OP_AGREE_ADD_COUPLE_NOTIFY:
		{
			CCLog("HandleMessageRelationOperateResponse SOCIAL_OP_AGREE_ADD_APPRENTICE_NOTIFY------------------");
			SocialData::notifyMsgKey = "agreeAddCoupleNotify";
			SocialData::notifyMsgValue = msg->data.name;
			CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"SocialMsgNotifyDialog");
			CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
		}
		break;
	case Opcode::SOCIAL_OP_REFUSE_ADD_COUPLE_NOTIFY:
		{
			CCLog("HandleMessageRelationOperateResponse SOCIAL_OP_REFUSE_ADD_COUPLE_NOTIFY------------------");
			SocialData::notifyMsgKey = "refuseAddCoupleNotify";
			SocialData::notifyMsgValue = msg->data.name;
			CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"SocialMsgNotifyDialog");
			CPEventHelper::uiNotify("UIShowSocialDialog","",msg->errcode);
		}
		break;
	case Opcode::SOCIAL_OP_ADD_COUPLE:
		{
			CCLog("HandleMessageRelationOperateResponse SOCIAL_OP_ADD_COUPLE------------------");
			// ???????????????
			SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_COUPLE);
		}
		break;
	case Opcode::SOCIAL_OP_DEL_COUPLE:
		{
			CCLog("HandleMessageRelationOperateResponse SOCIAL_OP_DEL_COUPLE------------------");
			// ???????????????
			SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_COUPLE);
		}
		break;
		*/
	}
	CPEventHelper::msgNotify("HandleMessageRelationOperateResponse","",oid,msg->data.name,0,0); 
	
}

void MsgMaster::HandleMessageRelationFindingResponse( IMsg *pMsg )
{
	MsgRelationFindingResponse *msg = dynamic_cast<MsgRelationFindingResponse *>(pMsg);
	if (!msg) return;

	if (msg->errcode!=Error::Success)
	{
		CPEventHelper::uiNotify("HandleMessageRelationFindingResponse", "", msg->errcode);
		return;
	}
	CPEventHelper::setEventStringData(CPEventName::UI_OPEN,CPEventData::VALUE_2,msg->name);
	CPEventHelper::setEventIntData(CPEventName::UI_OPEN,CPEventData::VALUE_3,msg->sceneid);
	CPEventHelper::setEventIntData(CPEventName::UI_OPEN,CPEventData::VALUE_4,msg->posx);
	CPEventHelper::setEventIntData(CPEventName::UI_OPEN,CPEventData::VALUE_5,msg->posy);
	CPEventHelper::openPanel("NoticePanel");
}
