#include "LineRenderer.h"
#include "Platform/D2DRenderManager.h"
#include "Components/Base/GameObject.h"

void LineRenderer::OnStart()
{
	renderManager->CreateBrush(D2D1::ColorF::Green, &brush);
}

void LineRenderer::OnDestroy()
{
	if (brush)
	{
		brush->Release();
	}
}

void LineRenderer::SetPosition1(Vector2 pos)
{
	position1 = pos;
}

Vector2 LineRenderer::GetPosition1()
{
	return position1;
}

void LineRenderer::SetPosition2(Vector2 pos)
{
	position2 = pos;
}

Vector2 LineRenderer::GetPosition2()
{
	return position2;
}


void LineRenderer::Render(D2DRenderManager* render)
{
	if (!IsActiveSelf()) return;

	if (brush)
	{
		D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();

		Vector2 pos = owner->GetTransform().GetPosition();
		render->SetRenderTransform(mat);
		render->DrawLine(brush, position1, position2, width, strokeStyle);
	}
}

void LineRenderer::SetWidth(FLOAT width)
{
	this->width = width;
}

void LineRenderer::SetStyle(ID2D1StrokeStyle* style)
{
	this->strokeStyle = style;
}