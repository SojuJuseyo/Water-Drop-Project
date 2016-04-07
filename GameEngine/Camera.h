#pragma once

#include "Vector2f.h"
#include "Entity.h"

namespace Moo
{
	class Camera
	{
	public:
		Camera();
		~Camera();
		Vector2f getPosition() const;
		void setPosition(const Vector2f &);
		void reset();
		void update(Hitbox);
		void move(const Vector2f &);
	private:
		Vector2f _position;
		Hitbox _lastHitbox;
		bool _isHitboxSet;
	};
}