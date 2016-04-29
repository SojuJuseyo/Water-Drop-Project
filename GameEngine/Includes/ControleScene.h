#pragma once

#include "Scene.h"

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
		std::shared_ptr<Texture>	_backgroundTexture;
		std::shared_ptr<Sprite>		_backgroundSprite;
		std::shared_ptr<Moo::Window> _window;
	};
}