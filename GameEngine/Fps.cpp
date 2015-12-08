#include "Fps.h"

namespace Moo
{
	Fps::Fps()
	{
		_lastTime = 0;
		_frameTime = 0;
		_elapsedTime = _timer.getElapsedSeconds();
		_tick = 0;
		_state = true;
	}

	Fps::~Fps()
	{

	}

	int		Fps::getTick()
	{
		return _tick;
	}

	void	Fps::update()
	{
		if (_state) {
			_elapsedTime = _timer.getElapsedSeconds();
			_frameTime += (_elapsedTime - _lastTime);
			_lastTime = _elapsedTime;
		}
	}

	void	Fps::toggleState()
	{
		_state = !_state;
	}

	float	Fps::getFrameTime()
	{
		return _frameTime;
	}

	void	Fps::reset(float limit)
	{
		_tick++;
		_frameTime -= 1.0f / limit;
	}
}