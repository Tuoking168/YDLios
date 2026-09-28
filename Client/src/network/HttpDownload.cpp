#include "HttpDownload.h"
#include <errno.h>
#include "cocos2d.h"
#ifdef WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace HD;

#pragma comment(lib, "libcurl_imp.lib")

#define TYR_TIMES 10

#include <sys/stat.h>

static unsigned long get_file_size(const char *path)
{
	unsigned long filesize = 0;	
	struct stat statbuff;
	if(stat(path, &statbuff) < 0){
		return filesize;
	}else{
		filesize = statbuff.st_size;
	}
	return filesize;
}

//////////////////////////////////////////////////////////////////////////
progress_callback	HttpDownload::m_pCallbackFunction = NULL;

HttpDownload* HttpDownload::instance()
{
	static HttpDownload _instance;
	return &_instance;
}

HttpDownload::HttpDownload()
:m_curlHandle(NULL)
{
	curl_global_init(CURL_GLOBAL_ALL);
}

HttpDownload::~HttpDownload()
{
	curl_global_cleanup();
}

bool HttpDownload::init()
{
	m_curlHandle = curl_easy_init();
	if (NULL == m_curlHandle)
	{
		//cerr << "get a easy handle failed." << endl;
		curl_global_cleanup();
		return false;
	}
	return true;
}

void HttpDownload::stop()
{
	if(m_curlHandle)
	{
		curl_easy_cleanup(m_curlHandle);
	}
}

FILE* createFile(const char *file)
{
	if (!file)
		return NULL;
	
	char buf[260];
	const char *pStart = file+1;
	const char *pEnd = NULL;

	do 
	{
		pEnd = strchr(pStart, '/');
		if (pEnd)
		{
			memcpy(buf, file, pEnd - file);
			buf[pEnd - file] = 0;
			pStart = ++pEnd;

			if (chdir(buf) == -1)
#ifdef WIN32
				if (mkdir(buf))
#else
				if (mkdir(buf, S_IRWXU))
#endif
				{
					cocos2d::CCLog("failed to mkdir: %d", errno);
					return NULL;
				}
		}
		else
		{
			FILE *fp;
			if ((fp = fopen(file, "ab+")) == 0)
				return NULL;
			return fp;
		}
	} while (1);

	return NULL;
}

