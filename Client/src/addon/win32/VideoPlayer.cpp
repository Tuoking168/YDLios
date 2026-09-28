#include "../VideoPlayer.h"



VideoPlayer* VideoPlayer::shared()
{
	static VideoPlayer __v_p__;
	return &__v_p__;
}


void VideoPlayer::start()
{

}

void VideoPlayer::stop()
{

}

bool VideoPlayer::is_playing()
{
	return false;
}