#include "Audio.h"

namespace Moo
{
	Audio::Audio()
	{

	}

	Audio::~Audio()
	{

	}

	bool	Audio::init()
	{
		_dev = alcOpenDevice(NULL);
		if (!_dev) {
			return false;
		}
		_devcon = alcCreateContext(_dev, NULL);
		alcMakeContextCurrent(_devcon);
		if (!_devcon) {
			return false;
		}
		return true;
	}

	bool	Audio::playSound(Sound &sound, bool loop)
	{
		alSourcei(sound.getSource(), AL_LOOPING, loop);
		alSourcePlay(sound.getSource());
		if (alGetError() != AL_NO_ERROR) {
			return false;
		}
		return true;
	}

	void	Audio::pauseSound(Sound &sound)
	{
		alSourcePause(sound.getSource());
	}

	void	Audio::destroy()
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(_devcon);
	}
}