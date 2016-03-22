#include "Camera.h"

namespace Moo
{
	Camera::Camera()
	{
		reset();
	}

	Camera::~Camera()
	{
	}

	void	Camera::reset()
	{
		_position = Vector2f(0, 0);
	}

	Vector2f Camera::getPosition() const
	{
		return _position;
	}

	void	Camera::setPosition(const Vector2f &position)
	{
		_position = position;
	}

	void	Camera::move(const Vector2f &offset)
	{
		_position.x += offset.x;
		_position.y += offset.y;
	}
}