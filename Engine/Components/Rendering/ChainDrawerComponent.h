#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/BitmapResource.h"


class ChainDrawerComponent : public RenderComponent
{
public:	
	void Render(D2DRenderManager* manager) override;
	void Draw(D2DRenderManager* manager);
	void CalcNormalizedRect(float value);
	void OnStart() override;


	float duration = 1.0f;

private:	
	float timer = 0.0f;

	std::shared_ptr<BitmapResource> baseBitmap;	
	std::vector<D2D1_RECT_F> rects;
};