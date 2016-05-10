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
		float x = (hitbox.x1 - 320) * -1;
		float y = (hitbox.y1 - 320) * -1;
		if (x > 0)
			x = 0;
		if (y > 0)
			y = 0;
		if (x < (_mapInfos.getMapWidth() * 40 - 800) * -1)
			x = (_mapInfos.getMapWidth() * 40 - 800) * -1;
		if (y < (_mapInfos.getMapHeight() * 40 - 600) * -1)
			y = (_mapInfos.getMapHeight() * 40 - 600) * -1;
		_position = Vector2f(x, y);
	}

	Vector2f Camera::getPosition() const
	{
		return _position;
	}

	void	Camera::setPosition(const Vector2f &position)
	{
		_position = position;
	}

	void	Camera::setInfoMap(MapInfos mapInfos)
	{
		_mapInfos = mapInfos;
	}

	void	Camera::update(Hitbox hitbox)
	{
		Vector2f posCamera(_position.x * -1, _position.y * -1);
		Hitbox hitboxTmp;

		hitboxTmp.x1 = hitbox.x1 - 180;
		hitboxTmp.y1 = hitbox.y1;
		//DEBUG
		/*std::cout << "hitboxTmp.y1 : " << std::setprecision(3) << hitboxTmp.y1
		<< ", lastHitbox.y1 : " << std::setprecision(3) << _lastHitbox.y1
		<< ", posCamera.y : " << std::setprecision(3) << posCamera.y
		<< ", - : " << std::setprecision(1) << hitbox.y1 - _lastHitbox.y1 << std::endl;*/

		if (!_isHitboxSet)
		{
			_isHitboxSet = true;
			_lastHitbox = hitbox;
		}
		if (hitbox.x1 - _lastHitbox.x1 > 0) // si direction negative axe x
		{
			if (hitboxTmp.x1 > posCamera.x + 150 && _position.x + (_lastHitbox.x1 - hitbox.x1) > (_mapInfos.getMapWidth() * 40 - 800) * -1)
				_position.x += (_lastHitbox.x1 - hitbox.x1);
		}
		else
			if (hitbox.x1 - _lastHitbox.x1 < 0) // si direction positive axe x
			{
				if (hitboxTmp.x1 < posCamera.x + 150 && _position.x + (_lastHitbox.x1 - hitbox.x1) < 0)
					_position.x += (_lastHitbox.x1 - hitbox.x1);
			}
		if (hitbox.y1 - _lastHitbox.y1 > 0) // si direction negative axe y
		{
			if (hitboxTmp.y1 > posCamera.y + 400 && _position.y + (_lastHitbox.y1 - hitbox.y1) > (_mapInfos.getMapHeight() * 40 - 600) * -1)
				_position.y += (_lastHitbox.y1 - hitbox.y1);
		}
		else
			if (hitbox.y1 - _lastHitbox.y1 < 0) // si direction positive axe y
			{
				if (hitboxTmp.y1 < posCamera.y + 400 && _position.y + (_lastHitbox.y1 - hitbox.y1) < 0)
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