#pragma once

#include "Vector2f.h"

namespace Moo
{
	class Camera
	{
	public:
		Camera();
		~Camera();
		Vector2f getPosition() const;
		void setPosition(const Vector2f &);
		void move(const Vector2f &);
	private:
		Vector2f _position;
	};
}