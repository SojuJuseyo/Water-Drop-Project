#pragma once

#include "Text.h"
#include "Keyboard.h"
#include "Window.h"
#include "SoundSystem.h"

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
		virtual bool init(SoundSystem *) = 0;
		virtual bool run(Moo::Window &window) = 0;
		virtual void clean() = 0;
	};
}