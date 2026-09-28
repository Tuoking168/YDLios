#ifndef _NETITEM_H_
#define _NETITEM_H_

class NetItem 
{
public:
	NetItem() 
	{
		mPosition = 0;
		mTypeID = 0;
		mDuraMax = 0;
		mDuration = 0;
		mItemFlags = 0;
		mLevel = 0;
		mAddAC = 0;
		mAddMAC = 0;
		mAddDC = 0;
		mAddMC = 0;
		mAddSC = 0;
		mAddHp = 0;
		mAddMp = 0;
		mUpdAC = 0;
		mUpdMAC = 0;
		mUpdDC = 0;
		mUpdMC = 0;
		mUpdSC = 0;
		mLuck = 0;
		mProtect = 0;
		mCreateTime = 0;
	}

public:
	static const int ITEM_FLAG_BIND = 0x1;
	static const int ITEM_FLAG_USE_BIND = 0x2;
	static const int ITEM_FLAG_JIPING = 0x4;

	int mPosition;
	int mTypeID;
	int mDuraMax;
	int mDuration;
	int mItemFlags;
	int mLevel;
	short mAddAC;
	short mAddMAC;
	short mAddDC;
	short mAddMC;
	short mAddSC;
	short mAddHp;
	short mAddMp;
	short mUpdAC;
	short mUpdMAC;
	short mUpdDC;
	short mUpdMC;
	short mUpdSC;
	short mLuck;
	short mProtect;
	int mCreateTime;
};

#endif //_NETITEM_H_
