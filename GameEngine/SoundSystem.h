#pragma once
#include "fmod.hpp"
#include <map>

typedef FMOD::Sound* SoundClass;

class SoundSystem
{
private:
	std::map<std::string, SoundClass> soundMap;

	bool createSound(SoundClass * sound, const char * file);
public:
	FMOD::System *m_pSystem;

	SoundSystem();
	~SoundSystem();
	bool addSound(const char* file, std::string name);
	void releaseSound(std::string soundName);
	void initAllSounds();
	FMOD::Channel *playSound(std::string soundName, bool loop);
};


