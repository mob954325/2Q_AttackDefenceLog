#pragma once
#include "Components/Base/Component.h"
#include "Components/Rendering/RenderComponent.h"
#include <string>

class TextRenderer : public RenderComponent
{
public:
	void Render(D2DRenderManager* manager) override;

	void SetText(const std::wstring& text);
	void SetPosition(float left, float top);
	void SetViewportPosition(float viewportX, float viewportY);

	void SetWorldObject(bool value);
	bool IsWorldPosition();

	void SetColor(D2D1::ColorF color);

private:
	std::wstring text;
	
	D2D1::ColorF color = D2D1::ColorF::White;

	bool isWorldPosition = false;
	float left = 0.0f;
	float top = 0.0f;
};

