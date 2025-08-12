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

	void SetFlipX(bool value);
	bool IsFlipX();

	void SetFlipY(bool value);
	bool IsFlipY();

	void SetUseCustomRect(bool value);

	void SetDestRect(const D2D1_RECT_F& rect);
	D2D1_RECT_F GetDestRect() const;

	void SetSrcRect(const D2D1_RECT_F& rect);
	D2D1_RECT_F GetSrcRect() const;

	void SetCapacity(float value);
	float GetCapacity();

	// Cliping
	void SetClipingPosition(const std::vector<Vector2>& points);

protected:
	std::shared_ptr<BitmapResource> m_bitmapResource;
	D2D1_RECT_F destRect = {};
	D2D1_RECT_F srcRect = {};

	float offsetX = 0.0f;
	float offsetY = 0.0f;

	float timer = 0;
	float maxtimer = 0.2f;

	bool isFlipX = false;
	bool isFlipY = false;
	bool useCustomRect = false; // 위 destRect, srcRect 사용여부 변수

	float capacity = 1.0f;

	// For Cliping
	Microsoft::WRL::ComPtr<ID2D1PathGeometry> pathGeometry{};	// 출력할 범위 기하학 도형 데이터
	ID2D1GeometrySink* pSink = NULL;							// 기하학 범위를 그릴 sink
	ID2D1Layer* layer = NULL;
	std::vector<Vector2> points;								// 도형 꼭짓점 좌표값들
};

