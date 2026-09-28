#include "SystemData.h"
#include "cocos2d.h"
#include "res/Path.h"
#include <fstream>
#include <sstream>
#include "GameData.h"
#include "NPCFunctionData.h"
#include "CCFileUtils.h"
#include "ext/CCMenuItemTextImage.h"
#include "curl.h"
#include "script/MainLua.h"
#include "userdata/luadata/LuaData.h"
#include "QuestDefinition.h"
#include "MsgScene.h"
#include "network/HandleMessage.h"
#include "UserData.h"
#include "TaskData.h"
#include "HeroData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/GhostManager.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "script/LuaWrapper.h"
#include "SceneDefinition.h"
#include "NPCDefinition.h"
#include "scene/panel/NPCPanel.h"
#include "ItemDefinition.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "utils/TestUtils.h"
#include "utils/RichTextUtils.h"
#include "ext/CCActionDestroy.h"
#include "MsgWorld.h"
#include "WorldData.h"
#include "MsgActivity.h"
#include "event/CPEventHelper.h"
#include "logic/BagOperator.h"
#include "userdata/TaskData.h"
#include "userdata/LayoutData.h"
#include "module/TaskModule.h"

#include <algorithm>

using namespace cocos2d;

stack<int> npcIDstack;

int NPCFunctionData::m_iNPCStaticID=0;
std::string NPCFunctionData::m_sNPCname="";
bool NPCFunctionData::m_bIsSub=false;
bool NPCFunctionData::m_bIsReadMe=false;

bool NPCFuncSort(npcFunction v1, npcFunction v2){
	return v1.numid < v2.numid;
}

CCArray* NPCFunctionData::getnpcFunction( std::vector<npcFunction> FunctionList ,bool isSub)
{
	CCArray *pArray=CCArray::create();
	std::vector<npcFunction>::iterator it;
	bool flag1=false;//????в?????????
	if (!FunctionList.empty())
	{
		sort(FunctionList.begin(),FunctionList.end(),NPCFuncSort);
		for (it=FunctionList.begin();it!=FunctionList.end();it++)
		{
			npcFunction func=(npcFunction)*it;
			if (func.functionid==7)
			{
				flag1=true;
			}
			CCMenuItemSprite* pItem=getSingleFunc(func);
			if (pItem)
			{
				pArray->addObject(pItem);  
			}
		}		
	}
	if (!flag1 && isSub)
	{
		//????????????????
		npcFunction func;
		func.functionid=NPC::Function_BackTop;
		if (npcIDstack.size()!=0)
		{
			func.data=npcIDstack.top();
			CCMenuItemSprite* pItem=getSingleFunc(func);
			if (pItem)
			{
				pArray->addObject(pItem);
			}
		}
		
	}
	return pArray;
}

	std::string ShopName[7]={
		"药品","杂货","武器","首饰","防具","书籍","特殊"
	};

CCMenuItemSprite* NPCFunctionData::getSingleFunc(npcFunction nFunc)
{
	CCMenuItemSprite* pItem;
	if(nFunc.show==0)
	{
		return NULL;
	}
	if (nFunc.functionid==NPC::Function_Shop)//?????
	{
		//CCLog("----------------------npcid: %d",nFunc.data);
		//CCLabelTTF* pLabel=CCLabelTTF::create(AToU8(ShopName[nFunc.data-10].c_str()),"??????",20);
		CPRichText* pLabel=RichTextUtils::getRichText(AToU8(ShopName[nFunc.data-10].c_str()),20);
		pItem=CCMenuItemSprite::create(pLabel,pLabel,NULL,NULL,NULL);
		pItem->setTag(TAG_NPCSHOP);
		npcFunction* func=new npcFunction();
		func->functionid=nFunc.functionid;
		func->data=nFunc.data;
		pItem->setUserData(func);
		return pItem;
	}
	else if (nFunc.functionid==NPC::Function_Portal)//??????
	{
		//????id??????????
		std::string MapName;
		LuaData::getProp(LuaData::MAP,nFunc.data,"name",MapName);
		//CCLabelTTF* pLabel=CCLabelTTF::create(MapName.c_str(),"??????",20);
		CPRichText* pLabel=RichTextUtils::getRichText(MapName.c_str(),20);
		pItem=CCMenuItemSprite::create(pLabel,pLabel,NULL,NULL,NULL);
		pItem->setTag(TAG_CHANGEMAP);
		npcFunction* func=new npcFunction();
		func->functionid=nFunc.functionid;
		func->data=nFunc.data;
		pItem->setUserData(func);
	}
	else if (nFunc.functionid==NPC::Function_ScriptC)//???????
	{
		std::string TitleName;
		/*
		Ghost* targetGhost = GameData::s_user->m_pGhostManager->getGhostById(GameData::s_user->m_nNpcTalkId);
		int npcID=targetGhost->mStaticID;*/ 
		LuaData::getProp_NPCfunc(LuaData::NPC,NPCFunctionData::getNPCID(),"nFunction",nFunc.functionid,nFunc.data,TitleName);

		std::string content;
		NPCFunctionData::getNPCfuncNameSub(NPCFunctionData::getNPCID(),TitleName,content);
		CPRichText* pLabel=RichTextUtils::getRichText((content.c_str()),20);
		pItem=CCMenuItemSprite::create(pLabel,pLabel,NULL,NULL,NULL);
		pItem->setTag(TAG_SCRIPT_C);
		npcFunction* func=new npcFunction();
		func->functionid=nFunc.functionid;
		func->data=nFunc.data;
		pItem->setUserData(func);
	}
	else if (nFunc.functionid==NPC::Function_ScriptS)//?????????
	{
		std::string TitleName;
		/*std::string TitleName; 
		Ghost* targetGhost = GameData::s_user->m_pGhostManager->getGhostById(GameData::s_user->m_nNpcTalkId);
		int npcID=targetGhost->mStaticID;*/
		LuaData::getProp_NPCfunc(LuaData::NPC,NPCFunctionData::getNPCID(),"nFunction",nFunc.functionid,nFunc.data,TitleName);

		std::string content;
		NPCFunctionData::getNPCfuncNameSub(NPCFunctionData::getNPCID(),TitleName,content);
		//CCLabelTTF* pLabel=CCLabelTTF::create(AToU8(TitleName.c_str()),"??????",20);
		CPRichText* pLabel=RichTextUtils::getRichText(content.c_str(),20);
		pItem=CCMenuItemSprite::create(pLabel,pLabel,NULL,NULL,NULL);
		pItem->setTag(TAG_SCRIPT_S);
		npcFunction* func=new npcFunction();
		func->functionid=nFunc.functionid;
		func->data=nFunc.data;
		pItem->setUserData(func);
	} 
	else if (nFunc.functionid==NPC::Function_ShowText)// ??????
	{
		std::string TitleName;
		LuaData::getProp(LuaData::NPC,nFunc.data,"name",TitleName);
		//CCLabelTTF* pLabel=CCLabelTTF::create(TitleName.c_str(),"??????",20);
		std::string content;
		NPCFunctionData::getNPCfuncNameSub(nFunc.data,TitleName,content);
		CPRichText* pLabel=RichTextUtils::getRichText((content.c_str()),20);
		pItem=CCMenuItemSprite::create(pLabel,pLabel,NULL,NULL,NULL);
		pItem->setTag(TAG_SHOWTALK);
		npcFunction* func=new npcFunction();
		func->functionid=nFunc.functionid;
		func->data=nFunc.data;
		pItem->setUserData(func);		
	} 
	else if (nFunc.functionid==NPC::Function_SubNPC)//????NPC
	{
		std::string TitleName;
		LuaData::getProp(LuaData::NPC,nFunc.data,"name",TitleName);
		//CCLabelTTF* pLabel=CCLabelTTF::create(TitleName.c_str(),"??????",20); 

		std::string content;
		NPCFunctionData::getNPCfuncNameSub(nFunc.data,TitleName,content);
		CPRichText* pLabel=RichTextUtils::getRichText((content.c_str()),20);
		pItem=CCMenuItemSprite::create(pLabel,pLabel,NULL,NULL,NULL);
		pItem->setTag(TAG_CONNNPC);
		npcFunction* func=new npcFunction();
		func->functionid=nFunc.functionid;
		func->data=nFunc.data;
		pItem->setUserData(func);
	} 
	else if (nFunc.functionid==NPC::Function_BackTop)//???????NPC 
	{
		std::string TitleName="返回";
		//LuaData::getProp(LuaData::NPC,nFunc.data,"name",TitleName);
		//CCLabelTTF* pLabel=CCLabelTTF::create(AToU8(TitleName.c_str()),"??????",20);

		CPRichText* pLabel=RichTextUtils::getRichText(AToU8(TitleName.c_str()),20);
		pItem=CCMenuItemSprite::create(pLabel,pLabel,NULL,NULL,NULL);
		pItem->setTag(TAG_BACK);
		npcFunction* func=new npcFunction();
		func->functionid=nFunc.functionid;
		func->data=nFunc.data;
		pItem->setUserData(func);
	} 
	else if (nFunc.functionid==NPC::Function_BackScene)//???????????????????
	{
		std::string TitleName;
		/*std::string TitleName; 
		Ghost* targetGhost = GameData::s_user->m_pGhostManager->getGhostById(GameData::s_user->m_nNpcTalkId);
		int npcID=targetGhost->mStaticID;*/
		LuaData::getProp_NPCfunc(LuaData::NPC,NPCFunctionData::getNPCID(),"nFunction",nFunc.functionid,nFunc.data,TitleName);

		//CCLabelTTF* pLabel=CCLabelTTF::create(AToU8(TitleName.c_str()),"??????",20); 
		//CCLog("title name = %s",TitleName.c_str()); 
		CPRichText* pLabel=RichTextUtils::getRichText((TitleName.c_str()),20);
		pItem=CCMenuItemSprite::create(pLabel,pLabel,NULL,NULL,NULL);
		pItem->setTag(TAG_BACKSCENE);
		npcFunction* func=new npcFunction();
		func->functionid=nFunc.functionid;
		func->data=nFunc.data; 
		pItem->setUserData(func);
	}
	return pItem;
}


