#include "PatternDrawerComponent.h"
#include "Scene/SceneManager.h"
#include "Utils/GameTime.h"
#include "Resources/ResourceManager.h"

constexpr float PI = 3.141592654f; // 이건 진짜진짜 유명한 파이임

void PatternDrawerComponent::Draw(const std::queue<Line>& lines)
{	
	linesToDraw.clear();

	std::queue<Line> copy = lines;
	while (!copy.empty()) {
		linesToDraw.push_back(copy.front());
		copy.pop();
	}

	isPlaying = true; // 그릴 게 있으면
}

void PatternDrawerComponent::Render(D2DRenderManager* manager)
{
	if (!IsActiveSelf()) return; // 비활성화 얼리리턴

	if (!isPlaying || !stampBmp) return;

	timer += GameTime::GetInstance().GetDeltaTime();
	if (timer >= 1.0f) {
		isPlaying = false;
	}

	auto bmpSize = stampBmp->GetBitmap()->GetSize();
	D2D1_RECT_F srcRect = { 0, 0, bmpSize.width, bmpSize.height };

	for (auto& line : linesToDraw) {
		Vector2 from = line.from;
		Vector2 to = line.to;

		Vector2 delta = to - from;
		float dist = sqrtf(delta.x * delta.x + delta.y * delta.y);
		int steps = static_cast<int>(dist / 10.0f); // 커스텀 지점임
		if (steps < 1)
			steps = 1;

		for (int i = 0; i <= steps; ++i) {
			float t = static_cast<float>(i) / steps;
			Vector2 pos = from + delta * t;

			D2D1_RECT_F dest = {
				pos.x - bmpSize.width * 0.5f,
				pos.y - bmpSize.height * 0.5f,
				pos.x + bmpSize.width * 0.5f,
				pos.y + bmpSize.height * 0.5f
			};

			float angle = atan2f(delta.y, delta.x) * 180.0f / PI;
			auto transform = D2D1::Matrix3x2F::Rotation(angle, { pos.x, pos.y });

			manager->SetRenderTransform(transform);
			manager->DrawBitmap(stampBmp->GetBitmap().Get(), dest, srcRect);
		}
	}	
}

void PatternDrawerComponent::SetBitmap(std::wstring path)
{
	stampBmp = resourceManager->CreateBitmapResource(path);
}
