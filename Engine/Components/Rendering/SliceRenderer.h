#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Resources/BitmapResource.h"
#include "Math/Vector2.h"
#include "Components/Rendering/LineRenderer.h"

/*  2025.08.04 - 이성호
*	기능 : originalBitmap를 두 개의 이미지로 생성하고 자르는 컴포넌트
*	사용법 : 1. SetOriginalByPath 로 원본 이미지를 경로로 불러오기
*			2. Slice 함수로 잘리기 시작한 위치값과 잘리는 곳이 끝나는 위치값을 매개변수로 넣기
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
	Vector2 dirVec{};
	float speed{};
	float capacity = 1;
};

struct ClipEdge
{
	Vector2 p1, p2;
};

class SliceRenderer : public RenderComponent
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void Render(D2DRenderManager* manager) override;

	void SetOriginalByPath(std::wstring path);
	void SetOriginalByBitmap(std::shared_ptr<BitmapResource> bitmap);
	std::shared_ptr<BitmapResource> GetOriginal() const;
	
	void SetPoint(const std::vector<Vector2> points);
	GameObject* Slice(const Vector2& left, const Vector2& right);
	void Reset();

	void CreateGeomatryByPolygon(const std::vector<Vector2>& polygon);
	std::vector<Vector2> ClipPolygon(const  std::vector<Vector2>& subjectPolygon, const ClipEdge& edge);
	Vector2 GetIntersection(const Vector2& s, const Vector2& e, const ClipEdge& edge);

	// setinfo
	void SetPosition(const Vector2& position);
	void SetDirection(const Vector2& dir);
	void SetSpeed(float value);

	SliceBitmapInfo GetInfo() const;

private:
	bool IsInside(const Vector2& p, const ClipEdge& edge);
	bool NearlyEqual(float a, float b, float epsilon = 1e-6f);

	std::shared_ptr<BitmapResource> originBitmap{}; // 원본 비트맵
	Microsoft::WRL::ComPtr<ID2D1PathGeometry> pathGeometry{};
	SliceBitmapInfo infos; // 이 비트맵 정보

	std::vector<Vector2> points;

	ID2D1GeometrySink* pSink = NULL; // 기하학 범위를 그릴 sink

	std::vector<LineRenderer*> lrs;
};