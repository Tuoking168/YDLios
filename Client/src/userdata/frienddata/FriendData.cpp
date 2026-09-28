#include "FriendData.h"

FriendData::FriendsList FriendData::mFriends;

bool sortTwoFriend(FriendData::Friends* fri1, FriendData::Friends* fri2)
{
	if (fri1->online_state == 1 && fri2->online_state == 0)
		return true;
	else
		return false;
}

void FriendData::sortFriendList(int flag)
{
// 	if (flag == 1)
// 		mFs.sort(sortTwoFriend);
// 	else if (flag == 2)
// 		mEs.sort(sortTwoFriend);
// 	else if (flag == 3)
// 		mHs.sort(sortTwoFriend);
}
