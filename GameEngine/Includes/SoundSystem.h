#pragma once

#include <fmod.hpp>
#include <iostream>
#include <map>
#include <fmod_errors.h>
#include <windows.h>

#include "Exceptions.h"

#define SOUNDS_PATH "Ressources/Sounds/"

typedef FMOD::Sound* SoundClass;

class SoundSystem
{
private:
	std::map<std::string, SoundClass> soundMap;
	float _volume;

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
	void playSoundTilEnd(std::string soundName);
	float getVolume();
	void setVolume(float volume);
};
