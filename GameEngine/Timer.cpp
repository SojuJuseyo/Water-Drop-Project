#include "Timer.h"
namespace Moo {
	Timer::Timer()
	{
		QueryPerformanceCounter(&_startTime);
		QueryPerformanceCounter(&_endTime);
		QueryPerformanceFrequency(&_frequency);
	}
	Timer::~Timer()
	{

	}

	float	Timer::getElapsedMicroseconds()
	{
		LARGE_INTEGER elapsed;
		QueryPerformanceCounter(&_endTime);
		elapsed.QuadPart = _endTime.QuadPart - _startTime.QuadPart;
		elapsed.QuadPart *= 1000000;
		elapsed.QuadPart /= _frequency.QuadPart;
		return (float)elapsed.QuadPart;
	}

	float	Timer::getElapsedMilliseconds()
	{
		return getElapsedMicroseconds() / 1000;
	}

	float	Timer::getElapsedSeconds()
	{
		return getElapsedMicroseconds() / 1000000;
	}

	void	Timer::reset()
	{
		QueryPerformanceCounter(&_startTime);
	}
}