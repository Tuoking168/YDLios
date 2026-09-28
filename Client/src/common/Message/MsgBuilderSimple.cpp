#include "stdafx.h"
#include "MsgFactoryByMap.h"
#include "MsgBuilderSimple.h"
#include "MsgFactoryNetworkEx.h"
#include "MsgIf.h"

const char c_msg_header_flag = 47;
const char c_msg_new_header_flag1 = 27;
const char c_msg_new_header_flag2 = 20;
const char s_msg_new_header_reverse = 0;
const short s_msg_header_len = 6;
const short s_msg_new_header_crc1 = 0;
const short s_msg_new_header_crc2 = 0;
const short s_new_msg_head_len = 12;

// #define CRC_HEADER

MsgBuilderWithFactory::MsgBuilderWithFactory(bool bUseCRC /*=true*/, MsgFactoryByMap* pFact /* = NULL */)
:m_bUseCRC(bUseCRC), m_pMsgFact(pFact)
{
	if (m_pMsgFact==0)
	{
		m_pMsgFact = new MsgFactoryNetworkEx;
	}
}

MsgBuilderWithFactory::~MsgBuilderWithFactory()
{
	if (m_pMsgFact)
	{
		delete m_pMsgFact;
	}
}

bool
MsgBuilderWithFactory::onEncodeMsg(IMsg* pMsg, MsgOStream& stream)
{
	if (pMsg!=0)
	{
		if (m_bUseCRC)
		{
			short nMsgLen = pMsg->getLength() + 6;
			stream << c_msg_new_header_flag1 << c_msg_new_header_flag2 << s_msg_new_header_crc1 << s_msg_new_header_crc2;
			stream << pMsg->getMsgCate() << pMsg->getMsgID() << nMsgLen << s_msg_new_header_reverse;
			pMsg->encode(stream);
			stream.CRCMsg(s_new_msg_head_len, nMsgLen - s_new_msg_head_len);
		}
		else
		{
			stream << c_msg_header_flag;
			stream << pMsg->getMsgCate() << pMsg->getMsgID() << s_msg_header_len;
			pMsg->encode(stream);
			stream.updatelen();
		}

		return true;
	}
	else
	{
		return false;
	}
}


int
MsgBuilderWithFactory::onDecodeMsg (IMsg*& pMsg, MsgIStream& stream)
{
	std::size_t rsi = 0;
	char cFlag = 0;
	//LOG_INFO("stream.size = "<< stream.size());
	if (m_bUseCRC)
	{
		bool found = false;
		int headerLen = s_new_msg_head_len;
		while (stream.size() >= s_new_msg_head_len)
		{
			stream >> cFlag;
			if (cFlag == c_msg_new_header_flag1)
			{
				stream >> cFlag;
				if (cFlag == c_msg_new_header_flag2)
				{
					//rsi += 2;
					found = true;
					break;
				}
				++ rsi;
			}
			++ rsi;
		}
		if (!found)
		{
			if (rsi)
			{
				LOG_ERROR("Can't Find msg head wait for next buffer");
				stream.removeread(rsi);
			}
			return 1;
		}
		stream.clearread();
		if (!stream.CheckMsgHeadCRC(s_new_msg_head_len))
		{
			return 2;
		}
	}
	else
	{
		int headerLen = s_msg_header_len;
		while(stream.size() >= s_msg_header_len)
		{
			//LOG_INFO("size = "<< stream.size());
			stream >> cFlag;
			//LOG_INFO("cFLag = "<< (int)cFlag);
			if (cFlag == c_msg_header_flag)
			{
				break;
			}
		
			rsi ++;
		}
		if (cFlag != c_msg_header_flag)
		{
			if (rsi)
			{
				LOG_ERROR("Can't Find msg head wait for next buffer");
				stream.removeread(rsi);
			}
			else
			{
	//			LOG_ERROR("Next Msg Has'n come!");
			}
			return 1;
		}
	}
	char ucMC = 0;
	short nMID = 0, nLen = 0;
	if (m_bUseCRC)
	{
		uint32_t nMergedCRC32 = 0;
		// These 2 ucMC are header flags, and not used
		stream >> ucMC >> ucMC >> nMergedCRC32;
	}
	stream >> ucMC >> nMID >> nLen;
	if (m_bUseCRC)
	{
		uint8_t nReverse = 0;
		stream >> nReverse;
	}
	int headerLen = m_bUseCRC ? s_new_msg_head_len : s_msg_header_len;
	if (nLen < headerLen || nLen > MSG_BUFF_SIZE * 4)
	{
		// This is normally a bad message
		LOG_ERROR("Invalid message length indicator:" << nLen);
		return 2;
	}

	if (stream.size() + headerLen < nLen)
	{
		stream.clearread();
		return 1;
	}


	// if (nLen > MSG_BUFF_SIZE - 6)
	// {
	// 	LOG_ERROR("Messsage length = " << nLen << " is too long, this message will be skipped");
	// 	// This is normally a bad message
	// 	// Remove the head, and find the head flag next time
	// 	stream.removeread(rsi + 6);
	// 	return 1;
	// }


	pMsg = m_pMsgFact->createMsg(ucMC, nMID);
	if (pMsg != NULL)
	{
		pMsg->decode(stream);
		std::size_t rsize = stream.readsize();

		if (rsize != nLen)
		{
			LOG_WARN("msg Length Wrong, message "<< pMsg->getMsgName());
			// DO NOT trust the length in head
			stream.removeread(rsi + rsize);
// 			delete pMsg;
// 			pMsg = NULL;
			//return 0;
		}
		else
		{
			stream.removeread();
		}
//		LOG_INFO("stream.size = "<< stream.size());
		return 0;
	}
	else
	{
		// Remove exactly the message
		stream.removeread(nLen);
		return stream.size() == 0 ? 2 : 1;
	}
}

