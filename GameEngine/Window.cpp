#include "Window.h"

namespace Moo
{
	Window::Window(HINSTANCE hInstance, WindowSettings &config)
	{
		_config = config;
		initialize(hInstance);
	}

	Window::~Window()
	{
		destroy();
	}

	void	Window::initialize(HINSTANCE hInstance)
	{
		WNDCLASSEX wc;
		int posX, posY;
		auto hinstance = GetModuleHandle(NULL);
		auto applicationName = "Engine";

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

		auto screenWidth = GetSystemMetrics(SM_CXSCREEN);
		auto screenHeight = GetSystemMetrics(SM_CYSCREEN);

		screenWidth = 800;
		screenHeight = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;


		_hwnd = CreateWindowEx(	//Create our Extended Window
			WS_EX_APPWINDOW,	//Extended style
			applicationName,	//Name of our windows class
			applicationName,	//Name in the title bar of our window
			WS_OVERLAPPEDWINDOW,	//style of our window
			posX, posY,	//Top left corner of window
			SCREEN_WIDTH, SCREEN_HEIGHT,    // set window to new resolution
			NULL,	//Handle to parent window
			NULL,	//Handle to a Menu
			hInstance,	//Specifies instance of current program
			NULL	//used for an MDI client window
			);

		ShowWindow(_hwnd, SW_SHOW);
		SetForegroundWindow(_hwnd);
		SetFocus(_hwnd);
		ShowCursor(true);
		Moo::d3d::InitD3D(_hwnd);
		return;
	}

	bool	Window::isOpen()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_CLICK)
			{
				_rectangles.push_back(new Moo::RectangleShape(100, 100, msg.wParam, msg.lParam, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)));
			}
			if (msg.message == WM_LEFT)
				if (g_i >= 0)
					g_i -= 10;
			if (msg.message == WM_RIGHT)
				if (g_i <= SCREEN_WIDTH - 100)
					g_i += 10;
			if (msg.message == WM_FULLSCREEN)
				swapchain->SetFullscreenState(TRUE, NULL);
			if (msg.message == WM_QUIT)
				return false;
		}
		return true;
	}

	void	Window::destroy()
	{
		ShowCursor(true);
		DestroyWindow(_hwnd);
		_hwnd = NULL;
		Moo::d3d::CleanD3D();
		return;
	}

	void	Window::clear()
	{
		float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
		devcon->ClearRenderTargetView(backbuffer, color);
	}

	void	Window::display()
	{
		// select which primtive type we are using
		devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// select which vertex buffer to display
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		std::vector<RectangleShape *> _rectangles2(_rectangles);
		_rectangles2.push_back(new Moo::RectangleShape(SCREEN_WIDTH, 100, 0, SCREEN_HEIGHT - 100, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)));
		_rectangles2.push_back(new Moo::RectangleShape(100, 100, g_i, SCREEN_HEIGHT - 200, XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)));

		for (auto rectangle : _rectangles2)
		{
			rectangle->draw(dev, devcon);
			devcon->IASetVertexBuffers(0, 1, rectangle->getVertexBuffer(), &stride, &offset);
			devcon->Draw(8, 0);
			rectangle->release();
		}
		_rectangles2.clear();
		swapchain->Present(0, 0);
	}
}