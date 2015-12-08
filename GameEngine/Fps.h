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
		int	getTick();
		void toggleState();

		static Fps& Fps::getInstance()
		{
			static Fps instance;
			return instance;
		}

	private:
		float _lastTime;
		float _frameTime;
		float _elapsedTime;
		Timer _timer;
		int	_tick;
		bool _state;
	};
}