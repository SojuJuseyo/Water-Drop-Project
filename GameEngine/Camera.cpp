#include "Camera.h"

namespace Moo
{
	Camera::Camera()
	{
		_position = Vector2f(0, 0);
	}

	Camera::~Camera()
	{
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