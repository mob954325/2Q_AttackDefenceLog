#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Resources/BitmapResource.h"
#include "Math/Vector2.h"

/*  2025.08.04 - 이성호
*	기능 : originalBitmap를 두 개의 이미지로 생성하고 자르는 컴포넌트
*/

///                (0,0) +----+ (x, 0)
///                      |####|
///	                     |####| --> 출력 되는 공간
///	(0, y - draw height) +----+ (x, y - draw height)
///                      |    |
///                      |    | --> cliping되어 출력되지 않는 공간
///         (x, y - ...) +----+ (x, y - ...)
///                      |####| --> 출력 되는 공간
///	                     |####|
///	                     +----+ (x, y)


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

	// 그릴 기하학범위
	ComPtr<ID2D1PathGeometry> pathGeometry1;
	ComPtr<ID2D1PathGeometry> pathGeometry2;
	ID2D1GeometrySink* pSink = NULL; // 기하학 범위를 그릴 sink
};