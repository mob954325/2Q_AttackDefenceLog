#include "StageSelectManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Scripts/SceneCore.h"

void StageSelectManager::OnCreate()
{
}

void StageSelectManager::OnStart()
{
	CreateMenuObjects();

	objs[0]->SetImage(L"../Resource/UI/MenuUI/esc_menu_ui_continue.png");
	objs[1]->SetImage(L"../Resource/UI/MenuUI/esc_menu_ui_exit.png");
	objs[2]->SetImage(L"../Resource/UI/MenuUI/esc_menu_ui_sound.png");

	objs[0]->owner->GetTransform().SetPosition(-400, 200);
	objs[1]->owner->GetTransform().SetPosition(0, 0);
	objs[2]->owner->GetTransform().SetPosition(400, 400);

	objs[0]->AddEvent([&]() 
		{
			if (!isSceneChange)
			{
				Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::STAGE1); 
				isSceneChange = true;
			}
		});
	//objs[1]->AddEvent([&]() 
	//	{ 
	//		if (!isSceneChange)
	//		{
	//			Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::STAGE2);
	//			isSceneChange = true;
	//		}
	//	});
	//objs[2]->AddEvent([&]() 
	//	{ 
	//		if (!isSceneChange)
	//		{
	//			Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::STAGE3);
	//			isSceneChange = true;
	//		}
	//	});
}

void StageSelectManager::CreateMenuObjects()
{
	for (int i = 0; i < 3; i++)
	{
		GameObject* obj = new GameObject();
		obj->SetName("stage" + std::to_string(i + 1));
		obj->GetTransform().SetParent(&(this->owner->GetTransform()));

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		auto comp = obj->AddComponent<SliceableObject>();
		objs.push_back(comp);
	}
}