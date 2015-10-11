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

// global declarations (NOTE: move them after the engine proof)
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

static int g_i = 0; // tmp player position

namespace Moo
{
	class d3d
	{
	public:
		// Transform 3D points to 2D points
		static XMFLOAT3 PointToNdc(int x, int y, float z);
		static void InitD3D(HWND hWnd);
		static void	initPipeline();
		static void CleanD3D();
	};
}
