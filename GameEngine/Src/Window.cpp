#include "GameManagmentHeader.h"

namespace Moo
{
	Window::Window(HINSTANCE hInstance, WindowSettings &config)
	{
		_config = config;
		initialize(hInstance);
	}

	Window::~Window()
	{
	}

	void	Window::initialize(HINSTANCE hInstance)
	{
		WNDCLASSEX wc;
		int posX, posY;
		auto hinstance = GetModuleHandle(NULL);
		auto applicationName = _config.getTitle().c_str();

		// Setup the windows class with default settings.
		wc.cbSize = sizeof(WNDCLASSEX);	//Size of our windows class
		wc.style = CS_HREDRAW | CS_VREDRAW;	//class styles
		wc.lpfnWndProc = WindowProc;	//Default windows procedure function
		wc.cbClsExtra = NULL;	//Extra bytes after our wc structure
		wc.cbWndExtra = NULL;	//Extra bytes after our windows instance
		wc.hInstance = hInstance;	//Instance to current application
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);	//Title bar Icon
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//Default mouse Icon
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);	//Window bg color
		wc.lpszMenuName = NULL;	//Name of the menu attached to our window
		wc.lpszClassName = applicationName;	//Name of our windows class
		wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); //Icon in your taskbar

		RegisterClassEx(&wc);

		posX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)_config.getScreenSize().x) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)_config.getScreenSize().y) / 2;

		_hwnd = CreateWindowEx(	//Create our Extended Window
			WS_EX_APPWINDOW,	//Extended style
			applicationName,	//Name of our windows class
			applicationName,	//Name in the title bar of our window
			WS_OVERLAPPEDWINDOW,	//style of our window
			posX, posY,	//Top left corner of window
			(UINT)_config.getScreenSize().x, (UINT)_config.getScreenSize().y,    // set window to new resolution
			NULL,	//Handle to parent window
			NULL,	//Handle to a Menu
			hInstance,	//Specifies instance of current program
			NULL	//used for an MDI client window
			);

		ShowWindow(_hwnd, SW_SHOW);
		SetForegroundWindow(_hwnd);
		SetFocus(_hwnd);
		ShowCursor(false);
		d3d::getInstance().init(_hwnd, Vector2f(_config.getScreenSize().x, _config.getScreenSize().y));
		_dev = d3d::getInstance().getD3DDevice();
		_devcon = d3d::getInstance().getContext();
		return;
	}

	bool	Window::isOpen()
	{
		while (_fps.getFrameTime() <= 1.0f / _fpsLimit) {
			_fps.update();
		}
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.wParam == VK_F1) {
				d3d::getInstance().setFullScreenState(true);
			}
			if (msg.wParam == VK_F2) {
				d3d::getInstance().setFullScreenState(false);
			}
			/*
			if (msg.wParam == VK_ESCAPE) {
				// escape
				std::cout << "VK_ESCAPE handled" << std::endl;
				Moo::Game::getInstance().backToPrevScene();
			}
			*/
			if (msg.message == WM_PAUSEGAME) {
				Keyboard::getInstance().focused = false;
				if (Moo::Game::getInstance()._currentScene->sceneType == Moo::Game::LEVEL) {
					Moo::Game::getInstance().runScene(Moo::Game::PAUSE_MENU, true);
				}
				if (Game::getInstance().getSceneByType(Moo::Game::LEVEL) != nullptr &&
					((LevelScene *)(Game::getInstance().getSceneByType(Moo::Game::LEVEL)->scene))->themeChan != nullptr)
					((LevelScene *)(Game::getInstance().getSceneByType(Moo::Game::LEVEL)->scene))->themeChan->setPaused(true);
			}
			if (msg.message == WM_UNPAUSEGAME) {
				Keyboard::getInstance().focused = true;
				if (Game::getInstance().getSceneByType(Moo::Game::LEVEL) != nullptr &&
					((LevelScene *)(Game::getInstance().getSceneByType(Moo::Game::LEVEL)->scene))->themeChan != nullptr)
					((LevelScene *)(Game::getInstance().getSceneByType(Moo::Game::LEVEL)->scene))->themeChan->setPaused(false);
			}
			if (msg.message == WM_QUIT) {
				// croix
				Moo::Game::getInstance().exit();
				return false;
			}
		}
		return true;
	}

	void	Window::destroy()
	{
		ShowCursor(true);
		DestroyWindow(_hwnd);
		_hwnd = NULL;
		return;
	}

	void	Window::clear()
	{
		float color[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
		d3d::getInstance().clearWindow(color);
	}

	void	Window::draw(Drawable *drawable)
	{
		drawable->draw();
	}

	void	Window::inCameradraw(Sprite *sprite)
	{
		Vector2f savePos = sprite->getPosition();
		sprite->setPosition(Moo::Vector2f(sprite->getPosition().x + (d3d::getInstance().getCamera()->getPosition().x * -1), sprite->getPosition().y + (d3d::getInstance().getCamera()->getPosition().y * -1)));
		sprite->draw();
		sprite->setPosition(savePos);
	}

	void	Window::inCameradraw(Text *text)
	{
		Vector2f savePos = text->getPosition();
		text->setPosition(Moo::Vector2f(text->getPosition().x + (d3d::getInstance().getCamera()->getPosition().x * -1), text->getPosition().y + (d3d::getInstance().getCamera()->getPosition().y * -1)));
		text->draw();
		text->setPosition(savePos);
	}

	void	Window::display()
	{
		d3d::getInstance().display();
		_fps.reset(_fpsLimit);
	}

	void	Window::setFpsLimit(float limit)
	{
		_fpsLimit = limit;
	}

	float	Window::getFps()
	{
		return 1.0f / _fps.getFrameTime();
	}
}