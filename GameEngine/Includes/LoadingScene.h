#pragma once

#include "Scene.h"

namespace Moo
{
	class LoadingScene : public Scene
	{
	public:
		LoadingScene();
		~LoadingScene();
		void	clean();
		bool	init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture>);
		bool	runUpdate();

	private:
		std::shared_ptr<Sprite>		_animation;
		std::shared_ptr<Moo::Window> _window;
		std::shared_ptr<std::map<std::string, Texture>> _textures;
	};
}