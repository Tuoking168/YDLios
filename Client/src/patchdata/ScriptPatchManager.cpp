#include "ScriptPatchManager.h"
#include "network/HandleMessage.h"
#include "MsgWorld.h"
#include "userdata/UserData.h"
#include "utils/StringUtils.h"
#include "res/Path.h"
#include "script/LuaWrapper.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"
#include <fstream>
#ifdef WIN32
#include <direct.h>
#include <FileApi.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#endif

#define MAX_UPDATE_DURATION    (10 * 60 * 1000)

int ScriptPatchManager::GetMaxUpdateDuration()
{
	return MAX_UPDATE_DURATION;
}

int ScriptPatchManager::GetLastFetchTime(int nScriptId)
{
	std::string key("LastScriptPatch_");
	key += StringUtils::toString(nScriptId);
	return UserData::getIntData(key);
}

void ScriptPatchManager::UpdateLastFetchTime(int nScriptId)
{
	std::string key("LastScriptPatch_");
	key += StringUtils::toString(nScriptId);
	UserData::setIntData(key, time(NULL));
	UserData::saveData();
}

bool ScriptPatchManager::ScriptNeedUpdate(int nScriptId)
{
	return true;
	// int now = time(NULL);
	// return now - GetLastFetchTime(nScriptId) > MAX_UPDATE_DURATION;
}

ScriptPatchManager::ScriptPatchManager()
{

}

ScriptPatchManager::~ScriptPatchManager()
{

}

ScriptPatchManager* ScriptPatchManager::instance()
{
	static ScriptPatchManager spm;
	return &spm;
}

void ScriptPatchManager::UpdateScript(int nScriptId)
{
	CCLog("Sending update script request, script id = %d", nScriptId);
	MsgScriptDataRequest* req = new MsgScriptDataRequest();
	if (req)
	{
		req->ScriptID = nScriptId;
		req->ClientScriptVer = GetScriptVer(nScriptId);
		CCLog("Version of script %d is %d", req->ScriptID, req->ClientScriptVer);
		HandleMessage::sendMessage(req);

		// Clear the cache memory made in previous request
		m_theVers.clear();
		m_theData.clear();
	}
}

#define SCRIPT_KEY(id) std::string("LuaScript") + StringUtils::toString(nScriptId)

int ScriptPatchManager::GetScriptVer(int nScriptId)
{
	Lua::instance()->push(nScriptId);
	Lua::instance()->call("tActivityCfgVer", "GetActivityCfgVer", 1, 1);
	int nVer = 1;
	Lua::instance()->pop(nVer);
	return nVer;
}

void ScriptPatchManager::SetScriptVer(int nScriptId, int ver)
{
}

void ScriptPatchManager::UpdateScriptVer(int nScriptId)
{
	ScriptId2Ver::iterator pos = m_theVers.find(nScriptId);
	if (pos != m_theVers.end())
	{
		SetScriptVer(nScriptId, pos->second);
		// Remove it so that it could work next iteration if necessary
		m_theVers.erase(pos);
	}
}

std::string ScriptPatchManager::ScriptPath(int nScriptId)
{
	return std::string("dscript/") + StringUtils::toString(nScriptId) + std::string(".lua");
}

void ScriptPatchManager::HandleScriptDataResponse(MsgScriptDataResponse* pMsg)
{
	CCLog("ScriptPatchManager::HandleScriptDataResponse");
	int nScriptId  = pMsg->ScriptID;
	int nServerVer = pMsg->ServerScriptVer;
	CCLog("nServerVer = %d, nScriptId = %d", nServerVer, nScriptId);
	// Save the server version and only update the version 
	// after getting the script successfully
	int nClientVer  = GetScriptVer(nScriptId);
	int nPatchCount = nServerVer - nClientVer;
	if (nServerVer != nClientVer)
	{
		m_theVers.insert(std::make_pair(nScriptId, nServerVer));
	}
	else
	{
		// Tell the listeners the script is done
		BroadcastScriptReady(nScriptId);
	}
}

void ScriptPatchManager::HandleScriptPatchNotify(MsgScriptPatchNotify* pMsg)
{
	CCLog("ScriptPatchManager::HandleScriptPatchNotify");
	int nScriptId = pMsg->ScriptID;
	// If there is no update for this script, ignore the notification
	if (m_theVers.find(nScriptId) == m_theVers.end())
	{
		return;
	}
	int nTotal    = pMsg->PartCount;
	int nIndex    = pMsg->PartIndex;
	const std::string& data(pMsg->PatchContent);
	CCLog("nScriptId = %d, nTotal = %d, nIndex = %d, nSize = %d",
		nScriptId, nTotal, nIndex, data.size());
	if (nIndex < nTotal)
	{
		Accumulate(nScriptId, data);
	}
	else
	{
		if (SaveScript(nScriptId, data))
		{
			UpdateScriptVer(nScriptId);
		}
		// Tell the listeners the script is done
		BroadcastScriptReady(nScriptId);
	}
}

