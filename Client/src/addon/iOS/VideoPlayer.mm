#include "VideoPlayer.h"
#include "CCVideoPlayer.h"
#include "cocos2d.h"

VideoPlayer* VideoPlayer::shared()
{
	static VideoPlayer __v_p__;
	return &__v_p__;
}


void VideoPlayer::start()
{
	[CCVideoPlayer playMovieWithFile: @"data/v/start.mp4"];
	[CCVideoPlayer setNoSkip: YES];
	cocos2d::CCLog("Video Started.");
}

void VideoPlayer::stop()
{
	cocos2d::CCLog("Going to stop the video.\n");
	[CCVideoPlayer cancelPlaying];
	cocos2d::CCLog("Video stoped.");
}

bool VideoPlayer::is_playing()
{
	return [CCVideoPlayer isPlaying];
}