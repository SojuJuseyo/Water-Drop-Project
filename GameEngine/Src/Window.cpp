#include "Window.h"

namespace Moo
{
	Window::Window(HINSTANCE hInstance, WindowSettings &config)
	{
		_config = config;
		_fpsLimit = 60;
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
		while (Fps::getInstance().getFrameTime() <= 1.0f / _fpsLimit) {
			Fps::getInstance().update();
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
			if (msg.wParam == VK_ESCAPE) {
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
		float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
		d3d::getInstance().clearWindow(color);
		_devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void	Window::draw(Drawable *drawable)
	{
		drawable->draw();
	}

	void	Window::display()
	{
		d3d::getInstance().display();
		Fps::getInstance().reset(_fpsLimit);
	}

	void	Window::setFpsLimit(float limit)
	{
		_fpsLimit = limit;
	}

	float	Window::getFps()
	{
		return 1.0f / Fps::getInstance().getFrameTime();
	}
}