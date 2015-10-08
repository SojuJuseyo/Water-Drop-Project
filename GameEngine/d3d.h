#pragma once

#include "pch.h"
#include <windows.h>
#include <iostream>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

using namespace DirectX;

// global declarations
static IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
static ID3D11Device *dev;                     // the pointer to our Direct3D device interface
static ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
static ID3D11RenderTargetView *backbuffer;    // global declaration
static ID3D11InputLayout *pLayout;            // the pointer to the input layout
static ID3D11VertexShader *pVS;               // the pointer to the vertex shader
static ID3D11PixelShader *pPS;                // the pointer to the pixel shader
static ID3D11Buffer *pVBuffer;                // the pointer to the vertex buffer

struct VERTEX { XMFLOAT3 position; XMFLOAT4 color; };

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

static int g_i = 0;

namespace Moo
{
	class d3d
	{
	public:

		static XMFLOAT3 PointToNdc(int x, int y, float z)
		{
			XMFLOAT3 p;

			p.x = 2.0f*(float)x / SCREEN_WIDTH - 1.0f;
			p.y = 1.0f - 2.0f*(float)y / SCREEN_HEIGHT;
			p.z = z;

			return p;
		}

		static void InitD3D(HWND hWnd)
		{
			// create a struct to hold information about the swap chain
			DXGI_SWAP_CHAIN_DESC scd;

			// clear out the struct for use
			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

			// fill the swap chain description struct
			scd.BufferCount = 1;                                    // one back buffer
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
			scd.BufferDesc.Width = SCREEN_WIDTH;                    // set the back buffer width
			scd.BufferDesc.Height = SCREEN_HEIGHT;                  // set the back buffer height
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
			scd.OutputWindow = hWnd;                                // the window to be used
			scd.SampleDesc.Count = 4;                               // how many multisamples
			scd.Windowed = TRUE;                                    // windowed/full-screen mode
			scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

			// create a device, device context and swap chain using the information in the scd struct
			D3D11CreateDeviceAndSwapChain(NULL,
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

			// Set the viewport
			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = SCREEN_WIDTH;
			viewport.Height = SCREEN_HEIGHT;

			devcon->RSSetViewports(1, &viewport);

			initPipeline();
		}

		static void	initPipeline()
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
			};

			dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
			devcon->IASetInputLayout(pLayout);
		}

		// this is the function that cleans up Direct3D and COM
		static void CleanD3D()
		{
			swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode
		}
	};
}