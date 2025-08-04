#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Resources/BitmapResource.h"
#include "Math/Vector2.h"

struct SliceBitmapInfo
{
	Vector2 position{};
	D2D1_MATRIX_3X2_F renderMatrix{};
	float capacity = 1;
};

class SliceRenderer : public RenderComponent
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void Render(D2DRenderManager* manager) override;

	void SetOriginal(std::wstring path);
	void Slice(const Vector2& dirVec);
	void Reset();

private:
	std::shared_ptr<BitmapResource> originBitmap{}; // 원본 비트맵

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> slice1;	// 잘려진 비트맵 1
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> slice2;	// 잘려진 비트맵 2
	SliceBitmapInfo slice1Info{};
	SliceBitmapInfo slice2Info{};
};

