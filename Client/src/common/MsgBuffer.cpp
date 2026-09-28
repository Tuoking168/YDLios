#include "stdafx.h"
#include "MsgBuffer.h"


MsgBuffer::MsgBuffer(int size /* = MSG_BUFF_SIZE */)
:buffer_(NULL)
{
	if (size < MSG_BUFF_SIZE)
	{
		size = MSG_BUFF_SIZE;
	}
	max_size_ = size;
	buffer_ = new char[size];
	setg(buffer_, buffer_, buffer_ + size);
	setp(buffer_, buffer_ + size);
}

MsgBuffer::~MsgBuffer()
{
	delete [] buffer_;
}


size_t MsgBuffer::max_size()const
{
	return max_size_;
}