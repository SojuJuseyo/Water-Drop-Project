#include <al.h>
#include <alc.h>
#include <windows.h>
#include <iostream>

namespace Moo
{
	class Sound
	{
	public:
		Sound();
		~Sound();
		ALuint getSource();
		bool loadSound(const std::string &);

	private:
		ALuint _source;
		bool _currentState;
	};
}