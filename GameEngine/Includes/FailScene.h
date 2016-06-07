#pragma once

#include "Scene.h"

namespace Moo
{
	class FailScene : public Scene
	{
	public:
		FailScene();
		~FailScene();
		void												clean();
		bool												init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture>);
		bool												runUpdate();

		std::string											_errorMessage;

	private:
		std::shared_ptr<Sprite>								_backgroundSprite;
		std::shared_ptr<Moo::Window>						_window;
		std::shared_ptr<std::map<std::string, Texture>>		_textures;
	};
}