#include "BoxComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Components/Base/GameObject.h"
#include "Datas/EngineData.h"
#include "Scene/SceneManager.h"

void BoxComponent::OnStart()
{
	renderManager->CreateBrush(D2D1::ColorF::Green, &brush);
}

void BoxComponent::OnDestroy()
{
	if (brush)
	{
		brush->Release();
	}
}

void BoxComponent::Render(D2DRenderManager* render)
{
	if (!isShow) return;

	if (brush)
	{
		D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();

		Vector2 pos = owner->GetTransform().GetPosition();
		render->SetBitmapTransform(mat);
		render->DrawRectangle(rect, brush, width, strokeStyle);
	}
}

void BoxComponent::SetRect(D2D1_RECT_F rect)
{
	this->rect = rect; // 순수 크기
}

void BoxComponent::SetWidth(FLOAT width)
{
	this->width = width;
}

void BoxComponent::SetStyle(ID2D1StrokeStyle* style)
{
	this->strokeStyle = style;
}

void BoxComponent::SetIsShow(bool value)
{
	isShow = value;	
}

D2D1_POINT_2F BoxComponent::MatrixTransform(const D2D1_POINT_2F& point, const D2D1_MATRIX_3X2_F& matrix)
{
	return D2D1::Point2F(
		point.x * matrix._11 + point.y * matrix._21 + matrix._31,
		point.x * matrix._12 + point.y * matrix._22 + matrix._32
	);
}
