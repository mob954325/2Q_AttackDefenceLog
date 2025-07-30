#include "BoxRenderer.h"
#include "Platform/D2DRenderManager.h"
#include "Components/Base/GameObject.h"
#include "Datas/EngineData.h"
#include "Scene/SceneManager.h"

void BoxRenderer::OnStart()
{
	renderManager->CreateBrush(D2D1::ColorF::Green, &brush);
}

void BoxRenderer::OnDestroy()
{
	if (brush)
	{
		brush->Release();
	}
}

void BoxRenderer::Render(D2DRenderManager* render)
{
	if (!IsActiveSelf()) return;

	if (brush)
	{
		D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();

		Vector2 pos = owner->GetTransform().GetPosition();
		render->SetRenderTransform(mat);
		render->DrawRectangle(rect, brush, width, strokeStyle);
	}
}

void BoxRenderer::SetRect(D2D1_RECT_F rect)
{
	this->rect = rect; // 순수 크기
}

void BoxRenderer::SetWidth(FLOAT width)
{
	this->width = width;
}

void BoxRenderer::SetStyle(ID2D1StrokeStyle* style)
{
	this->strokeStyle = style;
}

D2D1_POINT_2F BoxRenderer::MatrixTransform(const D2D1_POINT_2F& point, const D2D1_MATRIX_3X2_F& matrix)
{
	return D2D1::Point2F(
		point.x * matrix._11 + point.y * matrix._21 + matrix._31,
		point.x * matrix._12 + point.y * matrix._22 + matrix._32
	);
}
