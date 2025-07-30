#include "PatternManager.h"
#include "Components/Base/GameObject.h"
#include "Components/Rendering/BitmapRenderer.h"


void PatternManager::SetNodes(const std::array<GameObject*, 9>& positions, float radius)
{	
	for (int i = 0; i < 9; ++i) {		
		auto bmpSize = positions[i]->GetComponent<BitmapRenderer>()->GetResource()->GetBitmap()->GetSize();
		Vector2 mat = positions[i]->GetTransform().GetPosition();
		
		Vector2 offset = { bmpSize.width * 0.5f, bmpSize.height * 0.5f };

		nodes[i].position = mat + offset;
		
		nodes[i].radius = radius;
		nodes[i].isHit = false; // 초기화,

		std::cout << nodes[i].position<<std::endl;
	}
}

void PatternManager::AddNodes(Vector2 pos, float radius, int i)
{
	nodes[i].position = pos;
	nodes[i].radius = radius;
	nodes[i].isHit = false; // 초기화,
}


void PatternManager::SetPatternBox(const D2D1_RECT_F& box)
{
	patternBox = box;
}

void PatternManager::CheckTrails(const std::deque<TrailStamp>& trails)
{
	pattern.clear();

	for (auto stamp : trails) { // 트레일 안에 있는것들, 형태는 TrailStamp
		Vector2 pos = { stamp.position.x, stamp.position.y };

		for (int i = 0; i < 9; ++i) {

			auto& node = nodes[i]; // Node 구조체

			if (node.isHit) continue; // 이미 판정한건 건너뜀

			float dx = pos.x - node.position.x; // x축 차이
			float dy = pos.y - node.position.y; // y축 차이
			float distSq = dx * dx + dy * dy; // 피타고라스
			float radiusSq = node.radius * node.radius; // 반지름의 제곱 // 사실상 판정 거리임 반지름으로 보긴 애매할 수 있음

			if (distSq <= radiusSq) { // 충돌 경우수
				node.isHit = true;
				std::cout << "[DEBUG] pushing pattern index: " << (i + 1) << std::endl;
				pattern.push_back(i + 1); // 1~9				
			}
		}
	}

	for (int i = 0; i < 9; ++i) {
		nodes[i].isHit = false; // 초기화,
	}
}

void PatternManager::CheckOutOfBox(Vector2 pos) // AABB < 마우스 나갔는지만 판단해주면 충분함
{
	if (pos.x < patternBox.left || pos.x > patternBox.right || pos.y < patternBox.top || pos.y > patternBox.bottom)
		isMousOut = true;
	else
		isMousOut = false;
}



