#pragma once

#include "Includes/Scene.h"

namespace Moo
{
	class ControleScene : public Scene
	{
	public:
		ControleScene();
		~ControleScene();
		void	clean();
		bool	init(std::shared_ptr<Moo::Window> window);
		bool	runUpdate();
	private:
		Moo::Texture *controleText;
		Moo::Sprite *controle;
		std::shared_ptr<Moo::Window> _window;
	};
}