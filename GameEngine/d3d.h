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

		void d3d::init(HWND hWnd, Vector2f screenSize)
		{
			// create a struct to hold information about the swap chain
			DXGI_SWAP_CHAIN_DESC scd;

			// clear out the struct for use
			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
			_screenSize = screenSize;
			// fill the swap chain description struct
			scd.BufferCount = 1;                                    // one back buffer
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
			scd.BufferDesc.Width = (int)_screenSize.x;                    // set the back buffer width
			scd.BufferDesc.Height = (int)_screenSize.y;                  // set the back buffer height
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
			scd.OutputWindow = hWnd;                                // the window to be used
			scd.SampleDesc.Count = 4;                               // how many multisamples
			scd.Windowed = TRUE;                                    // windowed/full-screen mode
			//scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

											// create a device, device context and swap chain using the information in the scd struct
			HRESULT hresult = D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				D3D11_CREATE_DEVICE_DEBUG,
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

		XMMATRIX	d3d::getView()
		{
			return DirectX::XMMatrixIdentity();
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

		void	d3d::initPipeline()
		{
			// load and compile the two shaders
			ID3D10Blob *VS, *PS;

			D3DX11CompileFromFile("shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
			D3DX11CompileFromFile("shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

			// encapsulate both shaders into shader objects
			dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
			dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

			// set the shader objects
			devcon->VSSetShader(pVS, 0, 0);
			devcon->PSSetShader(pPS, 0, 0);

			// create the input layout object
			D3D11_INPUT_ELEMENT_DESC ied[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
			devcon->IASetInputLayout(pLayout);
		}

		d3d::~d3d()
		{

		}

		void d3d::release()
		{
			swapchain->SetFullscreenState(FALSE, NULL);
			swapchain->Release();
			//pPS->Release();
			//pVS->Release();
			//pLayout->Release();
			backbuffer->Release();
			devcon->Release();
			dev->Release();
		}

		void d3d::display()
		{
			swapchain->Present(0, 0);
		}

		void d3d::setFullScreen(bool value)
		{
			swapchain->SetFullscreenState(value, NULL);
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

		ID3D11Device *dev;
		ID3D11DeviceContext *devcon;
		IDXGISwapChain *swapchain;
		ID3D11RenderTargetView *backbuffer;
		ID3D11InputLayout *pLayout;
		ID3D11VertexShader *pVS;
		ID3D11PixelShader *pPS;
		Vector2f _screenSize;
	};
}
