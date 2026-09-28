#ifndef __CC_FILE_DATA_STREAM__
#define __CC_FILE_DATA_STREAM__

#include "platform/CCFileUtils.h"

#define MAX_USER_DATA_SIZE	16*1024

class CCFileDataStream
{
public:
	CCFileDataStream();
	~CCFileDataStream();

	bool save(const char* pszFileName);
	bool load(const char* pszFileName);


	template <class DataType>
	bool write(const DataType& d)
	{
		if (m_pBuffer==NULL)
		{
			m_pBuffer = new unsigned char[MAX_USER_DATA_SIZE];
			m_uWPtr = 0;
			m_uRPtr = 0;
		}
		memcpy(m_pBuffer+m_uWPtr, &d, sizeof(d));
		m_uWPtr+=sizeof(d);
		return true;
	}

	template <class DataType>
	bool read(DataType& d)
	{
		if (m_uRPtr+sizeof(d)<=m_uWPtr)
		{
			memcpy(&d, m_pBuffer+m_uRPtr, sizeof(d));
			m_uRPtr+=sizeof(d);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool write(const char* buff, short size)
	{
		if (m_pBuffer==NULL)
		{
			m_pBuffer = new unsigned char[MAX_USER_DATA_SIZE];
			m_uWPtr = 0;
			m_uRPtr = 0;
		}
		memcpy(m_pBuffer+m_uWPtr, buff, size);
		m_uWPtr+=size;
		return true;
	}

	bool read(char* buff, short size)
	{
		if (m_uRPtr+size<=m_uWPtr)
		{
			memcpy(buff, m_pBuffer + m_uRPtr, size);
			m_uRPtr+=size;
			return true;
		}
		else
		{
			return false;
		}
	}


	bool write(const std::string& val)
	{
		if (m_pBuffer==NULL)
		{
			m_pBuffer = new unsigned char[MAX_USER_DATA_SIZE];
			m_uWPtr = 0;
			m_uRPtr = 0;
		}

		unsigned short size = val.size();
		*(short*)(m_pBuffer+m_uWPtr) = size;
		m_uWPtr+=sizeof(size);
		if (size!=0)
		{
			memcpy(m_pBuffer+m_uWPtr, val.data(), size);
			m_uWPtr+=size;
		}
		return true;
	}

	bool read(std::string& val)
	{
		if (m_uRPtr+2<=m_uWPtr)
		{
			unsigned short size = 0;
			size = * (short*)(m_pBuffer + m_uRPtr);
			m_uRPtr+=sizeof(size);
			if (size!=0 && m_uRPtr+size<=m_uWPtr)
			{
				char* buff = new char[size+1];
				memcpy(buff, m_pBuffer + m_uRPtr, size);
				buff[size] = 0;
				m_uRPtr+=size;
				val = buff;
				return true;
			}
		}
		return false;
	}

	unsigned long size()
	{
		return m_uWPtr-m_uRPtr;
	}

	CC_SYNTHESIZE_READONLY(unsigned char *, m_pBuffer, Buffer);
	CC_SYNTHESIZE_READONLY(unsigned long ,  m_uRPtr,   RPtr);
	CC_SYNTHESIZE_READONLY(unsigned long ,  m_uWPtr,   WPtr);

	//FILE*			m_theFile;
};

#endif