CCLabelTTF* NPCFunctionData::getSingleQuest( int qid )
{
	std::string TaskName;
	LuaData::getProp(LuaData::QUEST, qid,"name",TaskName);
	CCLabelTTF* pLabel=CCLabelTTF::create(TaskName.c_str(),"微软雅黑",15);				
	CCLabelTTF* pLabelhead = NULL;			
	CCLabelTTF* pLabelstate = NULL;		
	CCLabelTTF* pLabellvl = NULL;
	int questlvl=0;
	LuaData::getProp(LuaData::QUEST, qid,"req_lvl",questlvl);
	ccColor3B color={186,85,211};
	//????????????????? ???  ???????
	const int state = TaskData::getTaskState(qid);
	if (state==Quest::state_Available)
	{
		color=ccYELLOW;
		pLabelstate=SystemData::getLabelTTF("NPCTalk_weijieshou");
		pLabelstate->setFontSize(16);
		pLabelstate->setAnchorPoint(ccp(0,0.5));	
		pLabelstate->setPosition(ccp(pLabel->getContentSize().width,pLabel->getContentSize().height/2));
	}
	else if (state==Quest::state_NotFinished)
	{
		pLabelstate=SystemData::getLabelTTF("NPCTalk_jinxingzhong");
		pLabelstate->setFontSize(16);
		pLabelstate->setAnchorPoint(ccp(0,0.5));	
		pLabelstate->setPosition(ccp(pLabel->getContentSize().width,pLabel->getContentSize().height/2));
	}
	else if (state==Quest::state_Finished)
	{
		color=ccGREEN;
		pLabelstate=SystemData::getLabelTTF("NPCTalk_yiwancheng");
		pLabelstate->setFontSize(16);
		pLabelstate->setAnchorPoint(ccp(0,0.5));	
		pLabelstate->setPosition(ccp(pLabel->getContentSize().width,pLabel->getContentSize().height/2));
	}
	else
	{
		return NULL;
	}

	if (pLabelstate)
	{
		pLabelstate->setColor(color);
	}

	const int line = TaskData::getTaskLine(qid);
	if (line==Quest::line_Main)
	{
		CCString* pStr=CCString::createWithFormat("%d??",GameData::s_user->m_pMainRole->mLevel);
		pLabellvl=CCLabelTTF::create(AToU8(pStr->getCString()),"",16);
		pLabellvl->setFontSize(16);
		pLabellvl->setAnchorPoint(ccp(0,0.5));	
		pLabellvl->setPosition(ccp(pLabel->getContentSize().width+pLabelstate->getContentSize().width,pLabelstate->getPositionY()));

		pLabelhead=SystemData::getLabelTTF("NPCTalk_zhuxian");
		pLabelhead->setFontSize(16);
		pLabelhead->setAnchorPoint(ccp(0,0.5));	
		pLabelhead->setPosition(ccp(-pLabelhead->getContentSize().width,pLabelstate->getPositionY()));
	}
	else if (line==Quest::line_Daily)
	{
		CCString* pStr=CCString::createWithFormat("%d??",GameData::s_user->m_pMainRole->mLevel);
		pLabellvl=CCLabelTTF::create(AToU8(pStr->getCString()),"",16);
		pLabellvl->setFontSize(16);
		pLabellvl->setAnchorPoint(ccp(0,0.5));	
		pLabellvl->setPosition(ccp(pLabel->getContentSize().width+pLabelstate->getContentSize().width,pLabelstate->getPositionY()));

		pLabelhead=SystemData::getLabelTTF("NPCTalk_meiri");
		pLabelhead->setFontSize(16);
		pLabelhead->setAnchorPoint(ccp(0,0.5));	
		pLabelhead->setPosition(ccp(-pLabelhead->getContentSize().width,pLabelstate->getPositionY()));
	}
	else if (line==Quest::line_Exp)
	{
		CCString* pStr=CCString::createWithFormat("%d??",questlvl);
		pLabellvl=CCLabelTTF::create(AToU8(pStr->getCString()),"",16);
		pLabellvl->setFontSize(16);
		pLabellvl->setAnchorPoint(ccp(0,0.5));	
		pLabellvl->setPosition(ccp(pLabel->getContentSize().width+pLabelstate->getContentSize().width,pLabelstate->getPositionY()));

		pLabelhead=SystemData::getLabelTTF("NPCTalk_jingyan");
		pLabelhead->setFontSize(16);
		pLabelhead->setAnchorPoint(ccp(0,0.5));	
		pLabelhead->setPosition(ccp(-pLabelhead->getContentSize().width,pLabelstate->getPositionY()));
	}
	else if (line==Quest::line_Honor)
	{
		CCString* pStr=CCString::createWithFormat("%d??",questlvl);
		pLabellvl=CCLabelTTF::create(AToU8(pStr->getCString()),"",16);
		pLabellvl->setFontSize(16);
		pLabellvl->setAnchorPoint(ccp(0,0.5));	
		pLabellvl->setPosition(ccp(pLabel->getContentSize().width+pLabelstate->getContentSize().width,pLabelstate->getPositionY()));

		pLabelhead=SystemData::getLabelTTF("NPCTalk_rongyu");
		pLabelhead->setFontSize(16);
		pLabelhead->setAnchorPoint(ccp(0,0.5));	
		pLabelhead->setPosition(ccp(-pLabelhead->getContentSize().width,pLabelstate->getPositionY()));
	}
	else if (line==Quest::line_Money)
	{
		CCString* pStr=CCString::createWithFormat("%d??",questlvl);
		pLabellvl=CCLabelTTF::create(AToU8(pStr->getCString()),"",16);
		pLabellvl->setFontSize(16);
		pLabellvl->setAnchorPoint(ccp(0,0.5));	
		pLabellvl->setPosition(ccp(pLabel->getContentSize().width+pLabelstate->getContentSize().width,pLabelstate->getPositionY()));

		pLabelhead=SystemData::getLabelTTF("NPCTalk_jinbi");
		pLabelhead->setFontSize(16);
		pLabelhead->setAnchorPoint(ccp(0,0.5));	
		pLabelhead->setPosition(ccp(-pLabelhead->getContentSize().width,pLabelstate->getPositionY()));
	}
	else if (line==Quest::line_Emigrated)
	{
		CCString* pStr=CCString::createWithFormat("%d??",GameData::s_user->m_pMainRole->mLevel);
		pLabellvl=CCLabelTTF::create(AToU8(pStr->getCString()),"",16);
		pLabellvl->setFontSize(16);
		pLabellvl->setAnchorPoint(ccp(0,0.5));	
		pLabellvl->setPosition(ccp(pLabel->getContentSize().width+pLabelstate->getContentSize().width,pLabelstate->getPositionY()));

		pLabelhead=SystemData::getLabelTTF("NPCTalk_caishen");
		pLabelhead->setFontSize(16);
		pLabelhead->setAnchorPoint(ccp(0,0.5));	
		pLabelhead->setPosition(ccp(-pLabelhead->getContentSize().width,pLabelstate->getPositionY()));
	}

	if (pLabelhead)
	{
		pLabelhead->setColor(color);
	}

	if (pLabellvl)
	{
		pLabellvl->setColor(ccGREEN);
	}
	
	if (pLabelstate)
	{
		pLabel->addChild(pLabelstate);
	}

	if (pLabellvl && line!=Quest::line_Main)
	{
		pLabel->addChild(pLabellvl);
	}

	if (pLabelhead)
	{
		pLabel->addChild(pLabelhead);
	}
	pLabel->setAnchorPoint(ccp(0,0.5));
	pLabel->setPosition(ccp(60,pLabel->getContentSize().height/2));
	pLabel->setColor(color);

	return pLabel;

}

