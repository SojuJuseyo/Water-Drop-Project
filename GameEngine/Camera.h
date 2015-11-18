#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

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