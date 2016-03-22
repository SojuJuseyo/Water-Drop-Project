#pragma once

#include <al.h>
#include <alc.h>
#include "Sound.h"

namespace Moo
{
	class Audio
	{
	public:
		Audio();
		~Audio();
		static Audio& getInstance()
		{
			static Audio instance;
			return instance;
		}
		bool init();
		void destroy();
		bool playSound(Sound &, bool);
		void pauseSound(Sound & sound);
	private:
		ALCdevice *_dev;
		ALCcontext *_devcon;
	};
}