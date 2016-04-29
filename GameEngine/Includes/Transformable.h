#pragma once

#include "Vector2f.h"

namespace Moo
{
	class Transformable
	{
	public:
		Transformable();
		virtual ~Transformable();

		void setPosition(float x, float y);
		void setPosition(const Vector2f& position);
		void setRotation(float angle);
		void setScale(float factorX, float factorY);
		void setScale(const Vector2f& factors);
		void setOrigin(float x, float y);
		void setOrigin(const Vector2f& origin);
		const Vector2f& getPosition() const;
		float getRotation() const;
		const Vector2f& getScale() const;
		const Vector2f& getOrigin() const;
		void move(float offsetX, float offsetY);
		void move(const Vector2f& offset);
		void rotate(float angle);
		void scale(float factorX, float factorY);
		void scale(const Vector2f& factor);
		void setX(const float x);
		void setY(const float y);
		float getX() const;
		float getY() const;

	private:
		Vector2f _position;
		Vector2f _scale;
		Vector2f _origin;
		float _rotation;
	};
}