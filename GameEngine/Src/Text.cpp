#include "Includes/Text.h"

namespace Moo
{
	Text::Text(const std::string &text, float width, float height, float x, float y) :
		solidColorVS(0), solidColorPS(0),
		inputLayout(0),
		colorMap(0), colorMapSampler(0),
		mvpCB(0), alphaBlendState(0)
	{
		_width = width;
		_height = height;
		setPosition(x, y);
		_text = text;

		_dev = d3d::getInstance().getD3DDevice();
		_devcon = d3d::getInstance().getContext();
		loadTexture();
	}

	Text::Text(Text & Text)
	{
		*this = Text;
	}

	Text::~Text()
	{
		//delete(_texture);
	}

	bool Text::CompileD3DShader(char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer)
	{
		D3DX11CompileFromFile(filePath, 0, 0, entry, shaderModel,
			NULL, 0, 0, buffer, NULL, 0);
		return true;
	}

	void	Text::loadTexture()
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
			"Font.dds", 0, 0, &colorMap, 0);

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
	}

	void	Text::createVertex(char letter, int offsetx)
	{
		float halfWidth = (float)_width / 2.0f;
		float halfHeight = (float)_height / 2.0f;

		float factor = (letter - '0') * 0.01f;
		_color = XMFLOAT4(1.0f, 0.1f, 0.1f, 1.0f);
		VERTEX testing[] =
		{
			{ XMFLOAT3(halfWidth,  halfHeight, 1.0f), _color, XMFLOAT2(0.18f + factor, 0.0f) },
			{ XMFLOAT3(halfWidth, -halfHeight, 1.0f), _color, XMFLOAT2(0.18f + factor, 1.0f) },
			{ XMFLOAT3(-halfWidth, -halfHeight, 1.0f), _color, XMFLOAT2(0.17f + factor, 1.0f) },

			{ XMFLOAT3(-halfWidth, -halfHeight, 1.0f), _color, XMFLOAT2(0.17f + factor, 1.0f) },
			{ XMFLOAT3(-halfWidth,  halfHeight, 1.0f), _color, XMFLOAT2(0.17f + factor, 0.0f) },
			{ XMFLOAT3(halfWidth,  halfHeight, 1.0f), _color, XMFLOAT2(0.18f + factor, 0.0f) },
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


		unsigned int stride = sizeof(VERTEX);
		unsigned int offset = 0;

		_devcon->IASetInputLayout(inputLayout);
		_devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		_devcon->VSSetShader(solidColorVS, 0, 0);
		_devcon->PSSetShader(solidColorPS, 0, 0);
		_devcon->PSSetSamplers(0, 1, &colorMapSampler);

		XMMATRIX view = d3d::getInstance().getView();
		XMMATRIX projection = d3d::getInstance().getProjection();

		vpMatrix = DirectX::XMMatrixMultiply((XMMATRIX)view, (XMMATRIX)projection);

		_devcon->PSSetShaderResources(0, 1, &colorMap);
		_devcon->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		XMVECTOR axis = DirectX::XMVectorSet(0, 0, 0, 0);

		XMMATRIX translation = DirectX::XMMatrixTranslation((offsetx * 10) + getPosition().x + (_width / 2), getPosition().y + (_height / 2), 0.5f);
		XMMATRIX rotationZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(getRotation()));

		XMMATRIX scalling = DirectX::XMMatrixScaling(getScale().x, getScale().y, 1);

		XMMATRIX world = scalling * rotationZ * translation;

		XMMATRIX mvp = DirectX::XMMatrixMultiply((XMMATRIX)world, (XMMATRIX)vpMatrix);
		mvp = DirectX::XMMatrixTranspose(mvp);

		_devcon->UpdateSubresource(mvpCB, 0, 0, &mvp, 0, 0);
		_devcon->VSSetConstantBuffers(0, 1, &mvpCB);
		_devcon->Draw(6, 0);
	}

	void	Text::draw()
	{
		const char *writable = _text.c_str();
		int i = 0;
		while (writable[i] != '\0') {
			createVertex(writable[i], i);
			++i;
		}
	}

	void  Text::setText(const std::string &text)
	{
		_text = text;
	}

	float Text::getWidth()
	{
		return _width * getScale().x;
	}

	float Text::getHeight()
	{
		return _height * getScale().y;
	}

	ID3D11Buffer* const* Text::getVertexBuffer() const
	{
		return &vertexBuffer;
	}

	void Text::release()
	{
		if (vertexBuffer == nullptr) {
			vertexBuffer->Release();
		}
	}

}