#include "StageBGI.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"


void StageBGI::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true);

	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\arena-1.png");
	bitmapRenderer->SetOrderInLayer(-10);

	vignette = owner->AddComponent<VignetteEffect>();
	vignette->SetBitmap(bitmapRenderer->GetResource()->GetBitmap().Get());
	vignette->SetColor({ 0.0f, 0.0f,0.0f,1.0f }); // 검정색
	vignette->SetEffectSize(1.0f); // 몰?루 사이즈	
	vignette->SetOrderInLayer(-9); //무조건 원본보다 높게
	vignette->SetStrength(0.0f); //이거로 조정함

	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);
}

void StageBGI::OnUpdate()
{
	if (!isPlay) return;

	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();

	if (isGoingFillUp) { // 차오름
		progress += 0.5f * delta;
		if (progress >= 1.0f) isPlay = false;
	}
	else // 감소함
	{
		progress -= 0.7f * delta;
		if (progress <= 0.0f) isPlay = false;
	}

	progress = clampf(progress, 0.0f, 1.0f);

	vignette->SetStrength(progress); //이거로 조정함
}

void StageBGI::OnDestroy()
{

}

void StageBGI::Start() // 0 -> 1
{
	isGoingFillUp = true;
	progress = 0.0f;
	isPlay = true;
}

void StageBGI::End() // 1 -> 0
{
	if (!isGoingFillUp) return;

	isGoingFillUp = false;	
	progress = 1.0f;
	isPlay = true;
}


