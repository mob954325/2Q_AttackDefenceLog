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
	Vector2 dirVec{}; // D2D 좌표 기준 방향
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
	void Render(D2DRenderManager* manager) override;

	/// <summary>
	/// 경로를 통해 비트맵 이미지 가져오는 함수
	/// </summary>
	/// <param name="path"></param>
	void SetOriginalByPath(std::wstring path);

	/// <summary>
	/// 비트맵을 통해 비트맵을 설정하는 함수
	/// </summary>
	/// <param name="bitmap"></param>
	void SetOriginalByBitmap(std::shared_ptr<BitmapResource> bitmap);

	/// <summary>
	/// 해당 컴포넌트가 가지고 있는 비트맵을 반환하는 함수
	/// </summary>
	/// <returns>shared_ptr의 비트맵 리소스</returns>
	std::shared_ptr<BitmapResource> GetOriginal() const;
	
	/// <summary>
	/// 꼭짓점 위치 값 설정함수 ( 사용 시 현재 vector 컨테이너 내용을 덮어씀 )
	/// </summary>
	/// <param name="points"></param>
	void SetPoint(const std::vector<Vector2>& points);

	/// <summary>
	/// 해당 컴포넌트의 이미지를 자르는 함수 ( upper과 lower로 나뉨 )
	/// </summary>
	/// <param name="left">위치 값 1</param>
	/// <param name="right">위치 값 2</param>
	/// <returns></returns>
	GameObject* Slice(const Vector2& left, const Vector2& right);

	/// <summary>
	/// 좌표값들로 기하학 도형을 생성하는 함수
	/// </summary>
	/// <param name="polygon">좌표값들이 들어있는 vector 컨테이너</param>
	void CreateGeomatryByPolygon(const std::vector<Vector2>& polygon);

	/// <summary>
	/// subjectPolygon의 좌표점으로 만들어진 도형을 edge 값을 이용해 짜르는 함수
	/// </summary>
	/// <param name="subjectPolygon">꼭짓점 죄표 값 모음</param>
	/// <param name="edge">자를 vector2 위치 값 두개 구조체</param>
	/// <returns>짤린 도형의 꼭짓점들</returns>
	std::vector<Vector2> ClipPolygon(const  std::vector<Vector2>& subjectPolygon, const ClipEdge& edge);

	/// <summary>
	/// clipEdge에 교차하는 end - start 벡터에 대한 교차 비를 통해 startVec을 edge벡터까지 이동시킨 결과값을 반환하는 함수
	/// </summary>
	/// <param name="startVec">시작 위치값</param>
	/// <param name="endVec">끝 위치값</param>
	/// <param name="edge">교차하는 선분</param>
	/// <returns></returns>
	Vector2 GetIntersection(const Vector2& startVec, const Vector2& endVec, const ClipEdge& edge);

	// setinfo
	void SetPosition(const Vector2& position);
	void SetDirection(const Vector2& dir);
	void SetSpeed(float value);

	void SetGravity(bool value);

	SliceBitmapInfo GetInfo() const;

private:
	/// <summary>
	/// cross product를 이용해 edge와 한 점
	/// </summary>
	/// <param name="p">검사할 vector2 값</param>
	/// <param name="edge">검사할 선</param>
	/// <returns>p가 edge보다 위에 있으면 true 아니면 false</returns>
	bool IsInside(const Vector2& p, const ClipEdge& edge);

	/// <summary>
	/// a와 b가 유사한지 확인하는 함수 - 두 float 변수가 유사한지 확인하는 함수
	/// </summary>
	bool NearlyEqual(float a, float b, float epsilon = 1e-6f);

	std::shared_ptr<BitmapResource> originBitmap{};				// 원본 비트맵
	Microsoft::WRL::ComPtr<ID2D1PathGeometry> pathGeometry{};	// 출력할 범위 기하학 도형 데이터
	SliceBitmapInfo infos; // 이 비트맵 정보

	std::vector<Vector2> points; // 도형 꼭짓점 좌표값들
	ID2D1GeometrySink* pSink = NULL; // 기하학 범위를 그릴 sink

	std::vector<LineRenderer*> lrs;	 // debug용 lineRenderer

	bool useGravity = false;
	float speed = 5.0f;
};