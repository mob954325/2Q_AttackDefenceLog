#include "LevelSelectManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "Utils/GameTime.h"
#include "Scripts/GameManager.h"

void LevelSelectManager::OnCreate()
{
}

void LevelSelectManager::OnStart()
{
	CreateMenuObjects();

	objs[0]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\diffcult\\easy_ui.png");
	objs[1]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\diffcult\\nomal_ui.png");
	objs[2]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\diffcult\\difficult_ui.png");

	objs[0]->owner->GetTransform().SetPosition(-400, 0);
	objs[1]->owner->GetTransform().SetPosition(0, 0);
	objs[2]->owner->GetTransform().SetPosition(400, 0);

	objs[0]->AddEvent([this]()
		{
			if (!isSceneChange)
			{
				isSceneChange = true; // NOTE : 나중에 난이도 세팅하기
			}
		});
	// objs[1]->AddEvent([this]() 
	// 	{ 
	// 		if (!isSceneChange)
	// 		{
	// 			Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::STAGE2);
	// 			isSceneChange = true;
	// 		}
	// 	});
	// objs[2]->AddEvent([this]() 
	// 	{ 
	// 		if (!isSceneChange)
	// 		{
	// 			Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::STAGE3);
	// 			isSceneChange = true;
	// 		}
	// 	});
}

void LevelSelectManager::OnUpdate()
{
	if (isSceneChange)
	{
		timer += Singleton<GameTime>::GetInstance().GetDeltaTime();

		if (timer >= maxTimer)
		{
			Singleton<SceneManager>::GetInstance().LoadScene(Singleton<GameManager>::GetInstance().GetTargetBattleStage());
		}
	}
}

void LevelSelectManager::OnDestroy()
{
	objs.clear();
}

void LevelSelectManager::CreateMenuObjects()
{
	for (int i = 0; i < 3; i++)
	{
		GameObject* obj = new GameObject();
		obj->SetName("stage" + std::to_string(i + 1));

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		SliceableObject* comp = obj->AddComponent<SliceableObject>();
		objs.push_back(comp);
	}

	int startX = EngineData::SceenWidth * 0.3f;
	Vector2 ownerPos = owner->GetTransform().GetPosition();
	float gap = 250.0f;

	// 위치 맞추기
	for (int i = 0; i < objs.size(); i++)
	{
		objs[i]->owner->GetTransform().SetPosition(startX + gap * i, ownerPos.y);
	}
}