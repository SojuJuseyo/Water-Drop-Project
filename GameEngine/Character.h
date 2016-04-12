#pragma once

#include "WindowSettings.h"
#include "Vector2f.h"
#include "Entity.h"
#include "Sprite.h"

#define MINIMUM_VELOCITY_Y	-270//-400
#define STANDARD_VELOCITY_X	5

namespace Moo
{
	class Character : public Entity
	{
	public:
		Character(Vector2f, float, Sprite *, bool);
		virtual ~Character();
		void	move(Direction);
		bool	jump(bool);
		void	update();
		void	resetPos();
		Hitbox	resetHitbox();
		HitZone	collisionAABB(Entity *entity);
		Sprite	*getSprite() const;
		Sprite  *getHitboxSprite() const;
		void	setHealth(int);
		int		getHealth() const;

		// CHEAT
		bool	isGodMode() const;
		void	setGodMode(bool);
		void	toggleGodMode();

	private:
		Sprite			*_sprite;
		Sprite			*_hitboxSprite;
		Moo::Texture	*_texture;

		// Health points
		int		_health;

		// CHEAT
		bool	_godMode;
	};
}