#include "Transformable.h"

namespace Moo
{
	Transformable::Transformable() : _position(0, 0), _scale(1, 1), _rotation(0), _origin(0, 0)
	{

	}
	Transformable::~Transformable()
	{
	}
	void Transformable::setPosition(float x, float y)
	{
		_position = Vector2f(x, y);
	}
	void Transformable::setPosition(const Vector2f & position)
	{
		_position = position;
	}
	void Transformable::setRotation(float angle)
	{
		_rotation = angle;
	}
	void Transformable::setScale(float factorX, float factorY)
	{
		_scale = Vector2f(factorX, factorY);
	}
	void Transformable::setScale(const Vector2f & factors)
	{
		_scale = factors;
	}
	void Transformable::setOrigin(float x, float y)
	{
		_origin = Vector2f(x, y);
	}
	void Transformable::setOrigin(const Vector2f & origin)
	{
		_origin = origin;
	}
	const Vector2f & Transformable::getPosition() const
	{
		return _position;
	}
	float Transformable::getRotation() const
	{
		return _rotation;
	}
	const Vector2f & Transformable::getScale() const
	{
		return _scale;
	}
	const Vector2f & Transformable::getOrigin() const
	{
		return _origin;
	}
	void Transformable::move(float offsetX, float offsetY)
	{
		_position.x += offsetX;
		_position.y += offsetY;
	}
	void Transformable::move(const Vector2f & offset)
	{
		_position.x += offset.x;
		_position.y += offset.y;
	}
	void Transformable::rotate(float angle)
	{
		_rotation += angle;
	}
	void Transformable::scale(float factorX, float factorY)
	{
		_scale.x += factorX;
		_scale.y += factorY;
	}
	void Transformable::scale(const Vector2f & factor)
	{
		_scale.x += factor.x;
		_scale.y += factor.y;
	}
	void Transformable::setX(const float x)
	{
		_position.x = x;
	}
	void Transformable::setY(const float y)
	{
		_position.y = y;
	}
	float Transformable::getX() const
	{
		return _position.x;
	}
	float Transformable::getY() const
	{
		return _position.y;
	}
}