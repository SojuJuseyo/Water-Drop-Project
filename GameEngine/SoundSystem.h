#pragma once
#include "fmod.hpp"
#include <map>

typedef FMOD::Sound* SoundClass;

class SoundSystem
{
private:
	std::map<std::string, SoundClass> soundMap;

	void createSound(SoundClass * pSound, const char * pFile);
public:
	FMOD::System *m_pSystem;

	SoundSystem();
	~SoundSystem();
	void releaseSound(std::string soundName);
	void initAllSounds();
	FMOD::Channel *playSound(std::string soundName, bool bLoop);
};


