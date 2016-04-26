#pragma once

#include <chrono>
#include <ctime>
#include "WindowSettings.h"
#include "Vector2f.h"
#include "DynamicEntity.h"
#include "Sprite.h"

#define MINIMUM_VELOCITY_Y	-270//-400
#define STANDARD_VELOCITY_X	250
#define EVAPORATION_RATE	0.25 //per second

namespace Moo
{
	class Character : public DynamicEntity
	{
	public:
		Character(Vector2f, float, Sprite *, bool, float, EntityType, std::string);
		virtual ~Character();

		void	move(Direction);
		bool	jump(bool);
		void	update();
		void	resetPos();
		HitZone	collisionAABB(Entity *entity);

		void	changeHealth(float);
		void	checkEvaporation();
		void	setTimers();
		void	setWallJumpVelocity(bool);

		// CHEAT
		bool	isGodMode() const;
		void	setGodMode(bool);
		void	toggleGodMode();

	private:
		Vector2f		_characterVelocity;

		std::chrono::time_point<std::chrono::system_clock> _startingTime, _lastEvaporation;

		bool	_godMode;
	};
}