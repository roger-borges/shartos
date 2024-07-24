#ifndef _audibleH_
#define _audibleH_

#include <map>
#include "object.h"
#include "dmusici.h"
#include "timer.h"
class audible : object
{
public:
	audible();
	~audible();
	void loadMusic(const std::string&);
	void startMusic(const std::string&);
	void stopMusic();
	const std::string getMusic();
	void loadSound(const std::string&);
	void startSound(const std::string&);
protected:
private:
	std::map<std::string, IDirectMusicSegment8*> _music;
	std::map<std::string, IDirectMusicSegment8*> _sound;
	std::string _current_music;
	Timer _timer;
	IDirectMusicPerformance8* _performance;
	IDirectMusicLoader8* _loader;

};

#endif