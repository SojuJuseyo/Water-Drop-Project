#pragma once
#include "Entity.h"
#include "Sprite.h"

namespace Moo
{
	class DynamicEntity : public Entity
	{
	public:
		DynamicEntity();
		virtual ~DynamicEntity() {};

		void	setGravity(bool);
		void	setVelocity(Vector2f);
		void	setMass(float);
		void	setHealth(float);

		bool			getGravity() const;
		Vector2f		getVelocity() const;
		float			getMass() const;
		float			getHealth() const;
		Sprite			*getSprite() const;
		Sprite			*getHitboxSprite() const;
		std::string		getName() const;

		HitZone	collisionAABB(Entity *entity);
		Hitbox	resetHitbox();

	protected:
		Vector2f	_velocity;
		float		_mass;
		float		_health;
		Vector2f	_acceleration;
		std::string	_name;
		bool		_hasGravity;

		Sprite			*_sprite;
		Sprite			*_hitboxSprite;
		Moo::Texture	*_texture;
	};
}
