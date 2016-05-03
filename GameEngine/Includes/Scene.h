#pragma once

#include "Keyboard.h"
#include "Window.h"

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
		bool _hasBeenInited = false;
	};
}