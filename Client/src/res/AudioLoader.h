#ifndef __AudioLoader_h__
#define	__AudioLoader_h__

#include "utils/MacroUtils.h"
#include <string>
#include "CCActionInterval.h"

namespace Sound
{
	namespace Effect
	{
		enum
		{
			zoulu = 1,
			shengji = 2,
			nangongji = 3,
			nansiwang = 4,
			nvgongji = 5,
			nvsiwang = 6,
			chibanghecheng = 7,
			dixueliang = 8,
			genghuanfangjv = 9,
			genghuanwuqi = 10,
			hecheng = 11,
			hunshixiangqian = 12,
			huodejinbi = 13,
			jianding = 14,
			jinenglengque = 15,
			jipinzhuanyi = 16,
			qianghua = 17,
			qianghuashibai = 18,
			qiling = 19,
			qilingshibai = 20,
			tihuan = 21,
		};
	}

	namespace Music
	{
		enum
		{
			login = 1,
		};
	}
}

class AudioLoader
{
public:
	static void doLoad();

	static void play(int effectID);
	static void play(const std::string &effectPath);

	static void transform(int musicID);
	static void transform(const std::string &musicPath);

	static void setSilent(bool silent);
	static bool isSilent();

	static void setEffectSilent(bool silent);
	static bool isEffectSilent();
	
	static void reduceEffectVoice();
	static void reduceBackGroundVoice();
	static void addEffectVoice();
	static void addBackGroundVoice();
	static void setBackGroundVolume(float volume);

	static void	stopAll();

private:
	CP_MAKE_STATIC_CLASS(AudioLoader);

	static void change(const std::string &targetMusicPath);

private:
	static bool sLoaded;
	static bool sIsSilent;
	static bool sIsEffectSilent;
	static std::string sCurrentMusic;
};

#endif //__AudioLoader_h__