CCString* NPCFunctionData::getCString( int qid,  int ptype)
{
	CCString* pStr=NULL;
	std::string str;
	int i=0;
	const int state = TaskData::getTaskState(qid);
	if (state==Quest::state_Finished || ptype == TAG_STATE_3)
	{
		//??? ?????XXXXX
		std::string str1=SystemData::getLayoutString("Task_Label2");
		int npcid;
		LuaData::getProp(LuaData::QUEST,qid,"npc_tgt",npcid);
		LuaData::getProp(LuaData::NPC,npcid,"name",str);
		pStr=CCString::createWithFormat("%s%s",str1.c_str(),str.c_str());
	}
	else if (state==Quest::state_NotFinished ||( ptype == TAG_STATE_2 && state==Quest::state_Available))
	{
		//??? XXXXX 0/5
		int datax = 0, datay = 0, dataz = 0;
		TaskData::getTaskExData(qid, datax, datay, dataz);
		LuaData::getProp(LuaData::QUEST,qid,"target_content",str);
		LuaData::getProp(LuaData::QUEST,qid,"target_datay",i);
		pStr=CCString::createWithFormat("%s %d/%d",str.c_str(),datay,i);
		if (str=="0")
		{
			pStr=CCString::createWithFormat(" ");
		}
	}
	else if (ptype == TAG_STATE_1)//δ????????tasktips???
	{
		//??? ????XXXXX
		std::string str1=SystemData::getLayoutString("Task_Label1");
		LuaData::getProp(LuaData::QUEST,qid,"name",str);
		pStr=CCString::createWithFormat("%s%s",str1.c_str(),str.c_str());
	}
	return pStr;
}

void NPCFunctionData::useShoes( int sid,int reason/*=0*/ )
{
	if (CommonFunction::checkShoesCount(sid,reason)!=Error::Success)
	{
		return;
	}
	MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
	sceneMsg->sid = sid;
	sceneMsg->reason = reason;
	HandleMessage::sendMessage(sceneMsg);
}

