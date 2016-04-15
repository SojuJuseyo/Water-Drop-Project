#pragma once
#include <fmod.hpp>
#include <iostream>
#include <map>
#include <fmod_errors.h>

#include "Exceptions.h"

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
	void releaseAllSounds();
	FMOD::Channel *playSound(std::string soundName, bool loop);
};


