#include "ChainDrawerComponent.h"
#include "Utils/GameTime.h"
#include "Resources/ResourceManager.h"

constexpr float PI = 3.141592654f; // 이건 진짜진짜 ㄹㅇ 유명한 파이임

void ChainDrawerComponent::OnStart() 
{



}

void ChainDrawerComponent::Render(D2DRenderManager* manager) // 사실상, trailComponent 내부에 보간식을 떼온거임
{


	Draw(manager);


}

void ChainDrawerComponent::Draw(D2DRenderManager* manager)
{
	if (!IsActiveSelf()) return; // 비활성화 얼리리턴

	D2D1_SIZE_F bmpSize = baseBitmap->GetBitmap()->GetSize(); // 사이즈 대충 구해서 중앙기준으로
	D2D1_RECT_F srcRect = { 0.0f, 0.0f,	bmpSize.width, bmpSize.height };
	
// 	D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Rotation( // 회전 행렬 생성하는거임
// 		180.0f / PI,
// 		{ 0,0 }
// 	);

	D2D1_RECT_F destRect = { // 대충 이미지 정 가운데 기준
		bmpSize.width * 0.5f,
		bmpSize.height * 0.5f,
		bmpSize.width * 0.5f,
		bmpSize.height * 0.5f,
	};

	//manager->SetRenderTransform(transform);

	manager->DrawBitmap(baseBitmap->GetBitmap(), destRect, srcRect, 1.0f);

}

void ChainDrawerComponent::CalcNormalizedRect(float value)
{







}