void NPCFunctionData::getShoesFunc( int qid ,int ptype)
{	
	int NPCID=0;
	int area=0;
	const int state = TaskData::getTaskState(qid);
	if (state==Quest::state_Available && ptype==TAG_GOTOTASK)
	{
		//???????? ?????????λ??
		AcceptQuest(qid);
		int type;
		LuaData::getProp(LuaData::QUEST,qid,"type",type);
		int datax = 0, datay = 0, dataz = 0;
		TaskData::getTaskExData(qid, datax, datay, dataz);
		if (type == Quest::type_MonsterKill)//???????????????
		{
			/*MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
			sceneMsg->sid = datax;
			sceneMsg->reason = Scene::seMonster;
			HandleMessage::sendMessage(sceneMsg);*/
			useShoes(datax,Scene::seMonster);
		}
		else if(type == Quest::type_Talk)
		{
			/*MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
			sceneMsg->sid = datax;
			sceneMsg->reason = Scene::seNpc;
			HandleMessage::sendMessage(sceneMsg);*/
			useShoes(datax,Scene::seNpc);
		}
	}
	else if (state==Quest::state_Available && ptype==TAG_GOTONPC)
	{		
		int srcnpc;
		LuaData::getProp(LuaData::QUEST,qid,"npc_src",srcnpc);
		/*MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
		sceneMsg->sid = srcnpc;
		sceneMsg->reason = Scene::seNpc;
		HandleMessage::sendMessage(sceneMsg);*/
		useShoes(srcnpc,Scene::seNpc);
	}	
	else if (state==Quest::state_NotFinished) 
	{
		int type;
		LuaData::getProp(LuaData::QUEST,qid,"type",type);
		if (type == Quest::type_MonsterKill)//???????????????
		{
			LuaData::getProp(LuaData::QUEST,qid,"target_area",area);
			/*MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
			sceneMsg->sid = area;
			sceneMsg->reason = Scene::seMonster;
			HandleMessage::sendMessage(sceneMsg);*/
			useShoes(area,Scene::seMonster);
		}
		else if(type == Quest::type_MonsterKillInMap)
		{
			LuaData::getProp(LuaData::QUEST,qid,"target_area",area);
			/*MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
			sceneMsg->sid = area;
			sceneMsg->reason = Scene::seInstance;
			HandleMessage::sendMessage(sceneMsg);*/
			useShoes(area,Scene::seInstance);
		}	
		else if(type == Quest::type_MonsterKillWithLvl)
		{
			LuaData::getProp(LuaData::QUEST,qid,"target_area",area);
			/*MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
			sceneMsg->sid = area;
			sceneMsg->reason = Scene::seMonster;
			HandleMessage::sendMessage(sceneMsg);*/
			useShoes(area,Scene::seMonster);
		}	
		else if(type == Quest::type_ItemCollect)
		{
			LuaData::getProp(LuaData::QUEST,qid,"target_area",area);
			/*MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
			sceneMsg->sid = area;
			sceneMsg->reason = Scene::seMonster;
			HandleMessage::sendMessage(sceneMsg);*/
			useShoes(area,Scene::seMonster);
		}	
		else if(type == Quest::type_Talk)
		{
			LuaData::getProp(LuaData::QUEST,qid,"target_area",area);
			/*MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
			sceneMsg->sid = area;
			sceneMsg->reason = Scene::seNpc;
			HandleMessage::sendMessage(sceneMsg);*/
			useShoes(area,Scene::seNpc);
		}
	}	
	else if (state==Quest::state_Finished)
	{
		int tgtnpc;
		LuaData::getProp(LuaData::QUEST,qid,"npc_tgt",tgtnpc);
		/*MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
		sceneMsg->sid = tgtnpc;
		sceneMsg->reason = Scene::seNpc;
		HandleMessage::sendMessage(sceneMsg);*/
		useShoes(tgtnpc,Scene::seNpc);
	}
	//dealwithQuest( qid );
}

void NPCFunctionData::AcceptQuest( int qid )
{
	MsgQuestAcceptRequest* req = new MsgQuestAcceptRequest;
	req->qid=TaskData::getTaskLine(qid);
	req->sid=qid;
	HandleMessage::sendMessage(req);
}

void NPCFunctionData::SubmitQuest( int qid )
{
	MsgQuestSubmitRequest* req = new MsgQuestSubmitRequest;
	req->qid=TaskData::getTaskLine(qid);
	HandleMessage::sendMessage(req);
}

void NPCFunctionData::GiveUpQuest( int qid )
{
	MsgQuestRemoveRequest* req = new MsgQuestRemoveRequest;
	req->qid=TaskData::getTaskLine(qid);
	HandleMessage::sendMessage(req);
}

void NPCFunctionData::QuickQuest( int qid )
{
	int cnt = GameData::s_user->getUserItemData()->getItemCntBySid(SystemData::getLayoutValue("任务完成符"));
	if (cnt!=0)
	{
		MsgQuestQuickFinishRequest* req = new MsgQuestQuickFinishRequest;
		req->qid=TaskData::getTaskLine(qid);
		HandleMessage::sendMessage(req);
	}
	else
	{
		CPEventHelper::uiNotify("","",Error::NotEnoughItem); 
	}
}

void NPCFunctionData::hideNPCTalkPanel()
{
	if (Game::getGameUI())
	{
		Game::getGameUI()->hidePanel(TAG_TALK_PANEL);
	}
}

