#include "SelectSeal.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"
#include "Scene/SceneManager.h"
#include "Utils/GameTime.h"

void SelectSeal::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);
	owner->GetTransform().SetScale(0.7f, 0.7f);
	// owner->GetTransform().SetUnityCoords(false);

	left = owner->AddComponent<BitmapRenderer>();
	left->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Seal\\seal_breaking_02.png");
	left->SetUseCustomRect(true);
	left->SetOrderInLayer(1000);

	right = owner->AddComponent<BitmapRenderer>();
	right->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Seal\\seal_breaking_01.png");
	right->SetUseCustomRect(true);
	right->SetOrderInLayer(1000);
}

void SelectSeal::OnStart()
{
}

void SelectSeal::OnUpdate()
{

	if (!go) {
		timer += Singleton<GameTime>::GetInstance().GetDeltaTime();

		if (timer > readyTimer) {
			go = true;
			timer = 0.0f;
		}
		else
			return;
	}

	if (!isRighDone)
	{
		if (timer < maxTimer)
		{
			float rectY = left->GetResource()->GetBitmap()->GetSize().height * timer / maxTimer;

			right->SetDestRect({ 0, 0, right->GetResource()->GetBitmap()->GetSize().width, rectY });
			right->SetSrcRect({ 0, 0, right->GetResource()->GetBitmap()->GetSize().width, rectY });

			timer += Singleton<GameTime>::GetInstance().GetDeltaTime();
		}
		else
		{
			isRighDone = true;
			timer = 0.0f;
		}
	}
	else // left
	{
		if (timer < maxTimer)
		{
			float rectY = left->GetResource()->GetBitmap()->GetSize().height * timer / maxTimer;

			left->SetDestRect({ 0, 0, left->GetResource()->GetBitmap()->GetSize().width, rectY });
			left->SetSrcRect({ 0, 0, left->GetResource()->GetBitmap()->GetSize().width, rectY });

			timer += Singleton<GameTime>::GetInstance().GetDeltaTime();
		}
	}
}