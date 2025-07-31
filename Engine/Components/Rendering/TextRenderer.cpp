#include "TextRenderer.h"
#include "Platform/D2DRenderManager.h"
#include "Datas/EngineData.h"
#include "Components/Base/GameObject.h"

void TextRenderer::Render(D2DRenderManager* manager)
{
	if (!IsActiveSelf()) return;

	if (!isWorldPosition)
	{
		manager->PrintText(text.c_str(), left, top, color);
	}
	else
	{
		D2D1_MATRIX_3X2_F final = owner->GetTransform().GetFinalMatrix();
		manager->SetRenderTransform(final);
		manager->PrintText(text.c_str(), 0x0, 0, color, true);
	}
}

void TextRenderer::SetText(const std::wstring& text)
{
	this->text = text;
}

/// <summary>
/// 좌측 상단을 0,0으로 한 위치 값 설정
/// </summary>
/// <param name="left">x값</param>
/// <param name="top">y값</param>
void TextRenderer::SetPosition(float left, float top)
{
	this->left = left;
	this->top = top;
}

void TextRenderer::SetViewportPosition(float viewportX, float viewportY)
{
	float posX = EngineData::SceenWidth * viewportX;
	float posY = EngineData::SceenHeight * viewportY;

	this->left = posX;
	this->top = posY;
}

void TextRenderer::SetWorldObject(bool value)
{
	isWorldPosition = value;
}

bool TextRenderer::IsWorldPosition()
{
	return isWorldPosition;
}

void TextRenderer::SetColor(D2D1::ColorF color)
{
	this->color = color;
}
