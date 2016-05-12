#include "Texture.h"

namespace Moo
{
	Texture::Texture() :
		solidColorVS(0), solidColorPS(0),
		inputLayout(0),
		colorMap(0), colorMapSampler(0), alphaBlendState(0)
	{
		_dev = d3d::getInstance().getD3DDevice();
		_devcon = d3d::getInstance().getContext();
		_textureHeight = 0;
		_textureWidth = 0;
	}

	Texture::~Texture()
	{
		release();
	}

	bool Texture::CompileD3DShader(char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer)
	{
		D3DX11CompileFromFile(filePath, 0, 0, entry, shaderModel,
			NULL, 0, 0, buffer, NULL, 0);
		return true;
	}

	void Texture::loadFromFile(const std::string &filename)
	{
		ID3DBlob* vsBuffer, *psBuffer = 0;
		D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		CompileD3DShader("Shaders/TextureMap.fx", "VS_Main", "vs_4_0", &vsBuffer);
		CompileD3DShader("Shaders/TextureMap.fx", "PS_Main", "ps_4_0", &psBuffer);

		DirectX::ThrowIfFailed(
			_dev->CreateVertexShader(vsBuffer->GetBufferPointer(),
				vsBuffer->GetBufferSize(),
				0,
				&solidColorVS)
			);

		DirectX::ThrowIfFailed(
			_dev->CreatePixelShader(psBuffer->GetBufferPointer(),
				psBuffer->GetBufferSize(),
				0,
				&solidColorPS)
			);

		unsigned int totalLayoutElements = ARRAYSIZE(solidColorLayout);

		DirectX::ThrowIfFailed(
			_dev->CreateInputLayout(solidColorLayout,
				totalLayoutElements,
				vsBuffer->GetBufferPointer(),
				vsBuffer->GetBufferSize(),
				&inputLayout)
			);

		D3DX11CreateShaderResourceViewFromFile(_dev.Get(),
			filename.c_str(), 0, 0, &colorMap, 0);

		ID3D11Resource *resource;
		ID3D11Texture2D *texture2D;
		D3D11_TEXTURE2D_DESC textureDesc;
		colorMap->GetResource(&resource);
		resource->QueryInterface<ID3D11Texture2D>(&texture2D);
		texture2D->GetDesc(&textureDesc);
		_textureWidth = static_cast<float>(textureDesc.Width);
		_textureHeight = static_cast<float>(textureDesc.Height);

		ID3D11Resource* colorTex;

		colorMap->GetResource(&colorTex);

		D3D11_TEXTURE2D_DESC colorTexDesc;
		((ID3D11Texture2D*)colorTex)->GetDesc(&colorTexDesc);
		colorTex->Release();

		ID3D11RasterizerState *rasterize;

		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

		rasterizerDesc.AntialiasedLineEnable = false;
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = true;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.FrontCounterClockwise = false;
		rasterizerDesc.MultisampleEnable = false;
		rasterizerDesc.ScissorEnable = false;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;

		_dev->CreateRasterizerState(&rasterizerDesc, &rasterize);
		_devcon->RSSetState(rasterize);

		// transparence
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));
		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		_dev->CreateBlendState(&blendDesc, alphaBlendState.GetAddressOf());
		_devcon->OMSetBlendState(alphaBlendState.Get(), blendFactor, 0xFFFFFFFF);

		D3D11_SAMPLER_DESC desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
		_dev->CreateSamplerState(&desc, &colorMapSampler);
	}


	ID3D11InputLayout *Texture::getInputLayout()
	{
		return inputLayout.Get();
	}

	ID3D11VertexShader *Texture::getVertexShader()
	{
		return solidColorVS.Get();
	}

	ID3D11PixelShader *Texture::getPixelShader()
	{
		return solidColorPS.Get();
	}

	ID3D11SamplerState *Texture::getColorMapSampler()
	{
		return colorMapSampler.Get();
	}

	ID3D11ShaderResourceView *Texture::getColorMap()
	{
		return colorMap.Get();
	}

	float Texture::getWidth()
	{
		return _textureWidth;
	}

	float Texture::getHeight()
	{
		return _textureHeight;
	}

	void Texture::release()
	{
		solidColorVS.Reset();
		solidColorPS.Reset();
		inputLayout.Reset();
		colorMapSampler.Reset();
		alphaBlendState.Reset();
		colorMap.Reset();
	}
}