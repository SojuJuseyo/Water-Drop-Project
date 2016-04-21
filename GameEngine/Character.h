#pragma once

#include <chrono>
#include <ctime>
#include "WindowSettings.h"
#include "Vector2f.h"
#include "Entity.h"
#include "Sprite.h"

#define MINIMUM_VELOCITY_Y	-270//-400
#define STANDARD_VELOCITY_X	250
#define EVAPORATION_RATE	0.25 //per second

namespace Moo
{
	class Character : public Entity
	{
	public:
		Character(Vector2f, float, Sprite *, bool, float, bool);
		virtual ~Character();
		void	move(Direction);
		bool	jump(bool);
		void	update();
		void	resetPos();
		Hitbox	resetHitbox();
		HitZone	collisionAABB(Entity *entity);
		Sprite	*getSprite() const;
		Sprite  *getHitboxSprite() const;
		void	setHealth(float);
		float	getHealth() const;
		void	changeHealth(float);
		void	checkEvaporation();
		void	setTimers();
		void	setWallJumpVelocity(bool);

		// CHEAT
		bool	isGodMode() const;
		void	setGodMode(bool);
		void	toggleGodMode();

	private:
		Sprite			*_sprite;
		Sprite			*_hitboxSprite;
		Moo::Texture	*_texture;
		Vector2f		_playerVelocity;
		bool			_isPlayer;

		std::chrono::time_point<std::chrono::system_clock> _startingTime, _lastEvaporation;

		// Health points
		float		_health;

		// CHEAT
		bool	_godMode;
	};
}