#pragma once

#include "Includes/WindowSettings.h"
#include "Includes/Entity.h"
#include "Includes/Sprite.h"

#define	GRAVITY					135//200
#define	JUMP_VELOCITY			500//750
#define MINIMUM_VELOCITY_Y		-270//-400
#define STANDARD_VELOCITY_X		250

namespace Moo
{
	class DynamicEntity : public Entity
	{
	public:
		DynamicEntity();
		virtual ~DynamicEntity() {};

		void			setGravity(bool);
		void			setVelocity(Vector2f);
		void			setMass(float);
		void			setHealth(float);

		bool			getGravity() const;
		Vector2f		getVelocity() const;
		float			getMass() const;
		float			getHealth() const;
		Sprite			*getSprite() const;
		Sprite			*getHitboxSprite();

		HitZone			collisionAABB(Entity *entity);
		Hitbox			resetHitbox();
		void			resetPos();

	protected:
		Vector2f					_velocity;
		float						_mass;
		float						_health;
		Vector2f					_acceleration;
		bool						_hasGravity;

		std::shared_ptr<Sprite>		_sprite;
		std::shared_ptr<Sprite>		_hitboxSprite;
		std::shared_ptr<Texture>	_texture;
	};
}
