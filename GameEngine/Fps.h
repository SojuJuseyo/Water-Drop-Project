#pragma once

#include "Timer.h"

namespace Moo
{
	class Fps
	{
	public:
		Fps();
		~Fps();
		void update();
		float getFrameTime();
		void reset(float limit);

	private:
		float _lastTime;
		float _frameTime;
		float _elapsedTime;
		Timer _timer;
	};
}