void NPCFunctionData::dealwithQuest( int qid )
{
	if (qid <= 0)
	{
		return;
	}
	GameRole* myRole = GameData::getMyRole();
	if (!myRole) return;
	myRole->stopAutoMoving();
	int NPCID=0;
	int area=0;
	int line=TaskData::getTaskLine(qid);
	const int state = TaskData::getTaskState(qid);
	int type;
	LuaData::getProp(LuaData::QUEST,qid,"type",type);
	myRole->m_iTargetSid=0;
	if (state==Quest::state_Finished)
	{		
		LuaData::getProp(LuaData::QUEST,qid,"npc_tgt",NPCID);
		GameData::s_user->m_pGhostManager->gotoGhostPos(NPCID,"npcs",GHOST_TYPE_NPC);
	}	
	else if (state==Quest::state_NotFinished) 
	{
		if (type == Quest::type_MonsterKill)//???????????????
		{
			LuaData::getProp(LuaData::QUEST,qid,"target_area",area);
			//GameData::s_user->m_pGhostManager->gotoGhostPos(area,"monsters",GHOST_TYPE_MONSTER);
			GameData::s_user->m_pGhostManager->gotoFindMonster(area);
			myRole->setEasyAI(true);
		}
		else if (type == Quest::type_MonsterKillInMap)
		{
			LuaData::getProp(LuaData::QUEST,qid,"target_area",area);
			GameData::s_user->m_pGhostManager->gotoMapKillMonster(area,GHOST_TYPE_MONSTER);
			myRole->setEasyAI(true);
		}
		else if (type == Quest::type_MonsterKillWithLvl)
		{
			LuaData::getProp(LuaData::QUEST,qid,"target_area",area);
			GameData::s_user->m_pGhostManager->gotoGhostPos(area,"monsters",GHOST_TYPE_MONSTER);
			myRole->setEasyAI(true);
		}
		else if (type == Quest::type_ItemCollect)
		{
			LuaData::getProp(LuaData::QUEST,qid,"target_area",area);
			GameData::s_user->m_pGhostManager->gotoGhostPos(area,"monsters",GHOST_TYPE_MONSTER);
			myRole->setEasyAI(true);
		}
		else if (type == Quest::type_GoToInstance)
		{
			LuaData::getProp(LuaData::QUEST,qid,"npc_tgt",area);
			GameData::s_user->m_pGhostManager->gotoGhostPos(area,"npcs",GHOST_TYPE_NPC);
		}
		else
		{
			LuaData::getProp(LuaData::QUEST,qid,"target_area",area);
			GameData::s_user->m_pGhostManager->gotoGhostPos(area,"npcs",GHOST_TYPE_NPC);
		}
		/*AliveGhost* pGhost=GameData::s_user->m_pMainRole->getTheAim();
		if (pGhost)
		{
			if(!checkIsQuestMonster(pGhost->getDress(AVATAR_TYPE_CLOTH)))
			{
				GameData::s_user->m_pMainRole->changeTheAim(NULL);
			}
		}*/
	}
	else if (state==Quest::state_Available)
	{
		LuaData::getProp(LuaData::QUEST,qid,"npc_src",NPCID);	
		GameData::s_user->m_pGhostManager->gotoGhostPos(NPCID,"npcs",GHOST_TYPE_NPC);
	}

	GameData::getMyRole()->setQuestDoing(true);
	TaskData::setCurrentDoingTask(qid);
	if (type == Quest::type_Talk && state==Quest::state_Finished && line!=Quest::line_Main)
	{
		return;
	}
	hideNPCTalkPanel();
}

void NPCFunctionData::clickFunctionScriptC(int npcid, int data)
{
	Lua::instance()->push(npcid);
	Lua::instance()->push(data);
	Lua::instance()->call("npc_talk_handler", 2, 0); 
}

void NPCFunctionData::clickFunctionScriptS(int npcid, int data)
{
	MsgClickNPCFunctionScriptRequest* req = new MsgClickNPCFunctionScriptRequest;
	req->NPCid = npcid;
	req->data = data;
	HandleMessage::sendMessage(req);
}

void NPCFunctionData::clickOtherNpc( int npcid, bool isSub/*=false*/, bool isReadme/*=false*/ )
{
	if (NPCFunctionData::getNPCID()!=0)
	{
		if (isSub)
		{
			npcIDstack.push(NPCFunctionData::getNPCID());
		}
		else
		{
			if (npcIDstack.size()!=0)
			{
				if (npcIDstack.top()==npcid && npcIDstack.size()>1)
				{
					npcIDstack.pop();
				}
				else
				{
					while (npcIDstack.size()!=0 && npcIDstack.top()!=npcid)
					{
						npcIDstack.pop();
					}
				}
				if (npcIDstack.size()>=1)
				{
					isSub=true;
				}
			}			
		}
		NPCFunctionData::setNPCID(npcid);
		NPCFunctionData::setReadmeAndSub(isReadme,isSub);
		NPCFunctionData::updatedynamicData(NPCFunctionData::getNPCID());
		MsgClickNPCRequest* req = new MsgClickNPCRequest;
		req->NPCid=npcid;
		HandleMessage::sendMessage(req); 
	}
	
}

void NPCFunctionData::clearNpcStack()
{
	while (npcIDstack.size()!=0)
	{
		npcIDstack.pop();
	}
}

bool NPCFunctionData::checkIsQuestMonster( int id )
{
	const IDVector &quests = TaskData::getCurrentTasks();
	for (int i = 0; i < (int)quests.size(); i++)
	{
		int area = 0, datax = 0, datay = 0, dataz = 0,type=0;
		LuaData::getProp(LuaData::QUEST, quests[i], "type", type);
		LuaData::getProp(LuaData::QUEST, quests[i], "target_area", area);
		TaskData::getTaskExData(quests[i], datax, datay, dataz);
		if (TaskData::getTaskState(quests[i])==Quest::state_NotFinished)
		{
			if ((id == datax || id==area) && type==Quest::type_MonsterKill)
			{
				TaskData::setCurrentDoingTask(quests[i]);
				return true;
			}
			else if (type==Quest::type_MonsterKillInMap && (GameData::s_user->mMap.mID==area || GameData::s_user->mMap.mID==datax ))
			{
				TaskData::setCurrentDoingTask(quests[i]);
				return true;
			}
			else if (type==Quest::type_MonsterKillWithLvl )
			{
				int lvl=LuaData::getProp(LuaData::MONSTER,id,"lvl",lvl);
				if (lvl>=area || lvl>=datax)
				{
					TaskData::setCurrentDoingTask(quests[i]);
					return true;
				}
			}
			else if (type==Quest::type_ItemCollect && id==area)
			{
				TaskData::setCurrentDoingTask(quests[i]);
				return true;
			}
		}
	}
	return false;
}

bool NPCFunctionData::getNPCcontent( int npcid ,std::string& content)
{
	Lua::instance()->push(npcid);	
	if(	Lua::instance()->call("get_npc_talkcontent", 1, 1) &&
		Lua::instance()->pop_utf8(content)) 
	{ 
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : npc_talk_handler string"); 
	}
	return false;   
}

bool NPCFunctionData::getNPCfuncNameSub( int npcid,std::string str,std::string& content )
{
	Lua::instance()->push(npcid);
	Lua::instance()->push_utf8(str);	
	if(	Lua::instance()->call("get_npc_talkfuncname_sub", 2, 1) &&
		Lua::instance()->pop_utf8(content)) 
	{ 
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_npc_talkfuncname_sub string"); 
	}
	return false;
}

bool NPCFunctionData::getNPCcontentSub( int npcid,std::string str,std::string& content )
{
	Lua::instance()->push(npcid);	
	Lua::instance()->push_utf8(str);	
	if(	Lua::instance()->call("get_npc_talkcontent_sub", 2, 1) &&
		Lua::instance()->pop_utf8(content)) 
	{ 
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : npc_talk_handler string"); 
	}
	return false;
}


