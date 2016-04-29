#include "SoundSystem.h"
#include <stdio.h>

SoundSystem::SoundSystem()
{
	FMOD_RESULT res;
	res = FMOD::System_Create(&m_pSystem);
	if (res != FMOD_OK) {
		throw Moo::InitException("Create soundSystem failed, " + std::string(FMOD_ErrorString(res)));
		return;
	}

	int driverCount = 0;
	res = m_pSystem->getNumDrivers(&driverCount);

	if (driverCount == 0) {
		throw Moo::InitException("Driver failed, " + std::string(FMOD_ErrorString(res)));
		return;
	}

	res = m_pSystem->init(30, FMOD_INIT_NORMAL, nullptr);
	if (res != FMOD_OK) {
		throw Moo::InitException("Init soundSystem failed, " + std::string(FMOD_ErrorString(res)));
		return;
	}

	initAllSounds();
}

SoundSystem::~SoundSystem()
{
}

bool SoundSystem::createSound(SoundClass *sound, const char* file)
{
	if (file == nullptr) {
		std::cerr << "Create sound failed, file name is null" << std::endl;
		return false;
	}
	FMOD_RESULT res = m_pSystem->createSound(std::string(SOUNDS_PATH + std::string(file)).c_str(), FMOD_DEFAULT, 0, sound);
	if (res != FMOD_OK) {
		std::cerr << "Create " << file << " sound failed, " << FMOD_ErrorString(res) << std::endl;
		return false;
	}
	return true;
}


bool SoundSystem::addSound(const char* file, std::string name)
{
	bool res = createSound(&soundMap[name], file);
	if (res != true) {
		std::cerr << "Create " << name.c_str() << " sound from file " << file << " has failed" << std::endl;
		return false;
	}
	return true;
}

void SoundSystem::initAllSounds()
{
	createSound(&soundMap["jump"], "jump.wav");
	createSound(&soundMap["victory"], "Victory.wav");
	createSound(&soundMap["defeat"], "Defeat.wav");
	createSound(&soundMap["menu"], "Menu.wav");
}

// Returns a channel FMOD, use it's method stop() to stop the sound
FMOD::Channel *SoundSystem::playSound(std::string soundName, bool loop = false)
{
	SoundClass pSound = soundMap[soundName];

	if ((pSound) == nullptr) {
		//throw Moo::Exception("Attempted to play an unknown sound.");
		return nullptr;
	}
	if (!loop) {
		pSound->setMode(FMOD_LOOP_OFF);
	}
	else {
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	FMOD::Channel *channel;

	FMOD_RESULT res = m_pSystem->playSound(pSound, 0, false, &channel);
	if (res != FMOD_OK) {
		throw Moo::Exception("Play " + soundName + "sound failed, " + std::string(FMOD_ErrorString(res)));
		return nullptr;
	}
	return channel;
}

void SoundSystem::releaseAllSounds()
{
	for (auto sound : soundMap) {
		releaseSound(sound.first);
	}
}

// Will release sound, free it from memory
void SoundSystem::releaseSound(std::string soundName)
{
	SoundClass pSound = soundMap[soundName];
	FMOD_RESULT res = pSound->release();
	if (res != FMOD_OK) {
		std::cerr << "Release " << soundName << "sound failed, " << FMOD_ErrorString(res) << std::endl;;
	}
}