#pragma once

#include "Text.h"
#include "Keyboard.h"
#include "Window.h"

namespace Moo
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();
		virtual bool run(Moo::Window &window) = 0;
		virtual void clean() = 0;
	};
}