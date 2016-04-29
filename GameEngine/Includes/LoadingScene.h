#pragma once

#include "../Includes/Scene.h"

namespace Moo
{
	class LoadingScene : public Scene
	{
	public:
		LoadingScene();
		~LoadingScene();
		void	clean();
		bool	init(std::shared_ptr<Moo::Window> window);
		bool	runUpdate();

	private:
		std::shared_ptr<Texture>	_backgroundTexture;
		std::shared_ptr<Sprite>		_backgroundSprite;
		std::shared_ptr<Moo::Window> _window;
	};
}