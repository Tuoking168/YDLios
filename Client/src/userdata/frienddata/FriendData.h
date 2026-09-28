#ifndef __FRIEND_DATA_H__
#define __FRIEND_DATA_H__

#include <vector>
#include <string>
#include <map>

class FriendData
{
public:
	struct Friends
	{
		std::string name;
		int title;//50表示仇人 100表示好友 20表示黑名单
		short online_state;
		Friends():title(100),online_state(1){}
	};
	typedef std::map<std::string,Friends*> FriendsList;
	static void sortFriendList(int flag);
	static FriendsList mFriends;
};

#endif//__FRIEND_DATA_H__