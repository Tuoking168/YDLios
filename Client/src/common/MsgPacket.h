//////////////////////////////////////////////////////////////////////////
// MsgPacket.h
// 
// W.Y-J
// 2012.3.30
//////////////////////////////////////////////////////////////////////////

#ifndef __MSGPACKET_H__
#define __MSGPACKET_H__

#include "MsgBuffer.h"
#include "../../../shared/CommonType.h"

class MsgPacket
{
public:
	MsgPacket() : m_msgid(0) {}

	explicit MsgPacket(uint16 msgid) : m_msgid(msgid) {}

	void Initialize(uint16 msgid)
	{
		clear();
		m_msgid = msgid;
	}

	void clear()
	{
		buffer.rd_ptr(size_t(0));
		buffer.wr_ptr(size_t(0));
	}

	uint16 GetMsgID() const { return m_msgid; }
	void SetMsgID(uint16 msgid) { m_msgid = msgid; }

	char *rd_ptr (void) const
	{
		return buffer.rd_ptr();
	}
	void rd_ptr (size_t n)
	{
		buffer.rd_ptr(n);
	}
	void rd_ptr (char* p)
	{
		buffer.rd_ptr(p);
	}
	char *wr_ptr (void) const
	{
		return buffer.wr_ptr();
	}
	void wr_ptr (size_t n)
	{
		buffer.wr_ptr(n);
	}

	size_t size() const
	{
		return buffer.size();
	}

	template<typename T>
	MsgPacket& operator >> (T& val)
	{
		buffer.sgetn((char*)&val, sizeof(val));
		return *this;
	}
	MsgPacket& operator >> (short& val)
	{
		buffer.sgetn((char*)&val, sizeof(val));
		return *this;
	}
#ifdef WIN32
	template<>
#endif
	MsgPacket& operator >>(char *&val)
	{
		unsigned short size = 0;
		buffer.sgetn((char*)&size, sizeof(size));
		if (size!=0)
		{
			buffer.sgetn(val, size);
			val[size] = 0;
		}
		return *this;
	}
	template<int N>
	MsgPacket& operator >>(char (&val)[N])
	{
		unsigned short size = 0;
		buffer.sgetn((char*)&size, sizeof(size));
		if (size!=0 && size < N)
		{
			buffer.sgetn(val, size);
			val[size] = 0;
		}
		return *this;
	}
#ifdef WIN32
	template<>
#endif
	MsgPacket& operator >> (std::string& val)
	{
// 		unsigned short size = 0;
// 		buffer.sgetn((char*)&size, sizeof(size));
// 		if (size!=0)
// 		{
// 			val.resize(size);
// 			buffer.sgetn((char*)val.data(), size);
// 		}
		val = "";
		bool flag = false;
		char c;
		for ( int i = 0; i < 1024*12; i++ )
		{
			c = buffer.sbumpc();
			if(c==0)
			{
				break;
			}
			val.push_back(c);
			flag = true;
		}
		if(flag == false)
		{
			val = "";
		}
		return *this;
	}
	template<typename T>
	MsgPacket& operator << (const T& val)
	{
		buffer.sputn((const char*)&val, sizeof(val));
		return *this;
	}

	MsgPacket& operator << (const short& val)
	{
		buffer.sputn((const char*)&val, sizeof(val));
		return *this;
	}
#ifdef WIN32
	template<>
#endif
	MsgPacket& operator << (const char * const &val)
	{
		unsigned short size = strlen(val);
		buffer.sputn((const char*)&size, sizeof(size));
		if (size!=0)
		{
			buffer.sputn(val, size);
		}
		return *this;
	}
#ifdef WIN32
	template<>
#endif
	MsgPacket& operator << (char * const &val)
	{
		unsigned short size = strlen(val);
		buffer.sputn((const char*)&size, sizeof(size));
		if (size!=0)
		{
			buffer.sputn(val, size);
		}
		return *this;
	}
	template<int N>
	MsgPacket& operator << (const char (&val)[N])
	{
		unsigned short size = strlen(val);
		buffer.sputn((const char*)&size, sizeof(size));
		if (size!=0)
		{
			buffer.sputn(val, size);
		}
		return *this;
	}
	template<int N>
	MsgPacket& operator << (char (&val)[N])
	{
		unsigned short size = strlen(val);
		buffer.sputn((const char*)&size, sizeof(size));
		if (size!=0)
		{
			buffer.sputn(val, size);
		}
		return *this;
	}
#ifdef WIN32
	template<>
#endif
	MsgPacket& operator << (const std::string& val)
	{
		unsigned short size = val.size();
		if (size!=0)
		{
			buffer.sputn(val.c_str(), size);
		}
		buffer.sputc(char(0));
		return *this;
	}

protected:
	uint16		m_msgid;
	MsgBuffer	buffer;
};
#endif // __MSGPACKET_H__
