#include "ChainDrawerComponent.h"
#include "Utils/GameTime.h"
#include "Resources/ResourceManager.h"

constexpr float PI = 3.141592654f; // 이건 진짜진짜 ㄹㅇ 유명한 파이임

void ChainDrawerComponent::SliceRect(std::vector<int> pattern) // 1 3 2 4 5 이런거 넣어주면
{
	pieces.clear();
	if (pattern.size() < 2) return; // 2개이상 있어야 자르기 시작함, 사실상 들어오진 않을듯? 방어로직

	float sliceH = bmpSize.height; // 세로 크기는 원본 그대로 사용함
	float currentX = 0.0f;

	for (int i = 0; i < pattern.size() - 1; ++i) { // -1까지, +1할꺼라 한칸 내림

		Vector2 from = positions[pattern[i] - 1]; // 1~9 > 0~8 (현재)
		Vector2 to = positions[pattern[i + 1] - 1]; // 다음 좌표
		

		float dist = (to - from).Megnituede(); // sqrt(x * x + y * y);		
		float remainingWidth = bmpSize.width - currentX; // 이번 dist 요구값
		
		if (dist > remainingWidth) { // 요구값보다 많으면 -> 초과됨
			float shortage = dist - remainingWidth; // 초과분
			Vector2 dir = (to - from).Normalize();
			to -= dir * shortage; // 부족한 만큼 뒤로 당기기
			dist = remainingWidth; // dist 재계산 안 해도 됨, 위에서 보정됨
		}

		Vector2 midPos = (from + to) * 0.5f;

		D2D1_RECT_F srcRect = {
			currentX,
			0.0f,
			currentX + dist, // dist = 거리, currentX = 이전 마지막 지점
			sliceH
		};

		float angle = atan2f(to.y - from.y, to.x - from.x); // 아크 탄젠트 값을 라디안으로 변환, 기울기 -> 라디안

		

		pieces.push_back({ srcRect ,angle, midPos, dist, 1.0f, 1.0f });
		currentX += dist;
	}

	totalLength = currentX;
	isPlay = true; // 고고혓 
}

void ChainDrawerComponent::OnStart()
{
	bmpSize = baseBitmap->GetBitmap()->GetSize();
}

void ChainDrawerComponent::OnCreate() {
	
}

void ChainDrawerComponent::Render(D2DRenderManager* manager) // 사실상, trailComponent 내부에 보간식을 떼온거임
{
	Draw(manager);
}

void ChainDrawerComponent::Draw(D2DRenderManager* manager)
{
	if (!IsActiveSelf()) return; // 비활성화 얼리리턴

	for (auto& pi : pieces) {
		float width = pi.rect.right - pi.rect.left;
		float height = pi.rect.bottom - pi.rect.top;

		D2D1_RECT_F destRect = {
			pi.pos.x - width * 0.5f,
			pi.pos.y - height * 0.5f,
			pi.pos.x + width * 0.5f,
			pi.pos.y + height * 0.5f
		};

		D2D1_POINT_2F center = { pi.pos.x, pi.pos.y };

		D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Rotation(pi.angle * 180.0f / PI, center);
		manager->SetRenderTransform(transform);

		manager->DrawBitmap(baseBitmap->GetBitmap(), destRect, pi.rect, 1.0f);
		if (pi.fillAmount > 0.0f) {
			D2D1_RECT_F fillSrcRect = pi.rect;
			fillSrcRect.right = fillSrcRect.left + width * pi.fillAmount;

			float displayWidth = width * pi.fillAmount;
			D2D1_RECT_F partialDestRect = {
			pi.pos.x - width * 0.5f,                // 왼쪽은 고정
			pi.pos.y - height * 0.5f,
			(pi.pos.x - width * 0.5f) + displayWidth, // 오른쪽만 늘어남
			pi.pos.y + height * 0.5f
			};

			manager->DrawBitmap(fillBitmap->GetBitmap(), partialDestRect, fillSrcRect, 1.0f);
		}
	}
}

void ChainDrawerComponent::Progress(float value)
{
	if (totalLength <= 0.0f) return;

	float targetLength = totalLength * value; // value는 0~1이 보장되야함 clamp안함
	float remaining = targetLength; // 남은 값이라는 뜻

	for (auto& p : pieces) { // 양동이에 물 채우는거랑 방식임
		if (remaining >= p.length) {
			p.fillAmount = 1.0f; // 꽉참
			remaining -= p.length; // 채운만큼 빼줌
		}
		else if (remaining > 0.0f) { // 애매하게 남은경우에 해당함
			p.fillAmount = remaining / p.length;
			remaining = 0.0f;
		}
		else { // 전혀 안남은 경우
			p.fillAmount = 0.0f;
		}
	}
}

void ChainDrawerComponent::SetBitmap(std::wstring path)
{
	baseBitmap = resourceManager->CreateBitmapResource(path);	
	fillBitmap = baseBitmap; // 일단 넣어
}

void ChainDrawerComponent::SetFillBitmap(std::wstring path)
{
	fillBitmap = resourceManager->CreateBitmapResource(path);
}

void ChainDrawerComponent::SetupNodes(Vector2 node, float interval)
{	
	for (int i = 0; i < 9; ++i) {
		int col = i % 3 - 1; // -1 0 1
		int row = i / 3 - 1;

		positions[i] = {
			node.x + interval * col,
			node.y + interval * row
		};		
	}
}

