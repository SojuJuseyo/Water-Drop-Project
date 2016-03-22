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
			release();
		}

		void d3d::init(HWND hWnd, Vector2f screenSize)
		{
			DXGI_SWAP_CHAIN_DESC scd;

			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
			_screenSize = screenSize;

			scd.BufferCount = 1;
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			scd.BufferDesc.Width = (int)_screenSize.x;
			scd.BufferDesc.Height = (int)_screenSize.y;
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			scd.OutputWindow = hWnd;
			scd.SampleDesc.Count = 4;
			scd.Windowed = TRUE;
			//scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			HRESULT hresult = D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				//D3D11_CREATE_DEVICE_DEBUG,
				NULL,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&scd,
				&swapchain,
				&dev,
				NULL,
				&devcon);

			// get the address of the back buffer
			ID3D11Texture2D *pBackBuffer;
			swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			// use the back buffer address to create the render target
			dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
			pBackBuffer->Release();

			// set the render target as the back buffer
			devcon->OMSetRenderTargets(1, &backbuffer, NULL);

			_camera = new Camera;
			_fullscreenstate = true;
		}

		void	d3d::setViewPort()
		{
			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = _screenSize.x;
			viewport.Height = _screenSize.y;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;

			devcon->RSSetViewports(1, &viewport);
		}

		Camera		*d3d::getCamera()
		{
			return _camera;
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

		void d3d::release()
		{
			if (swapchain != nullptr) {
				swapchain->SetFullscreenState(FALSE, NULL);
				swapchain->Release();
			}
			if (backbuffer != nullptr) {
				backbuffer->Release();
			}
			if (devcon != nullptr) {
				devcon->Release();
			}
			if (dev != nullptr) {
				dev->Release();
			}
		}

		void d3d::display()
		{
			swapchain->Present(0, 0);
		}

		void d3d::setFullScreen()
		{
			_fullscreenstate = !_fullscreenstate;
			swapchain->SetFullscreenState(_fullscreenstate, NULL);
		}

		void d3d::setFullScreenState(bool state)
		{
			swapchain->SetFullscreenState(state, NULL);
		}

		void d3d::clearWindow(const float* color)
		{
			devcon->ClearRenderTargetView(backbuffer, color);
		}
		
		ID3D11Device* d3d::getD3DDevice()
		{
			return dev;
		}

		ID3D11DeviceContext* d3d::getContext()
		{
			return devcon;
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
		ID3D11Device *dev;
		ID3D11DeviceContext *devcon;
		IDXGISwapChain *swapchain;
		ID3D11RenderTargetView *backbuffer;
		ID3D11InputLayout *pLayout;
		Vector2f _screenSize;
		Camera *_camera;
	};
}
