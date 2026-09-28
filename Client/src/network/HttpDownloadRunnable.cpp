//////////////////////////////////////////////////////////////////////////
// HttpDownloadRunnable.cpp
// 
// W.Y-J
// 2012.5.8
//////////////////////////////////////////////////////////////////////////

#ifndef WIN32
#include "common/stdafx.h"
#endif
#include "HttpDownloadRunnable.h"
#include "LockedQueue.h"
#include "Event.h"
#include "CommonType.h"
#include "MsgDownload.h"
#include "res/Path.h"
#include "CCCommon.h"
#include "network/HandleMessage.h"
#include "network/MsgListener.h"

using namespace cocos2d;

/////////////////HttpDownloadRunnable/////////////////////////////////////
struct HttpDownloadRunnableData
{
	HttpDownloadRunnableData()
		: stopEvent(true)
	{}

	volatile bool	stopEvent;

	WOE::LockedQueue<IMsg *> _queue;
	WOE::Thread _thread;
	HttpDownload httpDownload;

	std::string urlHead;
	std::string localPathRoot;
	std::string localPathHead;
	std::string runname;
};
HttpDownloadRunnable::HttpDownloadRunnable()
{
	this->mData = new HttpDownloadRunnableData();
	mData->runname = "HttpDownloadRunnable";
}

HttpDownloadRunnable::~HttpDownloadRunnable()
{
	delete this->mData;
}

void HttpDownloadRunnable::run()
{
	CCLog("%s start!!!!!", mData->runname.c_str());
	mData->stopEvent = false;

	if (!initialize())
	{
		mData->stopEvent = true;
		return;
	}

	while (!mData->stopEvent)
	{
		handleMessage();
		
#ifdef WIN32
		Sleep(3);
#else
		usleep(3);
#endif
	}

	if (!unInitialize())
	{
		CCLog("UnInitialize HttpDownloadRunnable Failed!");
	}
	CCLog("%s stopped!!!!!", mData->runname.c_str());
}

void HttpDownloadRunnable::stop()
{
	mData->stopEvent = true;
}

void HttpDownloadRunnable::exit()
{
	stop();
	mData->_thread.stop();
}

bool HttpDownloadRunnable::Send(IMsg *packet)
{
	if (!packet)
		return false;

	mData->_queue.add_back(packet);
	return true;	
}

HttpDownloadRunnable & HttpDownloadRunnable::instance()
{
	static HttpDownloadRunnable ret;
	return ret;
}

void HttpDownloadRunnable::initThread()
{
	if(mData->stopEvent)
	{
		mData->_thread.start(this);
		mData->httpDownload.setProgressCallback(onDownloadProgress);
	}
}

void HttpDownloadRunnable::setURLHead( const std::string &urlHead )
{
	mData->urlHead = urlHead;
}

void HttpDownloadRunnable::setLocalPath( const std::string &localPath )
{
	setLocalPath(localPath, false);
}

void HttpDownloadRunnable::setLocalPath( const std::string &localPath, bool isRoot )
{
	if (isRoot)
	{
		mData->localPathRoot = localPath;
		mData->localPathHead.clear();
	}
	else
	{
		mData->localPathRoot.clear();
		PathW::convert(mData->localPathRoot);
		mData->localPathHead = localPath;
	}
}

bool HttpDownloadRunnable::getNextMsg( IMsg *&msg )
{
	return mData->_queue.next(msg);
}

void HttpDownloadRunnable::download( const std::string &fileName )
{
	if (!fileName.empty())
	{
		MsgDownload *msg = new MsgDownload;
		msg->key = fileName;
		Send(msg);
	}	
}

RESULT_TYPE HttpDownloadRunnable::download( const std::string &url, const std::string &local_file )
{
	return mData->httpDownload.download(url, local_file);
}

void HttpDownloadRunnable::downloadResult( const std::string &key )
{
	MsgDownload *msgDl = new MsgDownload;
	msgDl->key = key;

	DownloadEvent *evt = new DownloadEvent;
	evt->type = Event::DOWNLOAD;
	evt->msg = msgDl;
	HandleMessage::s_msglistener->m_events.add_back(evt);
}

void HttpDownloadRunnable::getFullPath( const std::string &fileName, std::string &url, std::string &localPath )
{
	url = mData->urlHead + mData->localPathHead + fileName;
	localPath = mData->localPathRoot + mData->localPathHead + fileName;
}

int HttpDownloadRunnable::handleMessage()
{
	IMsg *msg = NULL;
	while (getNextMsg(msg) && msg)
	{
		MsgDownload *msgDl = dynamic_cast<MsgDownload *>(msg);
		if (msgDl)
		{
			std::string url, localPath;
			getFullPath(msgDl->key, url, localPath);
			if (HD::ERR_SUCCESS != download(url, localPath))
			{
				CCLog(">>>Error: failed to download file: %s", msgDl->key.c_str());
				delete msg;

				downloadResult("");
				continue;
			}

			CCLog(">>>Info: download file done: %s", localPath.c_str());
			downloadResult(msgDl->key);
		}
		delete msg;
	}

	return 0;
}

bool HttpDownloadRunnable::initialize()
{
	return true;
}

bool HttpDownloadRunnable::unInitialize()
{
	return true;
}

void HttpDownloadRunnable::onDownloadProgress( const std::string &file, double dltotal, double dlnow )
{
	dltotal = (dltotal > 1 ? dltotal : 1);
	MsgDownloadProgress *msgDl = new MsgDownloadProgress;
	msgDl->key = file;
	msgDl->percent = dlnow/dltotal;

	DownloadEvent *evt = new DownloadEvent;
	evt->type = Event::DOWNLOAD;
	evt->msg = msgDl;
	HandleMessage::s_msglistener->m_events.add_back(evt);
}