CPRichText* NPCFunctionData::getNPCallContent( int npcid,int width, int height )
{
	CPRichText* pRichText=CPRichText::create(width,height);
	std::string newContent;
	int contentsize=0;
	LuaData::getProp_size(LuaData::NPC,npcid,"text",contentsize);
	TestUtils::timeTestBegin();
	for (int i=1;i<=contentsize;i++) 
	{ 
		std::string oldstr;
		std::string colorstr;
		LuaData::getProp(LuaData::NPC,npcid,"text",i,"color",colorstr);
		LuaData::getProp(LuaData::NPC,npcid,"text",i,"content",oldstr);
		if (!NPCFunctionData::getNPCcontentSub(npcid,oldstr,newContent)) 
		{
			return NULL;
		}
		ccColor3B color=ccWHITE;
		if (colorstr=="g")
		{
			color=ccGREEN;
		}
		else if (colorstr=="b")
		{
			color=ccBLUE;
		}
		else if (colorstr=="y")
		{
			color=ccYELLOW;
		}
		else if (colorstr=="o")
		{
			color=ccORANGE;
		}
		else if (colorstr=="w")
		{
			color=ccWHITE;
		}
		CPRichTextItemLabel* pText=new CPRichTextItemLabel(newContent,"",18,color);
		pRichText->addItem(pText);
	}
	TestUtils::timeTestEnd("NPCFunctionData::getNPCallContent");
	return pRichText;
}

CPRichText* NPCFunctionData::getBigContent( int contentid,int width, int height )
{
	CPRichText* pRichText=CPRichText::create(width,height);
	std::string newContent;
	int contentsize=0;
	LuaData::getProp_size("gdBigContent",contentid,"text",contentsize);

	TestUtils::timeTestBegin();
	for (int i=1;i<=contentsize;i++) 
	{ 
		std::string oldstr;
		std::string colorstr;
		LuaData::getProp("gdBigContent",contentid,"text",i,"color",colorstr);
		LuaData::getProp("gdBigContent",contentid,"text",i,"content",oldstr);

		if (!NPCFunctionData::getNPCcontentSub(contentid,oldstr,newContent)) 
		{
			return NULL;
		}

		ccColor3B color=ccWHITE;
		if (colorstr=="g")
		{
			color=ccGREEN;
		}
		else if (colorstr=="b")
		{
			color=ccBLUE;
		}
		else if (colorstr=="y")
		{
			color=ccYELLOW;
		}
		else if (colorstr=="o")
		{
			color=ccORANGE;
		}
		else if (colorstr=="w")
		{
			color=ccWHITE;
		}
		CPRichTextItemLabel* pText=getSubContent(newContent,color,18);
		if (pText)
		{
			pRichText->addItem(pText);
		}
	}
	TestUtils::timeTestEnd("NPCFunctionData::getBigContent");
	return pRichText;
}

CPRichTextItemLabel* NPCFunctionData::getSubContent( std::string str,ccColor3B color,int size )
{
	CPRichTextItemLabel* pText=new CPRichTextItemLabel(str,"",size,color);
	if (pText)
	{
		return pText;
	}
	return NULL;
}

std::vector<QuestReward> NPCFunctionData::getQuestReward( int qid )
{
	std::vector<QuestReward> questrewardlist;
	std::string str[5]={
		"taskcontent_Exp","taskcontent_gold","taskcontent_Vcoin","taskcontent_Money","taskcontent_Honor"
	};

	const int line = TaskData::getTaskLine(qid);
	if (line==Quest::line_Main )
	{
		int size=0;
		int m=0;
		LuaData::getProp_size(LuaData::QUEST,qid,LuaData::QUEST_SUB,size);
		for (int i=0;i<size;i++)
		{
			int  type;
			int count;
			LuaData::getProp(LuaData::QUEST,qid,LuaData::QUEST_SUB,(i+1),LuaData::QUEST_SUB_1,LuaData::QUEST_SUB_2,type,count);
			if (count==0)
			{
				m++;
				continue;
			}
			if (type==0)
			{
				int id=0;
				switch (HeroData::getJob())
				{
				case UserData::CARRER_ZS:
					id=1;
					break;
				case UserData::CARRER_FS:
					id=3;
					break;
				case UserData::CARRER_DS:
					id=5;
					break;
				case UserData::CARRER_OMNI:
					id=1;
					break;
				default:
					break;
				}
				if (HeroData::getGender()==UserData::SEX_FEMALE)
				{
					id++;
				}
				std::string rewardname;
				int subcount=0;
				LuaData::getProp(LuaData::QUEST,qid,LuaData::QUEST_SUB,(i+1),"name",rewardname); 
				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"type",type);
				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"count",subcount);
				if (type == 0)
				{
					continue;
				}
				count=subcount;
			}
			QuestReward p;
			p.rewardid=type;
			p.rewardcnt=count;
			questrewardlist.push_back(p);
		}	
	}	
	else if (line==Quest::line_Emigrated)
	{
		int datax = 0, datay = 0, dataz = 0;
		TaskData::getTaskExData(qid, datax, datay, dataz);
		QuestReward p1;
		p1.rewardid=Item_Money;
		p1.rewardcnt=SystemData::getLayoutValue("财神闯关金币奖励数量");
		questrewardlist.push_back(p1);

		QuestReward p2;
		p2.rewardid=Item_Exp;
		p2.rewardcnt=dataz;
		questrewardlist.push_back(p2);
	}
	else if (line==Quest::line_Exp||
		line==Quest::line_Honor||
		line==Quest::line_Money)
	{		
		int datax = 0, datay = 0, dataz = 0;
		TaskData::getTaskExData(qid, datax, datay, dataz);
		int rewardid=dataz;
		int base=0;
		int expbase=0;
		int type=0;
		int sid=0;
		LuaData::getProp(LuaData::QUESTEX,rewardid,"base",base);
		LuaData::getProp(LuaData::QUESTEX,rewardid,"exp",expbase);
		int round=0;
		switch (line)
		{
		case Quest::line_Exp:
			round=GameData::s_user->m_pMainRole->m_iExpCount;
			sid=Item_Exp;
			type=1;
			break;
		case Quest::line_Honor:
			round=GameData::s_user->m_pMainRole->m_iHonorCount;
			sid=Item_Honor;
			type=5;
			break;
		case Quest::line_Money:
			round=GameData::s_user->m_pMainRole->m_iMoneyCount;
			sid=Item_Money;
			type=4;
			break;
		default:
			break;
		}
		int count=base+base/10*round;
		if (count!=0)
		{
			if (sid==Item_Exp && expbase!=0)
			{
				count+=expbase+expbase/10*round;
			}

			QuestReward p;
			p.rewardid=sid;
			p.rewardcnt=count;
			questrewardlist.push_back(p);
		}		


		//???????????????
		int n=0;
		if (sid!=Item_Exp && expbase!=0)
		{
			n++;
			int expcount=expbase+expbase/10*round;

			QuestReward p;
			p.rewardid=Item_Exp;
			p.rewardcnt=expcount;
			questrewardlist.push_back(p);
		}


		int size=0;
		LuaData::getProp_size(LuaData::QUESTEX,rewardid,LuaData::QUEST_SUB,size);
		for (int i=0;i<size;i++)
		{
			int sub_type;
			int sub_count;
			int m=0;
			LuaData::getProp(LuaData::QUESTEX,rewardid,LuaData::QUEST_SUB,(i+1),LuaData::QUEST_SUB_1,LuaData::QUEST_SUB_2,sub_type,sub_count);
			if (sub_count==0)
			{
				m++;
				continue;
			}
			if (sub_type==0)
			{
				int id=0;
				switch (HeroData::getJob())
				{
				case UserData::CARRER_ZS:
					id=1;
					break;
				case UserData::CARRER_FS:
					id=3;
					break;
				case UserData::CARRER_DS:
					id=5;
					break;
				case UserData::CARRER_OMNI:
					id=1;
					break;
				default:
					break;
				}
				if (HeroData::getGender()==UserData::SEX_FEMALE)
				{
					id++;
				}
				std::string rewardname;
				int subcount=0;
				LuaData::getProp(LuaData::QUESTEX,rewardid,LuaData::QUEST_SUB,(i+1),"name",rewardname);
				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"type",sub_type);
				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"count",subcount);
				if (sub_type == 0)
				{
					continue;;
				}
				if (subcount!=0)
				{
					sub_count=subcount;
				}
			}

			QuestReward p;
			p.rewardid=sub_type;
			p.rewardcnt=sub_count;
			questrewardlist.push_back(p);
		}
	}
	return questrewardlist;
}

