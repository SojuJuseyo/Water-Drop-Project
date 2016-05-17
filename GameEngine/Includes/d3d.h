#pragma once

#include "pch.h"
#include <windows.h>
#include <iostream>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

struct VERTEX { XMFLOAT3 position; XMFLOAT4 color; XMFLOAT2 texture; };

#include "Vector2f.h"
#include "Camera.h"

namespace Moo
{
	class d3d
	{
	public:
		// Transform 3D points to 2D points
		static XMFLOAT3 d3d::PointToNdc(int x, int y, float z)
		{
			XMFLOAT3 p;

			p.x = 2.0f*(float)x / d3d::getInstance().getScreenSize().x - 1.0f;
			p.y = 1.0f - 2.0f*(float)y / d3d::getInstance().getScreenSize().y;
			p.z = z;

			return p;
		}

		d3d::d3d()
		{

		}

		d3d::~d3d()
		{
			releaseBackBuffer();
		}

		void d3d::releaseBackBuffer()
		{
			_renderTarget.Reset();
			_backBuffer.Reset();
		}

		void d3d::init(HWND hWnd, Vector2f screenSize)
		{
			D3D_FEATURE_LEVEL levels[] = {
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0
			};

			UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
			//deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
			_screenSize = screenSize;

			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferCount = 1;
			sd.BufferDesc.Width = (UINT)_screenSize.x;
			sd.BufferDesc.Height = (UINT)_screenSize.y;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator = 0;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow = hWnd;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.Windowed = TRUE;
			sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			HRESULT hresult = D3D11CreateDeviceAndSwapChain(
				nullptr,
				D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_WARP,
				nullptr,
				deviceFlags,
				levels,
				ARRAYSIZE(levels),
				D3D11_SDK_VERSION,
				&sd,
				_swapchain.GetAddressOf(),
				_dev.GetAddressOf(),
				&_featureLevel,
				_devcon.GetAddressOf()
				);

			_camera = std::make_unique<Camera>();
			setFullScreenState(false);
		}

		void d3d::configureBackBuffer()
		{
			// get the address of the back buffer
			_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)_backBuffer.GetAddressOf());

			// use the back buffer address to create the render target
			_dev->CreateRenderTargetView(_backBuffer.Get(), nullptr, _renderTarget.GetAddressOf());

			// set the render target as the back buffer
			_devcon->OMSetRenderTargets(1, _renderTarget.GetAddressOf(), NULL);

			setViewPort();
		}

		void	d3d::setViewPort()
		{
			_backBuffer->GetDesc(&_bbDesc);

			ZeroMemory(&_viewport, sizeof(D3D11_VIEWPORT));
			_viewport.Height = (float)_bbDesc.Height;
			_viewport.Width = (float)_bbDesc.Width;
			_viewport.MinDepth = 0;
			_viewport.MaxDepth = 1;

			_devcon->RSSetViewports(
				1,
				&_viewport
				);
		}

		Camera		*d3d::getCamera()
		{
			return _camera.get();
		}

		XMMATRIX	d3d::getView()
		{
			return
				DirectX::XMMatrixMultiply(
					DirectX::XMMatrixIdentity(),
					DirectX::XMMatrixTranslationFromVector(
						XMVectorSet(
							_camera->getPosition().x,
							_camera->getPosition().y,
							0,
							0
							)
						)
					);
		}

		XMMATRIX	d3d::getProjection()
		{
			return
				DirectX::XMMatrixOrthographicOffCenterLH(
					0.0f,
					(float)d3d::getInstance().getScreenSize().x,
					0.0f,
					(float)d3d::getInstance().getScreenSize().y,
					0.0f,
					100.0f);
		}

		Vector2f	d3d::getScreenSize() const
		{
			return _screenSize;
		}

		void d3d::display()
		{
			_swapchain->Present(1, 0);
		}

		void d3d::setFullScreenState(bool state)
		{
			releaseBackBuffer();

			UINT windowWidth = _fullscreenstate ? 1920 : 0;
			UINT windowHeight = _fullscreenstate ? 1080 : 0;

			_swapchain->ResizeBuffers(0, windowWidth, windowHeight, DXGI_FORMAT_UNKNOWN, 0);

			_swapchain->SetFullscreenState(state, NULL);

			configureBackBuffer();
		}

		void d3d::clearWindow(const float* color)
		{
			_devcon->ClearRenderTargetView(_renderTarget.Get(), color);
		}

		ComPtr<ID3D11Device> d3d::getD3DDevice()
		{
			return _dev;
		}

		ComPtr<ID3D11DeviceContext> d3d::getContext()
		{
			return _devcon;
		}

		static d3d& d3d::getInstance()
		{
			static d3d instance;
			return instance;
		}

	private:
		d3d(d3d const&) = delete;
		void operator=(d3d const&) = delete;

		bool _fullscreenstate;

		Vector2f _screenSize;
		std::unique_ptr<Camera> _camera;


		//-----------------------------------------------------------------------------
		// Direct3D device
		//-----------------------------------------------------------------------------
		ComPtr<ID3D11Device>        _dev;
		ComPtr<ID3D11DeviceContext> _devcon;
		ComPtr<IDXGISwapChain>      _swapchain;


		//-----------------------------------------------------------------------------
		// DXGI swap chain device resources
		//-----------------------------------------------------------------------------
		ComPtr <ID3D11Texture2D>        _backBuffer;
		ComPtr <ID3D11RenderTargetView> _renderTarget;

		//-----------------------------------------------------------------------------
		// Direct3D device metadata and device resource metadata
		//-----------------------------------------------------------------------------
		D3D_FEATURE_LEVEL       _featureLevel;
		D3D11_TEXTURE2D_DESC    _bbDesc;
		D3D11_VIEWPORT          _viewport;
	};
}
