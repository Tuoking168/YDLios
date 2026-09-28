//////////////////////////////////////////////////////////////////////////
// HttpDownloadRunnable.h
// 
// W.Y-J
// 2012.5.8
//////////////////////////////////////////////////////////////////////////

#ifndef __HTTPDOWNLOADRUNNABLE_H__
#define __HTTPDOWNLOADRUNNABLE_H__

#include "Threading.h"
#include "HttpDownload.h"


class IHttpDownloadRunnable : public WOE::Runnable
{
public:
	virtual ~IHttpDownloadRunnable(){}

protected:
	virtual int handleMessage() = 0;
};

////////////////HttpDownloadRunnable//////////////////////////////////////
struct HttpDownloadRunnableData;
class HttpDownloadRunnable : public IHttpDownloadRunnable
{
public:
	virtual ~HttpDownloadRunnable();

	// send a download task by MsgDownload
	virtual bool Send(IMsg *packet);
	virtual void stop();
	virtual void exit();

	// called by WOE::Thread automatically
	virtual void run();

	static HttpDownloadRunnable &instance();
	void initThread();
	void setURLHead(const std::string &urlHead);
	void setLocalPath(const std::string &localPath);
	void setLocalPath(const std::string &localPath, bool isRoot);
	void download(const std::string &fileName);

protected:
	HttpDownloadRunnable();

	bool getNextMsg(IMsg *&msg);
	RESULT_TYPE download(const std::string &url, const std::string &local_file);
	void downloadResult(const std::string &key);
	void getFullPath(const std::string &fileName, std::string &url, std::string &localPath);
	virtual int handleMessage();

private:
	bool initialize();
	bool unInitialize();
	static void onDownloadProgress(const std::string &file, double dltotal, double dlnow);

protected:
	HttpDownloadRunnableData *mData;
};

#endif // __HTTPDOWNLOADRUNNABLE_H__
