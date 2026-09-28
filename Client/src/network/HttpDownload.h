#ifndef __HTTP_DOWNLOAD_H__
#define __HTTP_DOWNLOAD_H__

#include "curl.h"
#include <string>

typedef void (*progress_callback)(const std::string& file, double dltotal, double dlnow);

// download error
typedef unsigned short RESULT_TYPE;

namespace HD
{

enum
{
	ERR_SUCCESS					=	0,
	ERR_FAILED					=	1,
	ERR_SERVER_NA				=	2,
	ERR_NO_SUCH_FILE			=	3,

	ERR_MAX,
};

};

class HttpDownload
{
public:
	HttpDownload();
	~HttpDownload();

public:
	static HttpDownload* instance();

	/**
	* download a file from a specific url
	* @param url : remote file 
	* @param local_file : download remote file and save to the local_file
	* @return return 0 if successful and other value means a different type of error
	*/
	RESULT_TYPE download(const std::string& url, const std::string& local_file);

	/**
	* stop a current download
	*/
	void stop();

	/**
	* set a callback function so other modules can trace the download process if necessary
	*/
	void setProgressCallback(progress_callback _function);


	short getErrorState();
private:
	bool init();

	static size_t process_data(void* buffer, size_t size, size_t nmemb, void* user_p);

	static int progress_data(void* data, double dltotal, double dlnow);

private:
	CURL*	m_curlHandle;
	static progress_callback	m_pCallbackFunction;
};

#define sDownloader HttpDownload::instance()


#endif//__HTTP_DOWNLOAD_H__