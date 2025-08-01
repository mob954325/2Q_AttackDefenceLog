#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "PieceObject.h"
#include "Components/Rendering/BoxRenderer.h"

/* 0801 | 작성자 이성호
*  기능 : PiceObject를 관리하는 monobehaivor로 콜라이더 감지 및 조각을 이동시키는 제어 스크립트
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

// TODO : 닿은 그리드 위치 기준으로 오브젝트 분해하기

// NOTE:
// start와 end에 따라서 기울기를 정해서 날리기
// 각 각 start와  end가 존재하면 기울기에 따라 진입 인덱스와 나가는 위치 인덱스가 다를 것임!

class TestSliceObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnUpdate() override;

	void SetOriginImage(std::wstring path);
	void SetImages(std::vector<PieceObject*> objs);
	void Spread();
	void Reset();
	void SetGrid(); 

private:
	BitmapRenderer* origin{};
	std::vector<PieceObject*> pieces; // 12시 부터 1 2 3 4 5 6...
	std::vector<D2D1_RECT_F> grids;
	std::vector<BoxRenderer*> boxes; // debug

	bool isOverraped = false; // 최초 닿았는지 확인
	
};

// 15도씩 8방향 16개 이미지

