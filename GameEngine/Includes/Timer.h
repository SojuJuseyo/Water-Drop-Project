#pragma once

#include <windows.h>

namespace Moo {
	class Timer
	{
	public:
		Timer();
		~Timer();

		float getElapsedMicroseconds();
		float getElapsedMilliseconds();
		float getElapsedSeconds();
		void reset();

	private:
		LARGE_INTEGER _frequency, _startTime, _endTime;
	};
}