RESULT_TYPE HttpDownload::download( const std::string& url, const std::string& local_file )
{
	short rtv = ERR_SUCCESS;

	if(url.empty() || local_file.empty())
	{
		return ERR_FAILED;
	}

	if(!init())
	{
		return ERR_FAILED;
	}

	// start to download ... 
	bool successDownload = false;
	CURLcode res;
	FILE *fp = NULL;
	std::string file_temp = local_file + ".temp";

	int trycnt = 0;
	// if download failed, keep on downloading
	do 
	{
		++trycnt;

		fp = createFile(file_temp.c_str());
		cocos2d::CCLog(">>>>>>>>>>>>>>>>>>fp= %s", file_temp.c_str());
		if (NULL != fp)
		{
			const unsigned long size = get_file_size(file_temp.c_str());
			char range[1024];
			sprintf(range, "%d-", size);

			curl_easy_setopt(m_curlHandle, CURLOPT_URL, url.c_str());
			curl_easy_setopt(m_curlHandle, CURLOPT_CONNECTTIMEOUT, 20L);
			curl_easy_setopt(m_curlHandle, CURLOPT_WRITEFUNCTION, &process_data);
			curl_easy_setopt(m_curlHandle, CURLOPT_WRITEDATA, fp);
			curl_easy_setopt(m_curlHandle, CURLOPT_RANGE, range);

			curl_easy_setopt(m_curlHandle, CURLOPT_NOPROGRESS, 0L);   
			curl_easy_setopt(m_curlHandle, CURLOPT_PROGRESSFUNCTION, &progress_data);   
			curl_easy_setopt(m_curlHandle, CURLOPT_PROGRESSDATA, url.c_str());

			res = curl_easy_perform(m_curlHandle);
			if(CURLE_OK == res)
			{
				long nRetcode(0);
				curl_easy_getinfo(m_curlHandle, CURLINFO_RESPONSE_CODE, &nRetcode);

				if(404 == nRetcode)
				{
					cocos2d::CCLog(">failed to download file, no such file");
					rtv = ERR_NO_SUCH_FILE;
					break;
				}
				else if(403 == nRetcode)
				{
					cocos2d::CCLog(">failed to download file, bad request");
					rtv = ERR_NO_SUCH_FILE;
					break;
				}
				else // success download
				{
					successDownload = true;
					fclose(fp);

					int err = remove(local_file.c_str());
					if(err != ERR_SUCCESS)
					{
						cocos2d::CCLog(">>>Error: remove file failed! file: %s", local_file.c_str());
					}

					err = rename(file_temp.c_str(), local_file.c_str());
					if(err != ERR_SUCCESS)
					{
						cocos2d::CCLog(">>>Error: rename file failed! fileOld: %s, fileNew: %s", file_temp.c_str(), local_file.c_str());
					}
				}
			}
			else
			{
				fclose(fp);

				cocos2d::CCLog(">failed to download(%d): %s -> %s", res, url.c_str(), local_file.c_str());

				if(res == CURLE_COULDNT_CONNECT)
				{
					cocos2d::CCLog(">failed to download file, could not connect");
					rtv = ERR_SERVER_NA;
				}
				else if(res == CURLE_COULDNT_RESOLVE_HOST)
				{
					cocos2d::CCLog(">failed to download file, could not resolve host");
					rtv = ERR_SERVER_NA;
				}
				else if(res == CURLE_OPERATION_TIMEDOUT)
				{
					cocos2d::CCLog(">failed to download file, timeout");
					rtv = ERR_SERVER_NA;
				}
				else if ( CURLE_PARTIAL_FILE == res )
				{
					cocos2d::CCLog(">failed to download file, partial file");
					rtv = ERR_SERVER_NA;
				}
				else {
					rtv = ERR_SERVER_NA;
				}
			}
		}
		else
		{
			cocos2d::CCLog(">failed to create file for download: %d", errno);
			return ERR_FAILED;
		}

	} while (CURLE_OK != res && trycnt < TYR_TIMES);

	fclose(fp);
	curl_easy_cleanup(m_curlHandle);

	if(!successDownload)
	{
		int err = remove(file_temp.c_str());
		if(err != ERR_SUCCESS)
		{
			cocos2d::CCLog(">>>Error: remove file failed! file: %s", file_temp.c_str());
		}

		if(CURLE_OK != res)
		{
			cocos2d::CCLog(">failed to perform download: %d", res);
			return (RESULT_TYPE)res;
		}
	}

	return rtv;
}



void HttpDownload::setProgressCallback( progress_callback _function )
{
	m_pCallbackFunction = _function;
}


size_t HttpDownload::process_data( void* buffer, size_t size, size_t nmemb, void* user_p )
{
	FILE* fp = (FILE*)user_p; 
#ifdef WIN32
	char *head = (char *)buffer;
	if (!_strnicmp(head, "GIF", 3))
	{
		return 0;
	}
	else if (!_strnicmp(head, "<html>", 6))
	{
		return 0;
	}
#else
	char *head = (char *)buffer;
	if (!strncasecmp(head, "<html>", 6))
	{
		return 0;
	}
#endif
	size_t return_size = fwrite(buffer, size, nmemb, fp);
	return return_size; 
}

int HttpDownload::progress_data( void* data, double dltotal, double dlnow )
{
	if(m_pCallbackFunction)
	{
		m_pCallbackFunction((char*)data, dltotal, dlnow);
	}
	return 0;
}
