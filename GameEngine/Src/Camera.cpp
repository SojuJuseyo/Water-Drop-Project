#include "Camera.h"
#include <iomanip>

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

	void	Camera::resetToPlayer(Hitbox hitbox)
	{
		float x = (hitbox.x1 - 400);
		float y = (hitbox.y1 - 300);
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;
		if (x > (_mapInfos->getMapWidth() * 40 - 800))
			x = (_mapInfos->getMapWidth() * 40 - 800);
		if (y > (_mapInfos->getMapHeight() * 40 - 600))
			y = (_mapInfos->getMapHeight() * 40 - 600);
		_position = Vector2f(x * -1, y * -1);
	}

	Vector2f Camera::getPosition() const
	{
		return _position;
	}

	void	Camera::setPosition(const Vector2f &position)
	{
		_position = position;
	}

	std::shared_ptr<MapInfos> Camera::getInfoMap()
	{
		return _mapInfos;
	}

	void	Camera::setInfoMap(std::shared_ptr<MapInfos> mapInfos)
	{
		_mapInfos = mapInfos;
	}

	void	Camera::update(Hitbox hitbox)
	{
		Vector2f posCamera(_position.x * -1, _position.y * -1);

		if (!_isHitboxSet)
		{
			_isHitboxSet = true;
			_lastHitbox = hitbox;
		}
		if (hitbox.x1 - _lastHitbox.x1 > 0) // si direction positive axe x
		{
			if (hitbox.x1 > posCamera.x + 400 && posCamera.x + (hitbox.x1 - _lastHitbox.x1) < (_mapInfos->getMapWidth() * 40 - 800))
				_position.x += (_lastHitbox.x1 - hitbox.x1);
		}
		else
			if (hitbox.x1 - _lastHitbox.x1 < 0) // si direction negative axe x
			{
				if (hitbox.x1 < posCamera.x + 400 && posCamera.x + (hitbox.x1 - _lastHitbox.x1) > 0)
					_position.x += (_lastHitbox.x1 - hitbox.x1);
			}
		if (hitbox.y1 - _lastHitbox.y1 > 0) // si direction negative axe y
		{
			if (hitbox.y1 > posCamera.y + 300 && posCamera.y + (hitbox.y1 - _lastHitbox.y1) < (_mapInfos->getMapHeight() * 40 - 600))
				_position.y += (_lastHitbox.y1 - hitbox.y1);
		}
		else
			if (hitbox.y1 - _lastHitbox.y1 < 0) // si direction positive axe y
			{
				if (hitbox.y1 < posCamera.y + 300 && posCamera.y + (hitbox.y1 - _lastHitbox.y1) > 0)
					_position.y += (_lastHitbox.y1 - hitbox.y1);
			}
		_lastHitbox = hitbox;
	}

	void	Camera::move(const Vector2f &offset)
	{
		_position.x += offset.x;
		_position.y += offset.y;
	}
}