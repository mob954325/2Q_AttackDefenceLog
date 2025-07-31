#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Math/Vector2.h"

class LineRenderer : public RenderComponent
{
public:
	void OnStart() override;
	void OnDestroy() override;

	void SetPosition1(Vector2 pos);
	Vector2 GetPosition1();
	void SetPosition2(Vector2 pos);
	Vector2 GetPosition2();

	void Render(D2DRenderManager* render) override;
	void SetWidth(FLOAT width);
	void SetStyle(ID2D1StrokeStyle* style);

private:
	D2D1_RECT_F rect{};

	ID2D1SolidColorBrush* brush{};
	FLOAT width = 0.8f;
	ID2D1StrokeStyle* strokeStyle = (ID2D1StrokeStyle*)0;

	Vector2 position1{};
	Vector2 position2{};
};

