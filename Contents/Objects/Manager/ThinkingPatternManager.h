#pragma once

#include <vector>
#include <array>

/* 8.24. 한승규
* 9개의 노드 중 N개의 노드를 규칙성을 가진 배열로 잡아서 반환해줌
*
* 기사의 여행(Warnsdorff 휴리스틱)을 이용했음
* - 폰 바른스도르프 아져씨가 만든거임
* 9개의 노드 중, 재방문이 불가능 하고, 1칸 이웃한 칸만 진출 가능할 때,
* 남은 경로의 수가 1에 근접한 수(0은 후순위)가 남은 칸으로 이어가면
* 중간에 막히는 경우 없이 노드를 이을 수 있음,
* 즉. 여유 많은 노드의 경우에는, 다른 노드와 연결되어 있다는 의미이기도 해서
* 최대한 살리는거고, 눈앞에 진출 경로가 1만 남은 노드의 경우, 지금 고르지 않으면 막혀버리는거임
*
* 재!밌!다!.
* 신!난!다!.
*
* MakeTour(갯수) << 이거 쓰면 됨.
* 아무튼 다 됨, 갯수 만큼의 규칙성을 가지는 배열을 뱉어줌
*
* 약간의 찐빠가 있음
* 중앙 노드 5의 경우, 초반에 선택될 가능성이 매우, 아니 그냥 없음.
* 혼자 진출 가능 노드가 8개라서, 최소한 동점이 되는 순간
* 즉, 3번째까지는 절.대 안나옴
* 4번째부터 낮은 확률로 등장함
*/


// 1u가 32이상이 되면 터짐, 주의 바람
// uint16_t 기준이라서, 4*4까지 커버됨, 그런데 쓰지마셈
// 쓰지말라면 쓰지말라고

class ThinkingPatternManager {
public:

	std::vector<int> MakeTour(int length, bool isSmart = false); // 길이(갯수)를 지정해주면, 알아서 규칙성을 띄는 배열을 뽑아줌
	// isSmart = true인 경우, 3개 값만 랜덤으로 뱉어줌(플레이어 전용)

	void SetUp();

private:
	bool IsInside(int x, int y); // 정규화 한 값이 사이즈를 이탈하는지 확인하는 기능 함수	
	int StepTour(int nowNode, uint16_t& visited); // -1이나 음수 나오면 터진거임

	void SmartTour(std::vector<int>& p);

	static inline int countOnes(uint16_t x) noexcept {
		int cnt = 0;
		for (; x; ++cnt) x &= (x - 1);
		return cnt;
	}
	
	bool PickTwoNeighbors(int n, int& a, int& b, uint16_t visited = 0);


private:
	int m_size = 3; // 크기, 나중에 바꾸든가 마음대로(제발 바꾸지마)

	int m_sizeSqr;

	bool isSetUp = false;

	std::array<uint16_t, 9> adjMasks; // 진출 가능 여부를 확인하는 마스크		 
};