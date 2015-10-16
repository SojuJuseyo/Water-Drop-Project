#include "Fps.h"

namespace Moo
{
	Fps::Fps()
	{
		_lastTime = 0;
		_frameTime = 0;
		_elapsedTime = _timer.getElapsedSeconds();
	}

	Fps::~Fps()
	{

	}

	void	Fps::update()
	{
		_elapsedTime = _timer.getElapsedSeconds();
		_frameTime += (_elapsedTime - _lastTime);
		_lastTime = _elapsedTime;
	}

	float	Fps::getFrameTime()
	{
		return _frameTime;
	}

	void	Fps::reset(float limit)
	{
		_frameTime -= 1.0f / limit;
	}
}