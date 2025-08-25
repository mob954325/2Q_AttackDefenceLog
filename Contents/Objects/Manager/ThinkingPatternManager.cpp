#include "ThinkingPatternManager.h"
#include "../Engine/Math/GameRandom.h" // 랜덤값 내놔

#include <algorithm> // 알고라파덕
#include <cstdint> // 고정 폭 정수타입 정의해줌, 의도 명시 + 가시성 향상을 위해 사용됨(안써도 문제는 없음)
#include <climits> // 극값 쓸때 필요함, 각 타입의 최대 최소값을 받을 수 있음(안써도 문제없음)

std::vector<int> ThinkingPatternManager::MakeTour(int length)
{
	if (length > 9) length = 9;
	if (length < 1) length = 1;

	if (!isSetUp) {
		SetUp(); // 혹시라도 초기화 안했으면 해줌
	}

	std::vector<int> path;
	path.reserve(length); // 예약, 재할당 줄이기

	int n = GameRandom::RandomRange(0, 9); // 0 ~ 8
	path.push_back(n + 1);
	uint16_t visitedMask = 0;
	// n = 시작 노드

	for (int i = 0; i < length - 1; ++i) {
		// visitedMask는 SetpTour 내부에서 계속 누적 + 사용됨
		int tmp = StepTour(n, visitedMask);

		if (tmp < 0) { // 음수 나오면 내부에서 꼬인거임
			std::cout << "비상!!!비상!!!" << std::endl;
			break;
		}

		path.push_back(tmp + 1);
		n = tmp;
	}

	//디버그용
	std::cout << "경로 반환됨 : ";
	for (auto& p : path) {
		std::cout << p;
	}
	std::cout << std::endl;

	return path;
}

void ThinkingPatternManager::SetUp()
{
	adjMasks = { 0, };
	m_sizeSqr = m_size * m_size;

	for (int i = 0; i < adjMasks.size(); ++i) {
		int col = i % m_size; // 칸, X임 0 1 2
		int row = i / m_size; // 줄, Y임 0 1 2

		uint16_t mask = 0;

		for (int dy = -1; dy <= 1; ++dy) { // y 범위 -1 ~ +1
			for (int dx = -1; dx <= 1; ++dx) { // x 범위 -1 ~ +1

				if (dx == 0 && dy == 0) continue; // 00 <- 자기 자신임

				int newX = col + dx;
				int newY = row + dy;

				if (IsInside(newX, newY))
					mask |= (1u << (newY * m_size + newX));
			}
		}

		adjMasks[i] = mask;
	}

	isSetUp = true;
}

bool ThinkingPatternManager::IsInside(int x, int y)
{
	return (0 <= x && x < m_size) && (0 <= y && y < m_size);
}

int ThinkingPatternManager::StepTour(int nowNode, uint16_t& visited)
{
	//현재 노드에서 진입 가능한 노드 중 하나를 고를껀데
	//진입 가능한 노드들의 진출 가능 노드 갯수를 계산해서
	//1에 근접한 값을 골라서 반환해줌 + 마스크에도 새겨야함
	//원래는 0에 대한 예외처리가 필요함, 어디까지나 1에 근접하게, 0은 최 후순위임
	//그러나, 3*3에서는 예외가 발생하지 않음(검증 완료)
	//로직을 단순화 시킴

	const uint16_t full = (uint16_t)((1u << m_sizeSqr) - 1); // 자르는데 씀

	visited |= (1u << nowNode); // 일단, 현재 노드를 방문 완료취급해줌

	uint16_t invVisited = static_cast<uint16_t>(~visited) & full;
	uint16_t adj = adjMasks[nowNode]; // 진출 가능 목록	

	int correct = INT_MAX; // 대충 극값 넣어주면 될듯
	std::vector<int> same;

	for (int i = 0; i < m_sizeSqr; ++i) {
		if (adj & (1u << i) & invVisited) {
			//마스크에서 걸린 놈들임, 방문 X + 진출노드
			int n = countOnes(adjMasks[i] & invVisited); // i 노드의 진출 가능 경로 & 미방문 노드

			if (n == correct) { // 동점
				same.push_back(i); // 저장해두고 넘어감, 최대값은 동일하니 스킵						
			}
			else if (n < correct) // 갱신
			{
				same.clear(); // 동점 지워줌
				same.push_back(i); // 하나만 저장됨
				correct = n; // 최대값 갱신
			}
		}
	}

	if (same.empty())
		return -1; // 이게 무슨 일이야

	int num = GameRandom::RandomRange(0, same.size()); // 0 ~ size	

	return same[num];
}


//Kernighan 
//브라이언 커니핸 아져씨가 고안한 좋은방법임
/*
* 0000 0000 1011 1000
* 0000 0000 1011 0111
* 자연스럽게 최 하위 비트에서부터 1이 나올때까지를 지워버림 ㄷㄷ


int countOnes(uint16_t x) {
	int cnt = 0;

	while (x) {
		x &= (x - 1); // 커니햄 당신은 도대체 뭐하는 괴물입니까
		++cnt;
	}

	return cnt;
}
// 헤더에 인라인으로 옮겼음
*/

