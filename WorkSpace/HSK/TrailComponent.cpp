#include "TrailComponent.h"
#include "Components/Camera/Camera.h"
#include "Scene/SceneManager.h"

#include "Utils/GameTime.h"
#include "Datas/SpriteDatas.h"
#include "Utils/DebugUtility.h"

#define pipi 3.141592654f // 삐삐

void TrailComponent::Update(float currentTime) {

}

void TrailComponent::AddStamp(D2D1_POINT_2F pos, float angle, float time) {
	if (!trails.empty()) {

	}
	trailStamps.push_back({ pos, angle, time });

}

void TrailComponent::Draw(ID2D1RenderTarget* rt) {
	for (auto& stamp : trails) {
		D2D1_SIZE_F bmpSize = stampBitmap->GetSize();
		D2D1_RECT_F destRect = { // 대충 이미지 정 가운데 기준
		 stamp.position.x - bmpSize.width * 0.5f,
		 stamp.position.y - bmpSize.height * 0.5f,
		 stamp.position.x + bmpSize.width * 0.5f,
		 stamp.position.y + bmpSize.height * 0.5f,
		};

		D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Rotation(
			stamp.angle * 180.0f / pipi, // 
			stamp.position
		);

		rt->SetTransform(transform);
		rt->DrawBitmap(stampBitmap, destRect);
	}

	rt->SetTransform(D2D1::Matrix3x2F::Identity());
}

void TrailComponent::Render(D2DRenderManager* manager)
{
	owner->GetTransform().GetFinalMatrix();
}



