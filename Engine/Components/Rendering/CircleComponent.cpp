#include "CircleComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Components/Base/GameObject.h"

void CircleComponent::OnStart()
{
	renderManager->CreateBrush(D2D1::ColorF::Green, &brush);
}

void CircleComponent::OnDestroy()
{
	if (brush)
	{
		brush->Release();
	}
}

void CircleComponent::Render(D2DRenderManager* render)
{
	if (!isShow) return;

	if (brush)
	{
		D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();

		render->SetBitmapTransform(mat);
		render->DrawCircle(brush, radius, 1.0f, strokeStyle);
	}
}

void CircleComponent::SetRadius(float radius)
{
	this->radius = radius;
}

void CircleComponent::SetStyle(ID2D1StrokeStyle* style)
{
	this->strokeStyle = style;
}

void CircleComponent::SetIsShow(bool value)
{
	isShow = value;
}