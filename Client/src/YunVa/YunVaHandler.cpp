#include "YunVa/YunVaHandler.h"
#include <YunVaSDK/YVTool.h>
#include "CCDictionary.h"
#include "CCFileUtils.h"
#include "CCDirector.h"
#include "CCScheduler.h"
#include "YunVaRecordListener.h"
#include <strstream>

using namespace YVSDK;
using namespace cocos2d;

YunVaHandler::YunVaHandler(): m_listener(NULL)
{
}

YunVaHandler::~YunVaHandler()
{
	/*auto it = m_recordTimeMap.begin();
	while (it != m_recordTimeMap.end())
	{
		RecordStopNotify* s = it->second;
		s->release();
		++it;
	}*/
}

void YunVaHandler::update(float dt)
{
	YVTool::getInstance()->dispatchMsg(dt);
}

void YunVaHandler::init(unsigned long appId)
{
	YVTool* pYVTool = YVTool::getInstance();
	pYVTool->addLoginListern(this);
	pYVTool->addRecordVoiceListern(this);
	pYVTool->addStopRecordListern(this);
	pYVTool->addUpLoadFileListern(this);
	pYVTool->addFinishSpeechListern(this);
	pYVTool->initSDK(appId, CCFileUtils::sharedFileUtils()->getWritablePath(), false, false);
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, -1, false);
}

void YunVaHandler::login(std::string& nick, std::string &uid)
{
	YVTool::getInstance()->cpLogin(nick, uid);
}

int YunVaHandler::startRecord()
{
	static int recordId = 100;
	recordId++;

	std::strstream ss;
	ss << recordId;
	std::string ext = ss.str();

	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "test.amr";

	YVTool::getInstance()->startRecord(path, 1, ext);

	return recordId;
}

void YunVaHandler::stopRecord()
{
	YVTool::getInstance()->stopRecord();
}

YunVaHandler * YunVaHandler::sharedHandler()
{
	static YunVaHandler* m_instance = NULL;
	if (m_instance == NULL)
		m_instance = new YunVaHandler();
	return m_instance;
}

void YunVaHandler::onLoginListern(CPLoginResponce * responce)
{
	if (responce->result == 0)
	{
		
	}
}

void YunVaHandler::onRecordVoiceListern(RecordVoiceNotify *)
{
}

void YunVaHandler::onStopRecordListern(RecordStopNotify * notify)
{
	int id = 0;
	std::strstream ss;
	ss << notify->ext;
	ss >> id;

	m_recordTimeMap.insert(std::make_pair(id, notify->time));
}

void YunVaHandler::onUpLoadFileListern(UpLoadFileRespond * respond)
{
	if (respond->result == 0)
	{
		int id = 0;
		std::strstream ss;
		ss << respond->fileid;
		ss >> id;
		std::map<int, unsigned int>::iterator it = m_recordTimeMap.find(id);
		uint32 time = 0;
		if (it != m_recordTimeMap.end()) {
			time = it->second;
			m_recordTimeMap.erase(it);
		}

		if (m_listener)
		{
			std::strstream ss;
			ss << time << std::ends;
			std::string timeStr = ss.str();
			m_listener->onRecordFinish(0, respond->fileurl, timeStr);
		}
	}
}

void YunVaHandler::onFinishSpeechListern(SpeechStopRespond * respond)
{
	if (respond->err_id == 0)
	{
		
	}
}