void NPCFunctionData::setNPCID( int npcid )
{
	m_iNPCStaticID=npcid;

}

int NPCFunctionData::getNPCID()
{
	return m_iNPCStaticID;
}

void NPCFunctionData::setReadmeAndSub( bool isReadme,bool isSub )
{
	m_bIsReadMe=isReadme;
	m_bIsSub=isSub;
}

bool NPCFunctionData::getReadme()
{
	return m_bIsReadMe;
}

bool NPCFunctionData::getIsSub()
{
	return m_bIsSub;

}

std::string NPCFunctionData::getNPCName()
{
	LuaData::getProp(LuaData::NPC,NPCFunctionData::getNPCID(),"name",m_sNPCname);
	if (m_sNPCname == "0")
	{
		CCLog("npc id = %d Error#51",NPCFunctionData::getNPCID());
		return "";
	}
	return m_sNPCname;
}

void NPCFunctionData::removechildfromparent( CCNode* pNode )
{
	CCArray *children = pNode->getChildren();
	if (children && children->count() > 0)
	{
		CCObject *obj = NULL;
		CCARRAY_FOREACH(children, obj)
		{
			CCNode *child = dynamic_cast<CCNode *>(obj);
			if (child)
			{
				CCHide *hi = CCHide::create();
				CCDelayTime *dl = CCDelayTime::create(0.5f);
				CCActionInstantRemoveFromParent *rmv = CCActionInstantRemoveFromParent::create();
				CCAction *action = CCSequence::create(hi, dl, rmv, NULL);
				child->runAction(action);
			}
		}
	}
}

void NPCFunctionData::updatedynamicData(int NPCid)
{
	Lua::instance()->push(NPCid);	
	Lua::instance()->call("get_npc_requestwiddata", 1, 0); 
}


void NPCFunctionData::sendupdatedynamicData( int wid,int type )
{
 	if (wid!=0 && type==0)
	{
		MsgSyncWorldDataRequest* pMsg = new MsgSyncWorldDataRequest;
		pMsg->wid = wid;
		pMsg->version = WorldData::getWorldDataVersion(wid);
		HandleMessage::sendMessage(pMsg);
	}
	else if (wid!=0 && type==1)
	{
		MsgSyncWorldDataStringRequest* pMsg = new MsgSyncWorldDataStringRequest;
		pMsg->wid = wid;
		pMsg->version = WorldData::getWorldDataSVersion(wid);
		HandleMessage::sendMessage(pMsg);
	}

	/*int size = 0;
	Lua::instance()->push(NPCid);	
	if(	Lua::instance()->call("get_npc_requestwiddata", 1, 0) &&
		Lua::instance()->pop(size)) 
	{ 
		for (int i = 1;i<=size;i++)
		{
			int wid = 0;
			int type = 0;
			Lua::instance()->push(NPCid);
			Lua::instance()->push(i);	
			if(	Lua::instance()->call("get_npc_needwid", 2, 2) &&
				Lua::instance()->pop(type)&&
				Lua::instance()->pop(wid)) 
			{
				
			}
		}
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_npc_widcount int"); 
	}*/
}

void NPCFunctionData::sendupdateinstanceData()
{
	MsgGetInstanceCntRequest* pMsg = new MsgGetInstanceCntRequest;
	//pMsg->
	HandleMessage::sendMessage(pMsg);
}

void NPCFunctionData::doFuncScript( int funcid ,int datax,int datay,int dataz,std::string datas)
{
	Lua::instance()->push(funcid);
	Lua::instance()->push(datax);
	Lua::instance()->push(datay);
	Lua::instance()->push(dataz);
	Lua::instance()->push_utf8(datas);
	Lua::instance()->call("FuncHandler",5,1);
}

bool NPCFunctionData::clickNPCclosePanel( int npcid ,int datax)
{
	bool flag = false;
	Lua::instance()->push(npcid);
	Lua::instance()->push(datax);
	if(Lua::instance()->call("get_npc_panelcolse",2,1) && Lua::instance()->pop(flag))  
	{
		return flag; 
	}

	return true;
}

void NPCFunctionData::repairItem()
{
	int reqsid = SystemData::getLayoutValue("战神油");
	int cnt = GameData::s_user->getUserItemData()->getItemCntBySid(reqsid);
	if (cnt>0)
	{
		BagOperator::RepairAllFromServer(ItemRepair_Item);
	}
	else
	{
		CPEventHelper::uiNotify("","",Error::NotEnoughOil);
		int price = 0;
		LuaData::getProp(LuaData::ITEM,reqsid,"shopprice",price);
		if (price==0)
		{
			price =1;
		}
		Game::getGameUI()->showNumberKeyBoard(1,5,price,reqsid); 
	}
}

void NPCFunctionData::findreapairNPC()
{
	int npcid = GameData::s_user->m_pGhostManager->gotoFindNPC("铁匠");
	Game::getGameUI()->showFlyShoes(npcid);
}

