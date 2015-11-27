#include "Texture.h"

namespace Moo
{
	Texture::Texture() :
		solidColorVS(0), solidColorPS(0),
		inputLayout(0),
		colorMap(0), colorMapSampler(0),
		mvpCB(0), alphaBlendState(0)
	{
		_width = 50;
		_height = 50;
		_dev = d3d::getInstance().getD3DDevice();
		_devcon = d3d::getInstance().getContext();
	}

	Texture::~Texture()
	{
	}

	bool Texture::CompileD3DShader(char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer)
	{
		D3DX11CompileFromFile(filePath, 0, 0, entry, shaderModel,
			NULL, 0, 0, buffer, NULL, 0);
		return true;
	}

	void Texture::loadFromFile(const std::string &filename)
	{
		ID3DBlob* vsBuffer = 0;

		bool compileResult = CompileD3DShader("TextureMap.fx", "VS_Main", "vs_4_0", &vsBuffer);

		_dev->CreateVertexShader(vsBuffer->GetBufferPointer(),
			vsBuffer->GetBufferSize(), 0, &solidColorVS);


		D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		unsigned int totalLayoutElements = ARRAYSIZE(solidColorLayout);

		_dev->CreateInputLayout(solidColorLayout, totalLayoutElements,
			vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), &inputLayout);

		ID3DBlob* psBuffer = 0;

		compileResult = CompileD3DShader("TextureMap.fx", "PS_Main", "ps_4_0", &psBuffer);

		_dev->CreatePixelShader(psBuffer->GetBufferPointer(),
			psBuffer->GetBufferSize(), 0, &solidColorPS);

		D3DX11CreateShaderResourceViewFromFile(_dev,
			filename.c_str(), 0, 0, &colorMap, 0);

		D3D11_BUFFER_DESC constDesc;
		ZeroMemory(&constDesc, sizeof(constDesc));
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constDesc.ByteWidth = sizeof(XMMATRIX);
		constDesc.Usage = D3D11_USAGE_DEFAULT;

		_dev->CreateBuffer(&constDesc, 0, &mvpCB);

		ID3D11Resource* colorTex;

		colorMap->GetResource(&colorTex);

		D3D11_TEXTURE2D_DESC colorTexDesc;
		((ID3D11Texture2D*)colorTex)->GetDesc(&colorTexDesc);
		colorTex->Release();

		float halfWidth = (float)_width / 2.0f;
		float halfHeight = (float)_height / 2.0f;

		VERTEX testing[] =
		{
			{ XMFLOAT3(halfWidth,  halfHeight, 1.0f), _color, XMFLOAT2(1.0f, 0.0f) },
			{ XMFLOAT3(halfWidth, -halfHeight, 1.0f), _color, XMFLOAT2(1.0f, 1.0f) },
			{ XMFLOAT3(-halfWidth, -halfHeight, 1.0f), _color, XMFLOAT2(0.0f, 1.0f) },

			{ XMFLOAT3(-halfWidth, -halfHeight, 1.0f), _color, XMFLOAT2(0.0f, 1.0f) },
			{ XMFLOAT3(-halfWidth,  halfHeight, 1.0f), _color, XMFLOAT2(0.0f, 0.0f) },
			{ XMFLOAT3(halfWidth,  halfHeight, 1.0f), _color, XMFLOAT2(1.0f, 0.0f) },
		};

		D3D11_BUFFER_DESC vertexDesc;
		ZeroMemory(&vertexDesc, sizeof(vertexDesc));
		vertexDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.ByteWidth = sizeof(VERTEX) * 6;

		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(resourceData));
		resourceData.pSysMem = testing;

		_dev->CreateBuffer(&vertexDesc, &resourceData, &vertexBuffer);

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

		_dev->CreateBlendState(&blendDesc, &alphaBlendState);
		_devcon->OMSetBlendState(alphaBlendState, blendFactor, 0xFFFFFFFF);

		D3D11_SAMPLER_DESC desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
		_dev->CreateSamplerState(&desc, &colorMapSampler);
	}

	ID3D11InputLayout *Texture::getInputLayout()
	{
		return inputLayout;
	}

	ID3D11VertexShader *Texture::getVertexShader()
	{
		return solidColorVS;
	}

	ID3D11PixelShader *Texture::getPixelShader()
	{
		return solidColorPS;
	}

	ID3D11SamplerState *Texture::getColorMapSampler()
	{
		return colorMapSampler;
	}

	ID3D11ShaderResourceView *Texture::getColorMap()
	{
		return colorMap;
	}

	ID3D11Buffer *Texture::getVertexBuffer()
	{
		return vertexBuffer;
	}

	ID3D11Buffer *Texture::getContentBuffer()
	{
		return mvpCB;
	}

	void Texture::release()
	{
		vertexBuffer->Release();
		solidColorVS->Release();
		solidColorPS->Release();
		inputLayout->Release();
		mvpCB->Release();
		colorMapSampler->Release();
		alphaBlendState->Release();
		colorMap->Release();
	}
}