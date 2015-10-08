#pragma once

#include "Graphics.h"

class RectangleShape
{
public:
	RectangleShape::RectangleShape(float width, float height);
	~RectangleShape();

private:
	ComPtr<ID3D11RenderTargetView> rendertarget;
	ComPtr<ID3D11Buffer> vertexbuffer;
};
