#pragma once
#include "Graphics.h"

class CGame
{
public:
	void Initialize();
	void InitGraphics();
	void InitPipeline();
	void Update();
	void Render();

private:
	ComPtr<ID3D11Device1> dev;              // the device interface
	ComPtr<ID3D11DeviceContext1> devcon;    // the device context interface
	ComPtr<IDXGISwapChain1> swapchain;      // the swap chain interface
	ComPtr<ID3D11RenderTargetView> rendertarget;
	ComPtr<ID3D11Buffer> vertexbuffer;
	ComPtr<ID3D11InputLayout> inputlayout;    // the input layout interface
	ModelViewProjectionConstantBuffer		_constantBufferData;

	// active shaders
	ComPtr<ID3D11VertexShader> vertexshader;
	ComPtr<ID3D11PixelShader> pixelshader;
};
