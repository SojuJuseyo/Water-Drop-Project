#pragma once

#include <chrono>
#include <ctime>
#include "../Includes/WindowSettings.h"
#include "../Includes/Vector2f.h"
#include "../Includes/DynamicEntity.h"
#include "../Includes/Sprite.h"

namespace Moo
{
	class Character : public DynamicEntity
	{
	public:
		Character(Vector2f, float, std::shared_ptr<Sprite>, bool, float, EntityType);
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

	private:
		Vector2f		_characterVelocity;

		std::chrono::time_point<std::chrono::system_clock> _startingTime, _lastEvaporation;

		bool	_godMode;
	};
}