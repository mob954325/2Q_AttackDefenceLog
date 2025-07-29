#include "TrailComponent.h"
#include "Components/Camera/Camera.h"
#include "Scene/SceneManager.h"

#include "Utils/GameTime.h"
#include "Datas/SpriteDatas.h"
#include "Utils/DebugUtility.h"
#include "Resources/ResourceManager.h"

constexpr float PI = 3.141592654f;

void TrailComponent::Update() {

}

void TrailComponent::AddStamp(D2D1_POINT_2F pos) {

	if (trails.empty()) { // 첫 요소는 바로 처리해버림
		trails.push_back({ pos, 0.0f });
		return;
	}

	const TrailStamp& last = trails.back(); // 구조체를 빌려옴
	float dx = pos.x - last.position.x;
	float dy = pos.y - last.position.y;
	float dist = sqrtf(dx * dx + dy * dy); // 제곱해서 더한뒤 루트

	if (dist < minDistance) // 일정거리 이하면 생성안함
		return;

	int steps = static_cast<int>(dist / minDistance); //최소거리가 몇번들어가는지 확인하는거임(무조건 크기 때문에 1이상임)
	for (int i = 1; i <= steps; ++i) {
		float t = static_cast<float>(i) / steps; // 보간식, t + 1/t
		D2D1_POINT_2F interpPos = {
			last.position.x + dx * t,
			last.position.y + dy * t
		};

		float angle = (i == 1) // 첫번째 요소면
			? GetAngle(last.position, interpPos) // 마지막점과
			: GetAngle(trails.back().position, interpPos); // 아니면 마지막 추가된거랑
		trails.push_back({ interpPos, angle });
	}
}

void TrailComponent::Draw(D2DRenderManager* manager) {
	if (!stampBitmap) return;

	for (auto& stamp : trails) { 
		D2D1_SIZE_F bmpSize = stampBitmap->GetBitmap()->GetSize();
		D2D1_RECT_F destRect = { // 대충 이미지 정 가운데 기준
		 stamp.position.x - bmpSize.width * 0.5f,
		 stamp.position.y - bmpSize.height * 0.5f,
		 stamp.position.x + bmpSize.width * 0.5f,
		 stamp.position.y + bmpSize.height * 0.5f,
		};

		D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Rotation(
			stamp.angle * 180.0f / PI,
			stamp.position
		);

		manager->SetBitmapTransform(transform);
		D2D1_RECT_F srcRect = {
			0.0f, 0.0f,
			bmpSize.width, bmpSize.height
		};
		manager->DrawBitmap(stampBitmap->GetBitmap(), destRect, srcRect);
	}	
}

void TrailComponent::Render(D2DRenderManager* manager)
{
	auto tf = owner->GetTransform().GetPosition();
	AddStamp({ tf.x, tf.y });
	Draw(manager);
	Update();
}

void TrailComponent::SetBitmap(std::wstring path)
{
	stampBitmap = resourceManager->CreateBitmapResource(path);
}

void TrailComponent::OnDestroy()
{
	stampBitmap.reset(); // 수정했습니다 20:30 
}
