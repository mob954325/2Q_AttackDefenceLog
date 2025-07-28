#pragma once
#include "Application/Application.h"
#include "Components/Base/Component.h"
#include "Components/Rendering/RenderComponent.h"
#include "Components/Base/Transform.h"
#include "Resources/BitmapResource.h"

class BitmapRenderer : public RenderComponent 
{
public:
	BitmapRenderer() {};
	~BitmapRenderer() {};

	void Render(D2DRenderManager* manager) override;
	void OnStart() override;
	void OnDestroy() override;

	void CreateBitmapResource(std::wstring filePath);

	std::shared_ptr<BitmapResource> GetResource();

	void SetFlip(bool value);

protected:
	std::shared_ptr<BitmapResource> m_bitmapResource;
	D2D1_RECT_F destRect = {};

	int screenWidth = 0;
	int screenHeight = 0;
	float offsetX = 0.0f;
	float offsetY = 0.0f;

	float timer = 0;
	float maxtimer = 0.2f;

	bool isFlip = false;
};

