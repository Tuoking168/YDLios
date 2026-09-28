#ifndef		___AUDIO_LOADING___
#define		___AUDIO_LOADING___

#include "cocos2d.h"
USING_NS_CC;

enum
{
	sound_attack_knife=56,
	sound_attack_no_weapon=57,
	sound_attack_arrow=1000,
	sound_attack_knife_female=1001,
	sound_give_gole_coin=1002,
	sound_drink_drug=1003,
	sound_switch_panel=1004,
	sound_be_attack_male=1005,
	sound_be_attack_female=1006,
	sound_die_male=1007,
	sound_die_female=1008,
	sound_use_magic=2000,
	sound_shout_male=2001,
	sound_shout_female=2002,
	sound_mofadun=2004,
	sound_level_up=3001,
	sound_normal_step_one=4003,
	sound_normal_step_two=4004,
	sound_water_step_one=4701,
	sound_water_step_two=4702,
	sound_grass_step_one=4801,
	sound_grass_step_two=4802,
	sound_mud_step_one=4901,
	sound_mud_step_two=4902,
	sound_bird_sing_quiet=8001,
	sound_bird_sing_loud=8102,
	sound_criket_sing=8601,
	sound_water_flow_loud=8101,
	sound_water_flow_middle=8103,
	sound_water_flow_small=8701,
	sound_water_flow_quiet=8801,
	sound_wind_blow=8901,
	sound_max=31
};

class AudioLoading : public CCNode
{
public:
	static	void	doLoad();
	static	int		start(int idx,bool loop=false);
	static	void	stop(int effectId);
	static  void	startBackgroundMusic(int idx);
	static	void	set_state_sound(bool v);
	static	void	stopAll();

public:
	static	bool	_sound_status;
	static	short	_current_music_idx;
	static	bool	_loaded;
};

#endif
