#include "CircleRenderer.h"
#include "Platform/D2DRenderManager.h"
#include "Components/Base/GameObject.h"
	
void CircleRenderer::OnStart()
{
	renderManager->CreateBrush(D2D1::ColorF::Green, &brush);
}

void CircleRenderer::OnDestroy()
{
	if (brush)
	{
		brush->Release();
	}
}

void CircleRenderer::Render(D2DRenderManager* render)
{
	if (!IsActiveSelf()) return;

	if (brush)
	{
		D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();

		render->SetRenderTransform(mat);
		render->DrawCircle(brush, radius, 1.0f, strokeStyle);
	}
}

void CircleRenderer::SetRadius(float radius)
{
	this->radius = radius;
}

void CircleRenderer::SetStyle(ID2D1StrokeStyle* style)
{
	this->strokeStyle = style;
}