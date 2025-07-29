#pragma once
#include "Components/Rendering/RenderComponent.h"

/// 25.07.28 | 작성자 이성호
/// 원 모양을 그리는 컴포넌트
/// radius 크기의 원을 그린다.

class CircleComponent : public RenderComponent
{
public:
	void OnStart() override;
	void OnDestroy() override;

	void Render(D2DRenderManager* render) override;
	void SetRadius(float radius);
	void SetStyle(ID2D1StrokeStyle* style);
	void SetIsShow(bool value);

private:
	ID2D1SolidColorBrush* brush{};
	ID2D1StrokeStyle* strokeStyle = (ID2D1StrokeStyle*)0;

	float radius{};

	bool isShow = false;
};

