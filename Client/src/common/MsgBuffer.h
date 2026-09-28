#ifndef	___MSG_BUFFER___
#define ___MSG_BUFFER___

#include <iosfwd>
#include <streambuf>


#define MSG_BUFF_SIZE 1024 * 2

class MsgBuffer	:	public std::streambuf
{
public:
	MsgBuffer(int size = MSG_BUFF_SIZE);
	~MsgBuffer();

	std::size_t size() const
	{
		return pptr() - gptr();
	}

	std::size_t max_size() const;

	void commit(std::size_t n)
	{
		if (pptr() + n > epptr())
			n = epptr() - pptr();
		pbump(static_cast<int>(n));
		setg(eback(), gptr(), pptr());
	}

	void consume(std::size_t n)
	{
		if (gptr() + n > pptr())
			n = pptr() - gptr();
		gbump(static_cast<int>(n));
	}

	void update_buffer_length4() 	
	{ 		
		short val = size(); 		
		memcpy(gptr()+4, (char*)&val, 2);  	
	}

	char *rd_ptr (void) const
	{
		return gptr();
	}

	void rd_ptr (char *new_ptr)
	{
		setg(buffer_, new_ptr, buffer_ + max_size_);
	}

	void rd_ptr (size_t n)
	{
		setg(buffer_, buffer_ + n, buffer_ + max_size_);
	}

	char *wr_ptr (void) const
	{
		return pptr();
	}

	void wr_ptr (size_t n)
	{
		setp(buffer_ + n, buffer_ + max_size_);
	}

	void append(const MsgBuffer &buff)
	{
		//size_t rd = 0;
// 		size_t wr = 0;
// 		wr = wr_ptr() - buffer_;
// 
// 		memcpy(&buffer_[wr], buff.rd_ptr(), buff.size());
// 		wr_ptr(wr + buff.size());
		size_t rd = 0;
		size_t wr = 0;
		wr = wr_ptr() - buffer_;
		if (max_size_ < buff.size() + wr)
		{
			char *pTemp = new char[max_size() + buff.max_size()];
			memcpy(pTemp, buffer_, wr);
			rd = rd_ptr() - buffer_;
			delete [] buffer_;
			buffer_ = pTemp;
			max_size_ += buff.max_size();
			rd_ptr(rd);
			wr_ptr(wr);
		}

		memcpy(&buffer_[wr], buff.rd_ptr(), buff.size());
		wr_ptr(wr + buff.size());
	}

	void removeread()
	{
		size_t rd = rd_ptr() - buffer_;
		if (rd)
		{
			size_t wr = wr_ptr() - buffer_;
			memmove(buffer_, &buffer_[rd], size());
			wr -= rd;
			rd_ptr((size_t)0);
			wr_ptr(wr);
		}
	}
	void removeread(std::size_t rsize)
	{
		clearread();
		size_t rdmax = size();
		if (rdmax < rsize)
			rsize = rdmax;
		if (rsize)
		{
			printf("removeread size = %ld",rsize);
			size_t wr = wr_ptr() - buffer_;
			memmove(buffer_, &buffer_[rsize], size());
			wr -= rsize;
			rd_ptr((size_t)0);
			wr_ptr(wr);
		}
	}
	void clearread()
	{
		this->rd_ptr(buffer_);
	}

	std::size_t readsize() const
	{
		return rd_ptr() - buffer_;
	}

	void copy(const MsgBuffer& buff,int size)
	{
// 		if ((size_t)size > max_size_)
// 		{
// 			delete []buffer_;
// 			buffer_ = new char[size];
// 			max_size_ = size;
// 		}
// 		memcpy(buffer_, buff.rd_ptr(), size);
// 		setg(buffer_, buffer_, buffer_ + max_size_);
// 		setp(buffer_, buffer_ + max_size_);
	}

	void copy(const MsgBuffer& buff)
	{
// 		if (buff.max_size()>max_size_)
// 		{
// 			delete []buffer_;
// 			buffer_ = new char[buff.max_size()];
// 			max_size_ = buff.max_size();
// 		}
// 		memcpy(buffer_, buff.buffer_, buff.max_size());
// 		setg(buffer_, buffer_ + (buff.gptr()-buff.eback()), buffer_ + max_size_);
// 		setp(buffer_, buffer_ + (buff.pptr()-buff.pbase()), buffer_ + max_size_);
// 
	}

protected:
	enum { buffer_delta = 128 };

	int_type underflow()
	{
		if (gptr() < pptr())
		{
			setg(&buffer_[0], gptr(), pptr());
			return traits_type::to_int_type(*gptr());
		}
		else
		{
			return traits_type::eof();
		}
	}


	int_type overflow(int_type c)
	{
		// detail in boost buffer
		return traits_type::not_eof(c);
	}

	void reserve(std::size_t n)
	{
		//	detail in boost buffer
	}
private:
	char* buffer_;
	size_t	max_size_;
};


#endif
