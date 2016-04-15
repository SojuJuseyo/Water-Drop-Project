#pragma once

#include "Scene.h"
#include "Game.h"
#include "SoundSystem.h"

namespace Moo
{
	class ControleScene : public Scene
	{
	public:
		ControleScene();
		~ControleScene();
		bool	run(Moo::Window &window);
		void	clean();
		bool	init();
	private:
		std::shared_ptr<SoundSystem> soundSystem;
		Moo::Texture *controleText;
		Moo::Sprite *controle;
	};
}