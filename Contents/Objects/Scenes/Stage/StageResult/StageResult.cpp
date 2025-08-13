#include "StageResult.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Datas/EngineData.h"
#include "Application/AppPaths.h"
#include "Platform/Input.h"
#include "Math/EasingFunction.h"
#include "Utils/GameTime.h"
#include "Objects/Sound/SoundPlayScene.h"

void StageResult::OnCreate()
{
	isSoundPlay = false;
	// winPanel 초기화
	GameObject* winPanelObject = new GameObject();
	winPanelObject->GetTransform().SetUnityCoords(false);
	winPanelObject->SetRenderLayer(EngineData::RenderLayer::UI);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(winPanelObject);
	
	winPanel = winPanelObject->AddComponent<BitmapRenderer>();
	winPanel->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Result\\victory_ui_1.png");
	winPanel->SetOrderInLayer(100000000);

	winPanelObject->GetTransform().SetPosition(93.5f, 159.0f);

	// winMark 초기화
	GameObject* winMarkObject = new GameObject();
	winMarkObject->GetTransform().SetUnityCoords(false);
	winMarkObject->SetRenderLayer(EngineData::RenderLayer::UI);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(winMarkObject);
	
	winMark = winMarkObject->AddComponent<BitmapRenderer>();
	winMark->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Result\\victory_ui_b2.png");
	winMark->SetOrderInLayer(100000000);

	
	winMarkObject->GetTransform().SetPosition(93.5f, 159.0f);

	// defeatPanel 초기화

	GameObject* defeatPanelObject = new GameObject();
	defeatPanelObject->SetRenderLayer(EngineData::RenderLayer::UI);
	defeatPanelObject->GetTransform().SetUnityCoords(false);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(defeatPanelObject);
	defeatPanel = defeatPanelObject->AddComponent<BitmapRenderer>();
	defeatPanel->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Result\\defeat_ui_1.png");
	defeatPanel->SetOrderInLayer(100000000);


	defeatPanelObject->GetTransform().SetPosition(93.5f, 159.0f);

	// defeatMark 초기화
	GameObject* defeatMarkObject = new GameObject();
	defeatMarkObject->SetRenderLayer(EngineData::RenderLayer::UI);
	defeatMarkObject->GetTransform().SetUnityCoords(false);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(defeatMarkObject);
	defeatMark = defeatMarkObject->AddComponent<BitmapRenderer>();
	defeatMark->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Result\\defeat_ui_b2.png");
	defeatMark->SetOrderInLayer(100000000);

	
	defeatMarkObject->GetTransform().SetPosition(93.5f, 159.0f);
}

void StageResult::OnStart()
{
	winPanel->SetActive(false);
	winMark->SetActive(false);

	defeatPanel->SetActive(false);
	defeatMark->SetActive(false);
}

void StageResult::OnUpdate()
{
	if (timer < 1.5f) 
	{
		timer += Singleton<GameTime>::GetInstance().GetDeltaTime();
	}	
	else
	{
		// 도장
		if (winPanel->IsActiveSelf())
		{
			winMark->SetActive(true);

			if (!isSoundPlay)
			{
				auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Stamp");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();
				}
				isSoundPlay = true;
			}
		}
		else
		{
			defeatMark->SetActive(true);

			if (!isSoundPlay)
			{
				auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Stamp");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();
				}
				isSoundPlay = true;
			}
		}
	}
}

void StageResult::SetPanelState(ResultPanelState state)
{

	switch (state)
	{
	case None:
		winPanel->SetActive(false);
		winMark->SetActive(false);
		defeatPanel->SetActive(false);
		defeatMark->SetActive(false);
		break;
	case Win:
		winPanel->SetActive(true);
		winMark->SetActive(false);
		defeatPanel->SetActive(false);
		defeatMark->SetActive(false);
		break;
	case Defeat:
		winPanel->SetActive(false);
		winMark->SetActive(false);
		defeatPanel->SetActive(true);
		defeatMark->SetActive(false);
		break;
	}
}