//-----------------------------------------------------------------------------------------------------------//
const int ItemSize = 74;

TaskRewardPanel::TaskRewardPanel():
	m_pTableView(NULL),
	mrow(0),
	mline(0),
	m_iTipsdir(0)
{

}

TaskRewardPanel::~TaskRewardPanel()
{

}

bool TaskRewardPanel::init( int qid,int row,int line)
{
	m_rewardlist=NPCFunctionData::getQuestReward(qid);

	mrow=row;
	mline=line; 

	m_pTableView=CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutValue("taskcontent_reward_size.w")*mline,SystemData::getLayoutValue("taskcontent_reward_size.h")*mrow),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(CCPointZero);
	m_pTableView->reloadData();  
	addChild(m_pTableView);	 

	if (mrow*mline>=m_rewardlist.size())
	{
		m_pTableView->setTouchEnabled(false);
	}

	return true;
}

TaskRewardPanel* TaskRewardPanel::create( int qid ,int row,int line)
{
	TaskRewardPanel* pPanel = new TaskRewardPanel();
	if(pPanel && pPanel->init(qid,row,line))
	{
		pPanel->autorelease();
		return pPanel;
	}

	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

cocos2d::CCSize TaskRewardPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("taskcontent_reward_size");
}

cocos2d::extension::CCTableViewCell* TaskRewardPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* p=CCLayer::create();
		p->setPosition(CCPointZero);
		p->setAnchorPoint(CCPointZero);
		cell->addChild(p);

		int n=0;
		std::vector<QuestReward>::iterator it=m_rewardlist.begin();
		for (it;it!=m_rewardlist.end();it++)
		{
			if (n==idx*mline)
			{
				for (int i=0;i<mline;i++)
				{
					QuestReward preward=*it;
					int sid=preward.rewardid;
					int count=preward.rewardcnt;
					CCSprite* pborder=SystemData::getSpriteByPlist("taskcontent_reward_border");
					pborder->setPosition(ccp(SystemData::getLayoutPoint("taskcontent_reward_item").x+190*i,SystemData::getLayoutPoint("taskcontent_reward_item").y));
					p->addChild(pborder);

					CCMenuEx* pMenu=CCMenuEx::create();
					pMenu->setPosition(CCPointZero);
					pMenu->setAnchorPoint(CCPointZero);
					p->addChild(pMenu);

					CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(CommonFunction::createNewItem(sid),false);
					pItem->setPosition(pborder->getPosition());
					pItem->setTarget(this,menu_selector(TaskRewardPanel::itemcallback));
					pMenu->addChild(pItem);


					CCString* pStr=CCString::createWithFormat("x %d",count);
					CCLabelTTF* pcnt=CCLabelTTF::create(pStr->getCString(),"微软雅黑",16);
					pcnt->setAnchorPoint(CCPointZero);
					pcnt->setColor(ccGREEN);
					pcnt->setPosition(ccp(SystemData::getLayoutPoint("taskcontent_reward_text").x+190*i,SystemData::getLayoutPoint("taskcontent_reward_text").y));
					p->addChild(pcnt);
					
					it++;
					if (it==m_rewardlist.end())
					{
						break;
					}
				}				
				break;
			}
			n++;
		}
	}
	return cell;
}

unsigned int TaskRewardPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return m_rewardlist.size();
}

void TaskRewardPanel::itemcallback( CCObject* pSender )
{
	CCNode* pNode=(CCNode* )pSender;
	if (pNode)
	{
		UserItem* p=(UserItem*)pNode->getUserData();
		CCPoint anpos=CCPointZero;
		CCPoint pos=ccp(300,10);
		CCPoint itempos=pNode->getPosition();
		itempos=convertToWorldSpace(itempos);
		CCPoint pos1=ccp(itempos.x-ItemSize/2,itempos.y+(ItemSize/2));
		CCPoint pos2=ccp(itempos.x+ItemSize/2,itempos.y+(ItemSize/2));
		CCPoint pos3=ccp(itempos.x+ItemSize/2,itempos.y+(-ItemSize/2));
		CCPoint pos4=ccp(itempos.x-ItemSize/2,itempos.y+(-ItemSize/2));
		// ?ж?tips?????λ??
		if (m_iTipsdir==dir_left)
		{
			pos=ccp(pos4.x-SystemData::getLayoutValue("Tips_size_e.w"),pos4.y+20);
		}
		else if (m_iTipsdir==dir_right)
		{
			pos=ccp(pos3.x,pos3.y-55);
			//anpos=ccp(1,0);
		}
		if (CCDirector::sharedDirector()->getWinSize().width-pos.x<SystemData::getLayoutValue("Tips_size_e.w"))
		{
			pos=ccp(pos4.x-SystemData::getLayoutValue("Tips_size_e.w"),pos.y);
		}
		else if (pos.x<SystemData::getLayoutValue("Tips_size_e.w"))
		{
			pos=ccp(pos3.x,pos.y);
		}
		if (p->category==ItemCate_Equip)
		{
			pos=ccp(pos.x,pos.y-55);
		}
		Game::getGameUI()->showTipsPanel(p,TAG_Tips,pos,anpos);
	}
}

void TaskRewardPanel::settipsdir( int tag )
{
	m_iTipsdir=tag;
}

//-----------------------------------------------------------------------------------------------------------------------------//

FlyShoesMenu::FlyShoesMenu():
	m_iData(0),
	m_iType(0)
{

}

FlyShoesMenu::~FlyShoesMenu()
{

}

FlyShoesMenu* FlyShoesMenu::create(int data )
{
	FlyShoesMenu* pPanel = new FlyShoesMenu;
	if (pPanel && pPanel->init(data))
	{
		pPanel->autorelease();
		return pPanel;
	}
	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

bool FlyShoesMenu::init(int data )
{
	m_iData = data;

	CCMenu* pMenu = CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItemImage* mTeleportBtn = LayoutData::getMenuItemImg(CPModuleName::TASK, "teleport");
	mTeleportBtn->setTarget(this, menu_selector(FlyShoesMenu::flyCB));
	//mTeleportBtn->setVisible(false);
	pMenu->addChild(mTeleportBtn);
		
	this->scheduleUpdate();
	return true;
}

void FlyShoesMenu::flyCB( CCObject* pSender )
{
	NPCFunctionData::useShoes(m_iData,Scene::seNpc);
	//hide();
}

void FlyShoesMenu::hide()
{
	this->removeFromParent();
}

void FlyShoesMenu::update( float dt )
{
	if(!GameData::getMyRole()->m_bAutoMove)
	{
		hide();
	}
}
