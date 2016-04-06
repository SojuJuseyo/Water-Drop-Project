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

	m_pSystem->init(10, FMOD_INIT_NORMAL, nullptr);
}
SoundSystem::~SoundSystem()
{
}

void SoundSystem::createSound(SoundClass *pSound, const char* pFile)
{
	FMOD_RESULT res = m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
	if (res)
		printf("Create sound failed, error %i", res);
}

void SoundSystem::initAllSounds()
{
	createSound(&soundMap["Home"], "C:\\Users\\Varkiil\\Desktop\\HOME - Resonance.mp3");
	createSound(&soundMap["Alibi"], "C:\\Users\\Varkiil\\Desktop\\Love Alibi - K Klass Remix.mp3");
}

// Returns a channel FMOD, use it's method stop() to stop the sound
FMOD::Channel *SoundSystem::playSound(std::string soundName, bool bLoop = false)
{
	SoundClass pSound = soundMap[soundName];

	if ((pSound) == nullptr)
		printf("Attempted to play an unknown sound.\n");

	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	FMOD::Channel *channel;

	FMOD_RESULT res = m_pSystem->playSound(pSound, 0, false, &channel);
	if (res != FMOD_OK)
		printf("Play sound failed, error %i", res);
	return channel;
}

// Will release sound, free it from memory
void SoundSystem::releaseSound(std::string soundName)
{
	SoundClass pSound = soundMap[soundName];
	FMOD_RESULT res = pSound->release();
	if (res != FMOD_OK)
		printf("Release sound failed, error %i", res);

}