#pragma once

namespace Moo
{
	typedef struct Hitbox
	{
		float x;
		float y;
	}			   Hitbox;

	class Entity
	{
	public:
		Entity();
		virtual ~Entity() {}

		void setVelocity(float);
		void setMass(float);
		void setHitbox(Hitbox);

		float getVelocity() const;
		float getMass() const;
		Hitbox getHitbox() const;
	protected:
		float	_velocity;
		float	_mass;
		Hitbox	_hitbox;
	};
}