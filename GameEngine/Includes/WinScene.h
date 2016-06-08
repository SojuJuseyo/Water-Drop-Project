#pragma once

#include "Scene.h"
#include "Game.h"
#include "Font.h"

namespace Moo
{
	class WinScene : public Scene
	{
	public:
		WinScene();
		~WinScene();
		void	clean();
		bool	init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture>);
		bool	runUpdate();

	private:
		std::shared_ptr<Sprite>		_backgroundSprite;
		std::shared_ptr<Moo::Window> _window;
		std::shared_ptr<std::map<std::string, Texture>> _textures;
		std::shared_ptr<Moo::Font> _font;
		std::shared_ptr<Moo::Text> _time;
		std::string	_endTime;
	};
}