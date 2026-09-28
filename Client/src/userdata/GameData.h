#ifndef	___GAME_DATA_____
#define ___GAME_DATA_____

class UserData;
class MapData;
class GameRole;
class GhostManager;
struct NetMap;
class PixesMap;
class UserItemData;
enum GAME_STATE
{
	GAME_STATE_LOGIN,
	GAME_STATE_SELECT,
	GAME_STATE_CREATE,
	GAME_STATE_LODING,
	GAME_STATE_RUNNING,
	GAME_STATE_EXIT,
};

class GameData
{
public:
	static void initMapData();
	static void initUserData();
	static void initNetWorkHandle();
	static void releaseUserData();
	static void releaseGameDataForExit();
	static void releaseMapData();

	static GameRole *getMyRole();
	static GhostManager *getGhostManager();
	static NetMap *getCurrentMap();
	static PixesMap *getPixesMap();
	static UserItemData *getUserItemData();

public:
	static MapData*	    s_map;
	static UserData*	s_user;
	static int			s_game_state;
};

#endif //___GAME_DATA_____