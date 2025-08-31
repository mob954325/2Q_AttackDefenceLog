#include "Vignette.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"

void Vignette::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true);
	owner->GetTransform().SetScale(0.85f, 0.85f);
		
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\BackGround\\side_darkness.png");

	player = owner->AddComponent<BitmapRenderer>();
	player->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\BattlePanel\\GuideText\\connect_all_the_dots_at_once.png");

	enemy = owner->AddComponent<BitmapRenderer>();
	enemy->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\BattlePanel\\GuideText\\enemy_attack_text.png");	
}

void Vignette::OnStart()
{
	bitmapRenderer->SetOrderInLayer(1200);
	player->SetOrderInLayer(1201);
	enemy->SetOrderInLayer(1201);

	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);

	End();
	progress = 0.0f;
	enemy->SetCapacity(progress);
	player->SetCapacity(progress);
}

void Vignette::OnUpdate()
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

	bitmapRenderer->SetCapacity(progress);
	if (isPlayer) {
		player->SetCapacity(progress);
	}
	else {
		enemy->SetCapacity(progress);
	}	
}

D2D1_SIZE_F Vignette::GetSize()
{
	return size;
}

void Vignette::Start(bool isPl)
{	
	isGoingFillUp = true;
	progress = 0.0f;
	enemy->SetCapacity(progress);
	player->SetCapacity(progress);
	isPlay = true;
	isPlayer = isPl;
}

void Vignette::End(bool isPl)
{
	if (!isGoingFillUp) return;
	
	isGoingFillUp = false;
	progress = 1.0f;
	isPlay = true;
	isPlayer = isPl;
}