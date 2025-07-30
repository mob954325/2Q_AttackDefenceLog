#pragma once
#include "Components/Rendering/RenderComponent.h"

class BoxRenderer : public RenderComponent
{
public:
	void OnStart() override;
	void OnDestroy() override;

	void Render(D2DRenderManager* render) override;
	void SetRect(D2D1_RECT_F rect);
	void SetWidth(FLOAT width);
	void SetStyle(ID2D1StrokeStyle* style);
	void SetIsShow(bool value);


private:
	D2D1_POINT_2F MatrixTransform(const D2D1_POINT_2F& point, const D2D1_MATRIX_3X2_F& matrix);

	D2D1_RECT_F rect{};

	ID2D1SolidColorBrush* brush{};
	FLOAT width = 0.8f;
	ID2D1StrokeStyle* strokeStyle = (ID2D1StrokeStyle*)0;
};

