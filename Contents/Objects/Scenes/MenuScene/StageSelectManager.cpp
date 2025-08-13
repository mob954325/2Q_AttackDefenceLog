#include "StageSelectManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "Utils/GameTime.h"
#include "Scripts/GameManager.h"

void StageSelectManager::OnCreate()
{
}

void StageSelectManager::OnStart()
{
	CreateMenuObjects();
	ChangeImageByClearState();

	objs[0]->owner->GetTransform().SetPosition(-400, 200);
	objs[1]->owner->GetTransform().SetPosition(0, 0);
	objs[2]->owner->GetTransform().SetPosition(400, 400);
	  
	objs[0]->AddEvent([this]() 
		{
			if (Singleton<GameManager>::GetInstance().IsStage1Clear()) return;

			if (!isSceneChange)
			{
				Singleton<GameManager>::GetInstance().SetBattleStage(SceneCount::STAGE1);
				isSceneChange = true;
			}
		});
	objs[1]->AddEvent([this]() 
		{ 
			if (Singleton<GameManager>::GetInstance().IsStage2Clear()) return;

			if (!isSceneChange)
			{
				Singleton<GameManager>::GetInstance().SetBattleStage(SceneCount::STAGE2);
				isSceneChange = true;
			}
		});
	objs[2]->AddEvent([this]() 
		{ 
			if (Singleton<GameManager>::GetInstance().IsStage3Clear()) return;

			if (!isSceneChange)
			{
				Singleton<GameManager>::GetInstance().SetBattleStage(SceneCount::STAGE3);
				isSceneChange = true;
			}
		});
}

void StageSelectManager::OnUpdate()
{
	if (isSceneChange)
	{
		timer += Singleton<GameTime>::GetInstance().GetDeltaTime();

		if(timer >= maxTimer)
		{
			Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::SELECT);
		}
	}
}

void StageSelectManager::OnDestroy()
{
	objs.clear();
}

void StageSelectManager::CreateMenuObjects() 
{
	for (int i = 0; i < 3; i++)
	{
		GameObject* obj = new GameObject();
		obj->SetName("stage" + std::to_string(i + 1));
		obj->GetTransform().SetParent(&(this->owner->GetTransform()));

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		SliceableObject* comp = obj->AddComponent<SliceableObject>();
		objs.push_back(comp);
	}

}

void StageSelectManager::ChangeImageByClearState()
{
	if (!Singleton<GameManager>::GetInstance().IsStage1Clear())
	{
		objs[0]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\enemySelect\\robby_select_ui_mountain_front.png");
	}
	else
	{
		objs[0]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\TestClear\\TestClear.png");
	}

	if (!Singleton<GameManager>::GetInstance().IsStage2Clear())
	{
		objs[1]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\enemySelect\\robby_select_ui_mountain_peak.png");
	}
	else
	{
		objs[1]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\TestClear\\TestClear.png");
	}

	if (!Singleton<GameManager>::GetInstance().IsStage3Clear())
	{
		objs[2]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\enemySelect\\robby_select_ui_namgung.png");
	}
	else
	{
		objs[2]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\TestClear\\TestClear.png");
	}
}