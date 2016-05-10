#pragma once

#include "Vector2f.h"
#include "Entity.h"
#include "MapInfos.h"
#include <memory>

namespace Moo
{
	class Camera
	{
	public:
		Camera();
		~Camera();
		Vector2f getPosition() const;
		void setPosition(const Vector2f &);
		void setInfoMap(std::shared_ptr<MapInfos>);
		void reset();
		void resetToPlayer(Hitbox);
		void update(Hitbox);
		void move(const Vector2f &);
	private:
		Vector2f _position;
		Hitbox _lastHitbox;
		bool _isHitboxSet;
		std::shared_ptr<MapInfos> _mapInfos;
	};
}