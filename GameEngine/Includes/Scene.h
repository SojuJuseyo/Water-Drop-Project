#pragma once

#include "../Includes/Text.h"
#include "../Includes/Keyboard.h"
#include "../Includes/Window.h"

namespace Moo
{
	enum class TypeScene : int
	{
		MENU,
		LEVEL,
		PAUSE,
		CONTROLE,
		EXIT,
	};
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();
		virtual bool init(std::shared_ptr<Moo::Window> window) = 0;
		virtual bool runUpdate() = 0;
		virtual void clean() = 0;
	};
}