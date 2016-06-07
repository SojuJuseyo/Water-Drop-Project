#include "SettingsScreen.h"

namespace Moo
{
	SettingsScreen::SettingsScreen() {}

	SettingsScreen::~SettingsScreen() {}

	void	SettingsScreen::addSprite(std::string name, std::string filename, float width, float height, float x, float y, float divider)
	{
		_sprites[name] = std::make_shared<Sprite>(width, height, x, y);
		_sprites[name]->loadTexture(&_textures.get()->at(filename));
		_sprites[name]->setX(d3d::getInstance().getScreenSize().x / divider - _sprites[name]->getWidth() / 2);
	}

	bool	SettingsScreen::init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture> textures)
	{
		_window = window;
		_textures = std::make_shared<std::map<std::string, Texture>>(textures);

		//background
		_sprites["Background"] = std::make_shared<Moo::Sprite>(800.f, 600.f, 0.f, 0.f);
		_sprites["Background"]->loadTexture(&_textures.get()->at("Settings_Background"));

		//Buttons attributes
		float spaceBetweenButtons = 30;

		//Title
		addSprite("Title", "Settings_Title", 395.f, 55.f, 0.f, d3d::getInstance().getScreenSize().y / 10 * 8, 2.f);

		//Buttons related to Fullscreen
		addSprite("Fullscreen", "Settings_Fullscreen", 243.f, 33.f, 0.f, d3d::getInstance().getScreenSize().y / 10 * 6, 3);
		addSprite("Fullscreen_On", "Settings_Fullscreen_On", 246.f, 36.f, 0.f, _sprites["Fullscreen"]->getY(), 3);
		addSprite("Fullscreen_State_On", "Settings_Checkbox_Checked", 36.f, 36.f, 0.f, _sprites["Fullscreen"]->getY(), 1.6f);
		addSprite("Fullscreen_State_Off", "Settings_Checkbox_Unchecked", 36.f, 36.f, 0.f, _sprites["Fullscreen"]->getY(), 1.6f);
		_sprites["Fullscreen_Current"] = _sprites["Fullscreen"];
		_fullscreenOn = false;
		_sprites["Fullscreen_State"] = _sprites["Fullscreen_State_Off"];

		//Buttons related to Music
		addSprite("Music", "Settings_Music", 123.f, 33.f, 0.f, _sprites["Fullscreen"]->getY() - _sprites["Fullscreen"]->getHeight() - spaceBetweenButtons, 3);
		addSprite("Music_On", "Settings_Music_On", 124.f, 36.f, 0.f, _sprites["Music"]->getY(), 3);
		addSprite("Music_State_On", "Settings_Checkbox_Checked", 36.f, 36.f, 0.f, _sprites["Music"]->getY(), 1.6f);
		addSprite("Music_State_Off", "Settings_Checkbox_Unchecked", 36.f, 36.f, 0.f, _sprites["Music"]->getY(), 1.6f);
		_sprites["Music_Current"] = _sprites["Music"];
		_musicOn = true;
		_sprites["Music_State"] = _sprites["Music_State_On"];

		//Buttons related to SoundEffects
		addSprite("Sound_Effects", "Settings_Sound_Effects", 301.f, 33.f, 0.f, _sprites["Music"]->getY() - _sprites["Music"]->getHeight() - spaceBetweenButtons, 3);
		addSprite("Sound_Effects_On", "Settings_Sound_Effects_On", 303.f, 36.f, 0.f, _sprites["Sound_Effects"]->getY(), 3);
		addSprite("Sound_Effects_State_On", "Settings_Checkbox_Checked", 36.f, 36.f, 0.f, _sprites["Sound_Effects"]->getY(), 1.6f);
		addSprite("Sound_Effects_State_Off", "Settings_Checkbox_Unchecked", 36.f, 36.f, 0.f, _sprites["Sound_Effects"]->getY(), 1.6f);
		_sprites["Sound_Effects_Current"] = _sprites["Sound_Effects"];
		_soundEffectsOn = true;
		_sprites["Sound_Effects_State"] = _sprites["Sound_Effects_State_On"];

		//Buttons related to Back
		addSprite("Back", "Settings_Back", 129.f, 42.f, 0.f, _sprites["Sound_Effects"]->getY() - _sprites["Sound_Effects"]->getHeight() - spaceBetweenButtons * 3, 5);
		addSprite("Back_On", "Settings_Back_On", 161.f, 54.f, 0.f, _sprites["Back"]->getY(), 5);
		_sprites["Back_Current"] = _sprites["Back"];

		//Buttons related to Save
		addSprite("Save", "Settings_Save", 129.f, 42.f, 0.f, _sprites["Back"]->getY(), 1.25);
		addSprite("Save_On", "Settings_Save_On", 161.f, 54.f, 0.f, _sprites["Back"]->getY(), 1.25);
		_sprites["Save_Current"] = _sprites["Save"];

		//Init the position of the cursor
		_offset = e_settings::FULLSCREEN;
		_sprites["Fullscreen_Current"] = _sprites["Fullscreen_On"];

		return true;
	}

	bool	SettingsScreen::runUpdate()
	{
		Moo::Keyboard::updateInput();

		if (Moo::Keyboard::isDown(Keyboard::Enter))
			switch (_offset)
			{
			case e_settings::FULLSCREEN:
				if (_fullscreenOn == true)
				{
					_fullscreenOn = false;
					_sprites["Fullscreen_State"] = _sprites["Fullscreen_State_Off"];
				}
				else
				{
					_fullscreenOn = true;
					_sprites["Fullscreen_State"] = _sprites["Fullscreen_State_On"];
				}
				break;
			case e_settings::MUSIC:
				if (_musicOn == true)
				{
					_musicOn = false;
					_sprites["Music_State"] = _sprites["Music_State_Off"];
				}
				else
				{
					_musicOn = true;
					_sprites["Music_State"] = _sprites["Music_State_On"];
				}
				break;
			case e_settings::SOUND_EFFECTS:
				if (_soundEffectsOn == true)
				{
					_soundEffectsOn = false;
					_sprites["Sound_Effects_State"] = _sprites["Sound_Effects_State_Off"];
				}
				else
				{
					_soundEffectsOn = true;
					_sprites["Sound_Effects_State"] = _sprites["Sound_Effects_State_On"];
				}
				break;
			case e_settings::BACK:
				//Reset settings
				Game::getInstance().backToPrevScene();
				return true;
				break;
			case e_settings::SAVE:
				saveSettings();
				Game::getInstance().backToPrevScene();
				return true;
				break;
			}

		if (Keyboard::isDown(Keyboard::Up))
		{
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_settings::FULLSCREEN:
				_sprites["Fullscreen_Current"] = _sprites["Fullscreen"];
				_sprites["Back_Current"] = _sprites["Back_On"];
				_offset = e_settings::BACK;
				break;
			case e_settings::MUSIC:
				_sprites["Music_Current"] = _sprites["Music"];
				_sprites["Fullscreen_Current"] = _sprites["Fullscreen_On"];
				_offset = e_settings::FULLSCREEN;
				break;
			case e_settings::SOUND_EFFECTS:
				_sprites["Sound_Effects_Current"] = _sprites["Sound_Effects"];
				_sprites["Music_Current"] = _sprites["Music_On"];
				_offset = e_settings::MUSIC;
				break;
			case e_settings::BACK:
				_sprites["Back_Current"] = _sprites["Back"];
				_sprites["Sound_Effects_Current"] = _sprites["Sound_Effects_On"];
				_offset = e_settings::SOUND_EFFECTS;
				break;
			case e_settings::SAVE:
				_sprites["Save_Current"] = _sprites["Save"];
				_sprites["Sound_Effects_Current"] = _sprites["Sound_Effects_On"];
				_offset = e_settings::SOUND_EFFECTS;
				break;
			}
		}
		else if (Keyboard::isDown(Keyboard::Down))
		{
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_settings::FULLSCREEN:
				_sprites["Fullscreen_Current"] = _sprites["Fullscreen"];
				_sprites["Music_Current"] = _sprites["Music_On"];
				_offset = e_settings::MUSIC;
				break;
			case e_settings::MUSIC:
				_sprites["Music_Current"] = _sprites["Music"];
				_sprites["Sound_Effects_Current"] = _sprites["Sound_Effects_On"];
				_offset = e_settings::SOUND_EFFECTS;
				break;
			case e_settings::SOUND_EFFECTS:
				_sprites["Sound_Effects_Current"] = _sprites["Sound_Effects"];
				_sprites["Back_Current"] = _sprites["Back_On"];
				_offset = e_settings::BACK;
				break;
			case e_settings::BACK:
				_sprites["Back_Current"] = _sprites["Back"];
				_sprites["Fullscreen_Current"] = _sprites["Fullscreen_On"];
				_offset = e_settings::FULLSCREEN;
				break;
			case e_settings::SAVE:
				_sprites["Save_Current"] = _sprites["Save"];
				_sprites["Fullscreen_Current"] = _sprites["Fullscreen_On"];
				_offset = e_settings::FULLSCREEN;
				break;
			}
		}
		else if (Keyboard::isDown(Keyboard::Right))
		{
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_settings::FULLSCREEN:
				break;
			case e_settings::MUSIC:
				break;
			case e_settings::SOUND_EFFECTS:
				break;
			case e_settings::BACK:
				_sprites["Back_Current"] = _sprites["Back"];
				_sprites["Save_Current"] = _sprites["Save_On"];
				_offset = e_settings::SAVE;
				break;
			case e_settings::SAVE:
				break;
			}
		}
		else if (Keyboard::isDown(Keyboard::Left))
		{
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_settings::FULLSCREEN:
				break;
			case e_settings::MUSIC:
				break;
			case e_settings::SOUND_EFFECTS:
				break;
			case e_settings::BACK:
				break;
			case e_settings::SAVE:
				_sprites["Save_Current"] = _sprites["Save"];
				_sprites["Back_Current"] = _sprites["Back_On"];
				_offset = e_settings::BACK;
				break;
			}
		}

		_window->clear();
		_window->draw(_sprites["Background"].get());
		_window->draw(_sprites["Title"].get());

		_window->draw(_sprites["Fullscreen_Current"].get());
		_window->draw(_sprites["Fullscreen_State"].get());

		_window->draw(_sprites["Music_Current"].get());
		_window->draw(_sprites["Music_State"].get());

		_window->draw(_sprites["Sound_Effects_Current"].get());
		_window->draw(_sprites["Sound_Effects_State"].get());

		_window->draw(_sprites["Back_Current"].get());
		_window->draw(_sprites["Save_Current"].get());
		_window->display();

		return true;
	}

	void	SettingsScreen::saveSettings()
	{
		if (_fullscreenOn == true)
			d3d::getInstance().setFullScreenState(true);
		else
			d3d::getInstance().setFullScreenState(false);

		if (_musicOn == true)
			Game::getInstance().getSoundSystem()->unmuteBackgroundVolume();
		else
			Game::getInstance().getSoundSystem()->muteBackgroundVolume();

		if (_soundEffectsOn == true)
			Game::getInstance().getSoundSystem()->unmuteVolume();
		else
			Game::getInstance().getSoundSystem()->muteVolume();
	}

	void	SettingsScreen::clean() {}
}