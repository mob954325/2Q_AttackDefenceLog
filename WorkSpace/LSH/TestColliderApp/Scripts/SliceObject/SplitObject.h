#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "PieceObject.h"
#include "Components/Rendering/BoxRenderer.h"
#include "Components/Logic/InputSystem.h"

/* 0801 | 작성자 이성호
*  기능 : PieceObject를 관리하는 monobehaivor로 콜라이더 감지 및 조각을 이동시키는 제어 스크립트
*/

/*
*	   (0,0) +-----------+ (width, 0)
*	         | 0 | 1 | 2 |
*	         +-----------+
*	         | 3 | 4 | 5 |
*	         +-----------+
*	         | 6 | 7 | 8 |
* (0, height)+-----------+ (width, height)
*/

/*
* 
*/

enum OverlapState
{
	Notyet = 0,
	Processing,
	End,
};

class SplitObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnUpdate() override;

	void HandleOverlap();
	bool IsOverlap(float x, float y, int& outIndex);
	void SetOriginImage(std::wstring path);
	void SetImages(std::vector<PieceObject*> objs);
	void Spread();
	void Reset();
	void SetGrid(int gridSize);

	// slice function
	void SliceVertical();
	void SliceHorizon();
	void SliceDiagonalLeft();
	void SliceDiagonalRight();
private:
	BitmapRenderer* origin{};

	std::vector<PieceObject*> pieces; // 12시 부터 1 2 3 4 5 6...
	std::vector<D2D1_RECT_F> grids;
	std::vector<BoxRenderer*> boxes; // debug grid

	InputSystem* input{};

	OverlapState state = OverlapState::Notyet;
	
	Vector2 HorizontalVec = { 1,0 };
	Vector2 startVec{};
	Vector2 endVec{};
	int prevIndex = -1;
	int gridSize = -1; // 그리드 크기, 그리드 개수는 gridSize * gridSize
	
	const float HORIZONTAL_DOT_THRESHOLD = 0.18f;  // 수평에 가까운 기준
	const float VERTICAL_DOT_THRESHOLD = 0.82f;    // 수직에 가까운 기준
};