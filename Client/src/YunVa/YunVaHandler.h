#ifndef	___YUNVA_HANDLER___
#define ___YUNVA_HANDLER___

#include "CCObject.h"
#include "CCArray.h"
#include <YunVaSDK/yvListern.h>
#include <map>

using namespace YVSDK;

class YunVaRecordListener;

class YunVaHandler : public cocos2d::CCObject
, public YVListern::YVLoginListern
, public YVListern::YVRecordVoiceListern
, public YVListern::YVStopRecordListern
, public YVListern::YVUpLoadFileListern
, public YVListern::YVFinishSpeechListern
{
	YunVaRecordListener * m_listener;
public:
	YunVaHandler();
	virtual ~YunVaHandler();

	void setRecordListener(YunVaRecordListener* listener) { m_listener = listener; };

	void init(unsigned long appId);

	void login(std::string& nick, std::string &uid);

	int startRecord();
	void stopRecord();

	static YunVaHandler* sharedHandler();
private:
	void update(float dt);
	void onLoginListern(CPLoginResponce* responce);
	void onRecordVoiceListern(RecordVoiceNotify*);
	void onStopRecordListern(RecordStopNotify*);
	void onUpLoadFileListern(UpLoadFileRespond*);
	void onFinishSpeechListern(SpeechStopRespond*);

	std::map<int, unsigned int> m_recordTimeMap;
};

#endif
