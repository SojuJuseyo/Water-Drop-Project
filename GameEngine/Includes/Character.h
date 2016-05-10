#pragma once

#include <chrono>
#include <ctime>
#include "WindowSettings.h"
#include "Vector2f.h"
#include "DynamicEntity.h"
#include "Sprite.h"

namespace Moo
{
	class Character : public DynamicEntity
	{
	public:
		Character(Vector2f, float, std::shared_ptr<Sprite>, bool, float, EntityType, Direction);
		virtual ~Character();

		void	move(Direction);
		bool	jump(bool);
		void	update();
		HitZone	collisionAABB(Entity *entity);

		void	checkEvaporation();
		void	setTimers();
		void	setWallJumpVelocity(bool);

		// CHEAT
		bool	isGodMode() const;
		void	setGodMode(bool);
		void	toggleGodMode();

		void	reset();

	private:
		std::chrono::time_point<std::chrono::system_clock> _startingTime, _lastEvaporation;
		bool	_godMode;

		//Save variables
		Vector2f						_oldVelocity;
		float							_oldMass;
		float							_oldHealth;
		Vector2f						_oldAcceleration;
		bool							_oldHasGravity;
		Direction						_oldDirection;
		Hitbox							_oldHitbox;
		Vector2f						_oldSpritePosition;
		Vector2f						_oldSpriteScale;
		Vector2f						_oldHitboxSpritePosition;
		Vector2f						_oldHitboxSpriteScale;
	};
}