#include "AnimatedChainEffect.h"
#include "Resources/ResourceManager.h"
#include "../Engine/Utils/GameTime.h"
#include <cmath>
#include "Application/AppPaths.h"

constexpr float PI = 3.141592654f; // 3. 1415926535 8979323846 2643383279 5028841971 6939937510 5820974944 5923078164 0628620899 8628034825 이 얼마나 멋진 숫자인가

// static inline float Magnitude(const Vector2& v) { return v.Magnituede(); }
// static inline Vector2 Normalize(const Vector2& v) { return v.Normalize(); }

//=======================================================================================

void AnimatedChainEffect::SetupNodes(Vector2 center, float interval)
{
	for (int i = 0; i < 9; ++i) {
		int col = i % 3 - 1;
		int row = i / 3 - 1;
		positions[i] = { center.x + interval * col, center.y + interval * row };
	}
}

//=======================================================================================

void AnimatedChainEffect::Render(D2DRenderManager* manager)
{
	if (!isPlaying || !IsActiveSelf()) return;

	timer += Singleton<GameTime>::GetInstance().GetDeltaTime();
	
	int safety = 4; // 세이프티 캡 - 4번이상 넘어가면 while 나가게
	while (timer >= frameDur && safety-- > 0) {

		timer -= frameDur;
		++currentFrame;

		if (currentFrame >= maxFrame) {
			currentFrame = maxFrame - 1; // 마지막 프레임으로 고정
			Draw(manager);               // 마지막 프레임 1프레임 보여줌
			isPlaying = false;
			OnFinished.Invoke();
			return;
		}
	}

	Draw(manager);
}

void AnimatedChainEffect::OnCreate() {
	//"C:\Users\User\Documents\GitHub\Kyu1\Resource\ContentsResource\attack_line_spreadsheet.png"
	SetAtlasStrip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\Effect\\AttackLine\\attack_line_spreadsheet.png", 9); // 경로 + 프레임 수
	flashBitmap = resourceManager->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\Effect\\AttackLine\\attack_line_circle.png");
	flashSize = flashBitmap->GetBitmap()->GetSize();
}

void AnimatedChainEffect::OnStart() {

}

//=======================================================================================

void AnimatedChainEffect::SetAtlasStrip(std::wstring path, int maxF)
{
	atlasBitmap = resourceManager->CreateBitmapResource(path);
	size = atlasBitmap->GetBitmap()->GetSize();

	maxFrame = maxF;

	frameH = size.height;
	frameW = size.width / maxFrame;  // 이거 부모가 int인데 되나? 확인해야함
}

//=======================================================================================

void AnimatedChainEffect::PlayOnce(const std::vector<int>& pattern)
{
	currentFrame = 0;
	isPlaying = true;
	timer = 0.0f;

	activeNodes.clear();
	activeNodes = pattern;
	addLastNode = true;
	SliceRect(pattern);

	if (addLastNode) {
		activeNodes.resize(pieces.size() + 1);		
	}
	else {
		activeNodes.resize(pieces.size());
	}
}

//=======================================================================================

void AnimatedChainEffect::SliceRect(const std::vector<int>& pattern)
{
	pieces.clear();
	maxNodeIndex.clear();
	maxNodeIndex.push_back({ 0 });
	if (pattern.size() < 2) return; // 2개 이하면 안보여줌

	float currentX = 0.0f;

	for (int i = 0; i < pattern.size() - 1; ++i) {
		int a = pattern[i];
		int b = pattern[i + 1];

		Vector2 from = positions[a - 1];
		Vector2 to = positions[b - 1];

		Vector2 fromTo = to - from;

		float dist = fromTo.Magnitude(); // 거리

		float remain = frameW - currentX; // 요구사항 
		if (remain <= 0.0f) break; // 요구사항 충족시 탈출

		if (dist > remain) { // 
			Vector2 dir = fromTo.Normalize();
			to = { from.x + dir.x * remain, from.y + dir.y * remain }; // dir = 방향백터
			dist = remain;
			addLastNode = false;
		}

		if (dist <= 0.0f) continue; // 더이상 남은 거리가 없으면 컨티뉴

		// frame = (dist * maxFrame) / frameW, 
		int maxPoint = static_cast<int>((dist + currentX) * (maxFrame - 2) / frameW); // 알파값이 최대가 되는 경우 +2는 프레임의 시작과 끝에 1프레임씩 더 있다고 가정 + 등속운동
		maxNodeIndex.push_back({ maxPoint });

		Vector2 mid = { (from.x + to.x) * 0.5f, (from.y + to.y) * 0.5f };
		float angle = std::atan2(to.y - from.y, to.x - from.x);

		D2D1_RECT_F localSrc = { currentX, 0.0f, currentX + dist, frameH };

		pieces.push_back({ localSrc, angle, mid, dist });

		currentX += dist;

		if (currentX >= frameW) break;
		// frameW = 최대크기임 / 아틀라스가 아니라, 해당 프레임의 최대크기, 넘어가면 다음 프레임이 되어버림
	}
}

//=======================================================================================

void AnimatedChainEffect::Draw(D2DRenderManager* manager)
{
	float offsetX = currentFrame * frameW; // 현재 프레임별로 옆으로 밀어주는거임

	for (const auto& pi : pieces) { // 꺾인 조각들
		float width = pi.rect.right - pi.rect.left;
		float height = pi.rect.bottom - pi.rect.top;

		D2D1_RECT_F dest = {
			pi.pos.x - width * 0.5f,
			pi.pos.y - height * 0.5f,
			pi.pos.x + width * 0.5f,
			pi.pos.y + height * 0.5f
		};

		auto xf = D2D1::Matrix3x2F::Rotation(pi.angle * 180.0f / PI, { pi.pos.x, pi.pos.y });
		manager->SetRenderTransform(xf);

		D2D1_RECT_F src = {
			offsetX + pi.rect.left,
			pi.rect.top,
			offsetX + pi.rect.right,
			pi.rect.bottom
		};

		manager->DrawBitmap(atlasBitmap->GetBitmap(), dest, src);
	}

	auto identity = D2D1::Matrix3x2F::Identity();
	manager->SetRenderTransform(identity);

	for (int i = 0; i < activeNodes.size(); ++i) {
		if (i == 0) continue;

		int nodeIndex = activeNodes[i];
		Vector2 pos = positions[nodeIndex - 1];

		//=======================================================================
		// 기적의 알파값 계산법

		float alpha = 0.0f;
		int point = currentFrame - maxNodeIndex[i].framePointIndex;
		if ( point < 5 && point > -1)
		{
			alpha = 0.6f;
			if (!maxNodeIndex[i].isCalled) {
				OnNodeLightUp.Invoke(nodeIndex); // 1~ 9값이 외부로 반출됨
				maxNodeIndex[i].isCalled = true;
			}			
		}

		//=======================================================================


		D2D1_RECT_F dest = {
			pos.x - flashSize.width * 0.5f,
			pos.y - flashSize.height * 0.5f,
			pos.x + flashSize.width * 0.5f,
			pos.y + flashSize.height * 0.5f
		};

		D2D1_RECT_F src = { 0.0f, 0.0f, flashSize.width, flashSize.height };
		manager->DrawBitmap(flashBitmap->GetBitmap(), dest, src, alpha);
	}
}
