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
		~Entity();

		void setVelocity(float);
		void setMass(float);
		void setHitbox(Hitbox);

		float getVelocity() const;
		float getMass() const;
		Hitbox getHitbox() const;
	private:
		float	_velocity;
		float	_mass;
		Hitbox	_hitbox;
	};
}