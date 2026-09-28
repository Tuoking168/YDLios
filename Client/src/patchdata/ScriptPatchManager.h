#pragma once

#include <string>
#include <map>

class MsgScriptDataResponse;
class MsgScriptPatchNotify;

class ScriptPatchManager
{
private:
	ScriptPatchManager(void);
public:
	~ScriptPatchManager(void);
	static ScriptPatchManager* instance();
	
	int GetMaxUpdateDuration();
	int GetLastFetchTime(int nScriptId);
	void UpdateLastFetchTime(int nScriptId);
	bool ScriptNeedUpdate(int nScriptId);
	//
	void UpdateScript(int nScriptId);
	int  GetScriptVer(int nScriptId);
	void SetScriptVer(int nScriptId, int ver);
	void UpdateScriptVer(int nScriptId);

	std::string ScriptPath(int nScriptId);

	void HandleScriptDataResponse(MsgScriptDataResponse* pMsg);
	void HandleScriptPatchNotify(MsgScriptPatchNotify* pMsg);

	void EnableAllScripts();
	void EnableScript(int nScriptId);
	void EnableScript(const std::string& script);
private:
	void Accumulate(int nScriptId, const std::string& data);
	bool SaveScript(int nScriptId, const std::string& data);
	bool SaveScript(const std::string& name, const std::string& data);
	void BroadcastScriptReady(int nScriptId);
private:
	bool MakeDir(const std::string& path);
	typedef std::map<int, std::string> ScriptId2Data;
	ScriptId2Data m_theData;
	typedef std::map<int, int> ScriptId2Ver;
	ScriptId2Ver  m_theVers;
};