void ScriptPatchManager::BroadcastScriptReady(int nScriptId)
{
	CCLog("Broadcasting script ready, script id = %d", nScriptId);
	//
	CPEventHelper::setEventStringData(CPEventName::MSG_DATA_READY, CPEventData::SOURCE, "ScriptPatchManager");
	CPEventHelper::setEventStringData(CPEventName::MSG_DATA_READY, CPEventData::TARGET, "");
	CPEventHelper::setEventIntData(CPEventName::MSG_DATA_READY, CPEventData::VALUE_1, nScriptId);
	CPEvtDispatcher.dispatcherEvent(CPEventName::MSG_DATA_READY);
}

void ScriptPatchManager::Accumulate(int nScriptId, const std::string& data)
{
	ScriptId2Data::iterator pos = m_theData.find(nScriptId);
	if (pos == m_theData.end())
	{
		m_theData.insert(std::make_pair(nScriptId, data));
	}
	else
	{
		pos->second += data;
	}
}

bool ScriptPatchManager::SaveScript(int nScriptId, const std::string& data)
{
	bool result = false;
	// Save to file with name nScriptId/nPatchId.lua
	std::string name = ScriptPath(nScriptId);
	CCLog("Script will be saved to:%s", name.c_str());				   
	ScriptId2Data::iterator pos = m_theData.find(nScriptId);
	if (pos == m_theData.end())
	{
		result = SaveScript(name, data);
	}
	else
	{
		result = SaveScript(name, pos->second + data);
		m_theData.erase(pos);
	}
	return result;
}

class DirStore
{
public:
	DirStore()
	{
		char cwd[1024] = "\0";
		getcwd(cwd, 1024);
		m_strCurDir = std::string(cwd);
		CCLog("Current Directory:%s", cwd);
	}
	~DirStore()
	{
		chdir(m_strCurDir.c_str());
	}
private:
	std::string m_strCurDir;
};

bool ScriptPatchManager::MakeDir(const std::string& path)
{
	DirStore dummy;
	int pos = 1;
	while (true)
	{
		pos = path.find('/', pos);
		if (pos == std::string::npos)
		{
			break;
		}
		std::string sec(path.substr(0, pos));
		if (chdir(sec.c_str()) == -1)
		{
	#ifdef WIN32
			if (mkdir(sec.c_str()))
	#else
			if (mkdir(sec.c_str(), S_IRWXU))
	#endif
			{
				return false;
			}
		}
		++ pos;
	}
	return true;
}

bool ScriptPatchManager::SaveScript(const std::string& name, const std::string& data)
{
	std::string path;
	PathW::convert(path);
	path += name;
	// Create direcory tree as needed
	if (MakeDir(path))
	{
		std::ofstream script(path.c_str(), std::ios::binary | std::ios::trunc);
		if (script.is_open())
		{
			script.write(data.c_str(), data.length());
			script.close();
			return true;
		}
	}
	return false;
}

// nPatchId is the last pathed has been run
void ScriptPatchManager::EnableScript(int nScriptId)
{
	std::string path;
	PathW::convert(path);
	path += ScriptPath(nScriptId);
	EnableScript(path);
}

void ScriptPatchManager::EnableAllScripts()
{
	std::string path;
	PathW::convert(path);
	path += "dscript/";
#ifdef WIN32
	WIN32_FIND_DATAA theFindData;
	HANDLE hFindHandle = FindFirstFileA(path.c_str(), &theFindData);
	if (hFindHandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (theFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				continue;
			}
			std::string name = path + theFindData.cFileName;
			EnableScript(name);
		} while (FindNextFileA(hFindHandle, &theFindData) != 0);
		FindClose(hFindHandle);
	}

#else
	DIR* dir = opendir(path.c_str());
	if (dir)
	{
		while (true)
		{
			dirent* ent = readdir(dir);
			if (ent == 0)
			{
				break;
			}
			if (ent->d_type == DT_DIR)
			{
				continue;
			}
			std::string name = path + ent->d_name;
			EnableScript(name);
		}
	}
	closedir(dir);
#endif
}

void ScriptPatchManager::EnableScript(const std::string& script)
{
	CCLog("Enabling script %s", script.c_str());
	if (!script.empty())
	{
		Lua::instance()->dofile(script.c_str());
	}
}