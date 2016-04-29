#include "../Includes/Camera.h"
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
			if (hitboxTmp.x1 > posCamera.x + 150 && _position.x + (_lastHitbox.x1 - hitbox.x1) > (float)((_mapInfos.getMapWidth() * 40 - 800) * -1))
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
			if (hitboxTmp.y1 > posCamera.y + 400 && _position.y + (_lastHitbox.y1 - hitbox.y1) > (float)((_mapInfos.getMapHeight() * 40 - 600) * -1))
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