#include "SoundSystem.h"
#include "fmod.hpp"
#include "stdio.h"

SoundSystem::SoundSystem()
{
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		return;
	}

	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		return;
	}

	m_pSystem->init(30, FMOD_INIT_NORMAL, nullptr);
}
SoundSystem::~SoundSystem()
{
}

bool SoundSystem::createSound(SoundClass *sound, const char* file)
{
	FMOD_RESULT res = m_pSystem->createSound(file, FMOD_DEFAULT, 0, sound);
	if (res)
	{
		printf("Create %s sound failed, error %i\n", file, res);
		return false;
	}
	return true;
}


bool SoundSystem::addSound(const char* file, std::string name)
{
	bool res = createSound(&soundMap[name], file);
	if (res)
	{
		printf("Create %s sound failed, error %i\n", name.c_str(), res);
		return false;
	}
	return true;
}

void SoundSystem::initAllSounds()
{
//	createSound(&soundMap["Home"], "C:\\Users\\Varkiil\\Desktop\\HOME - Resonance.mp3");
//	createSound(&soundMap["Alibi"], "C:\\Users\\Varkiil\\Desktop\\Love Alibi - K Klass Remix.mp3");
	createSound(&soundMap["jump"], "jump.wav");
	createSound(&soundMap["victory"], "Victory.wav");
	createSound(&soundMap["defeat"], "Defeat.wav");
	createSound(&soundMap["menu"], "Menu.wav");
}

// Returns a channel FMOD, use it's method stop() to stop the sound
FMOD::Channel *SoundSystem::playSound(std::string soundName, bool loop = false)
{
	SoundClass pSound = soundMap[soundName];

	if ((pSound) == nullptr)
		printf("Attempted to play an unknown sound.(%s)\n", soundName.c_str());

	if (!loop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	FMOD::Channel *channel;

	FMOD_RESULT res = m_pSystem->playSound(pSound, 0, false, &channel);
	if (res != FMOD_OK)
		printf("Play %s sound failed, error %i\n", soundName.c_str(), res);
	return channel;
}

// Will release sound, free it from memory
void SoundSystem::releaseSound(std::string soundName)
{
	SoundClass pSound = soundMap[soundName];
	FMOD_RESULT res = pSound->release();
	if (res != FMOD_OK)
		printf("Release %s sound failed, error %i\n", soundName.c_str(), res);

}