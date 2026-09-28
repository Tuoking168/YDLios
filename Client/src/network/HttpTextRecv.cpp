#include "HttpTextRecv.h"
#include "curl.h"
#include "userdata/SystemData.h"


#pragma comment(lib, "libcurl_imp.lib")

httpTextRecv::httpTextRecv():
m_stopEvent(false),m_isRecv(true)
{

}


httpTextRecv::httpTextRecv(std::string url):
m_stopEvent(false),m_url(url),m_isRecv(true)
{

}

httpTextRecv::~httpTextRecv()
{

}

void
httpTextRecv::run()
{
	m_stopEvent = false;
	//m_thread.start(this);
	while(!m_stopEvent)
	{
		if (m_isRecv == false)
		{
			GetUrlText();
		}
	//	getRecvText();
	}
}

void 
httpTextRecv::stop()
{
	m_stopEvent = true;
//	m_thread.wait();
}

bool 
httpTextRecv::Send(IMsg *msg)
{
	return true;
}

std::string 
httpTextRecv::getRecvText()
{
	return m_recv;
}

void
httpTextRecv::setUrl(std::string url)
{
	m_url = url;
	m_recv = "";
	m_isRecv = false;
}

long writer(char *data, int size, int nmemb, std::string &content)
{
	long sizes = size * nmemb;
	std::string temp(data,sizes);
	content += temp; 
	return sizes;
}

void httpTextRecv::GetUrlText()
{
	CURL *pCurl = curl_easy_init();
	curl_easy_setopt(pCurl,CURLOPT_URL,m_url.c_str());
	curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &m_recv);
	curl_easy_perform(pCurl);
	curl_easy_cleanup(pCurl);
	//stop();
	m_isRecv = true;
}

bool httpTextRecv::isRecv()
{
	return m_isRecv;
}