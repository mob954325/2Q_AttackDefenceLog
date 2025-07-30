#pragma once
#include "Components/Rendering/TrailComponent.h"
#include "Components/Logic/InputSystem.h"
#include <array>

/* 7.30. 한승규
* 노드(9개)와, 현재 트레일 컴포넌트가 남긴 궤적의 충돌여부를 확인해서
* 결과값(어떤 노드를 통과-충돌 하였는지)를 반환해주는 매니저
* 즉, 1 3 2 이런식으로 배열을 뱉을 예정임
* + 추가적으로, 패턴 영역(사각형) 밖으로 나간걸 판단해서
* 트레일을 끊어주는(감소시키는) 플래그를 키는 역할도함
* 패턴 관련된 관리는 여기서 처리할 예정
*/

/* 기능 1 : 등록된 노드(9개)와, 입력된 큐(cachedTrails) 충돌처리 (충돌 순서)를 배열(큐)로 만들어서 반환 ex) 1 3 2 4 5 6 8
*  기능 2 : 등록된 박스(패턴 크기) 밖으로 마우스가 나가는걸 감지하면, 플래그변환해줌
*/

struct Node {
	Vector2 position;
	float radius;
	bool isHit = false;
};

class PatternManager {
public:
	void SetNodes(const std::array<Vector2, 9>& positions, float radius);
	void SetPatternBox(const D2D1_RECT_F& box);
	void CheckTrails(const std::deque<TrailStamp>& trails);
	void CheckOutOfBox(Vector2 pos);

	const std::deque<int>& GetPattern() const {
		return pattern;
	}

	bool isMousOut = false;
private:
	std::array<Node, 9> nodes;
	std::deque<int> pattern;
	D2D1_RECT_F patternBox = { 0,0,0,0 };
};
