#include "StageResult.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Datas/EngineData.h"
#include "Application/AppPaths.h"
#include "Platform/Input.h"
#include "Math/EasingFunction.h"
#include "Utils/GameTime.h"

void StageResult::OnCreate()
{
	// winPanel 초기화
	GameObject* winPanelObject = new GameObject();
	winPanelObject->GetTransform().SetUnityCoords(false);
	winPanelObject->SetRenderLayer(EngineData::RenderLayer::UI);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(winPanelObject);
	
	winPanel = winPanelObject->AddComponent<BitmapRenderer>();
	winPanel->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Result\\victory_ui_1.png");


	winPanelObject->GetTransform().SetPosition(93.5f, 159.0f);
	winPanel->SetOrderInLayer(20000);

	// winMark 초기화
	GameObject* winMarkObject = new GameObject();
	winMarkObject->GetTransform().SetUnityCoords(false);
	winMarkObject->SetRenderLayer(EngineData::RenderLayer::UI);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(winMarkObject);
	
	winMark = winMarkObject->AddComponent<BitmapRenderer>();
	winMark->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Result\\victory_ui_b2.png");

	
	winMarkObject->GetTransform().SetPosition(93.5f, 159.0f);
	winMark->SetOrderInLayer(20000);

	// defeatPanel 초기화

	GameObject* defeatPanelObject = new GameObject();
	defeatPanelObject->SetRenderLayer(EngineData::RenderLayer::UI);
	defeatPanelObject->GetTransform().SetUnityCoords(false);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(defeatPanelObject);
	defeatPanel = defeatPanelObject->AddComponent<BitmapRenderer>();
	defeatPanel->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Result\\defeat_ui_1.png");


	defeatPanelObject->GetTransform().SetPosition(93.5f, 159.0f);
	defeatPanel->SetOrderInLayer(20000);

	// defeatMark 초기화
	GameObject* defeatMarkObject = new GameObject();
	defeatMarkObject->SetRenderLayer(EngineData::RenderLayer::UI);
	defeatMarkObject->GetTransform().SetUnityCoords(false);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(defeatMarkObject);
	defeatMark = defeatMarkObject->AddComponent<BitmapRenderer>();
	defeatMark->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Result\\defeat_ui_b2.png");

	
	defeatMarkObject->GetTransform().SetPosition(93.5f, 159.0f);
	defeatMark->SetOrderInLayer(20000);
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
	if (timer < 1.0f) 
	{
		GameObject* winMarkObj = winMark->owner;
		D2D1_SIZE_F size = winMark->GetResource()->GetBitmap()->GetSize();
		timer += Singleton<GameTime>::GetInstance().GetDeltaTime() / 3.0f;
		float y = EasingList[EasingEffect::OutQuint](timer);

		// 현재 스케일 비율
		float scale = 2 - y;

		// 이미지 중심이 원점에 오도록 위치 보정
		float offsetX = -(size.width * 0.7f * (scale - 1.0f) * 0.5f);
		float offsetY = -(size.height * (scale - 1.0f) * 0.5f);

		winMarkObj->GetTransform().SetScale(scale, scale);
		winMarkObj->GetTransform().SetPosition(offsetX + size.height * 0.1f, offsetY + size.height * 0.2f);
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
		winMark->SetActive(true);
		defeatPanel->SetActive(false);
		defeatMark->SetActive(false);
		break;
	case Defeat:
		winPanel->SetActive(false);
		winMark->SetActive(false);
		defeatPanel->SetActive(true);
		defeatMark->SetActive(true);
		break;
	}
}
