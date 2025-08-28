#include "SelectSceneBGI.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "../Engine/Utils/GameTime.h"
#include "Application/AppPaths.h"

void SelectSceneBGI::OnStart()
{	
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true);

	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\BackGround\\lobby\\robby_background.png");
	bitmapRenderer->SetOrderInLayer(-200);

	bitmapRenderer2 = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer2->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\BackGround\\lobby\\select_level_text.png");
	bitmapRenderer2->SetOrderInLayer(-190);

	vig = owner->AddComponent<BitmapRenderer>();
	vig->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\BackGround\\side_darkness.png");
	vig->SetOrderInLayer(-190);
	alpha = 0.0f;
	vig->SetCapacity(alpha);

	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);
}

void SelectSceneBGI::OnUpdate()
{
	if (alpha < 1.0f) {
		alpha += Singleton<GameTime>::GetInstance().GetDeltaTime();			
		if (alpha >= 1.0f) alpha = 1.0f;
		vig->SetCapacity(alpha);
	}	
}

void SelectSceneBGI::OnDestroy()
{
}


