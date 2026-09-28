#ifndef __VIDEO_PLAYER___
#define __VIDEO_PLAYER___

class VideoPlayer 
{
public:
	static VideoPlayer* shared();

	void	start();
	void	stop();
	bool	is_playing();
};

#endif
