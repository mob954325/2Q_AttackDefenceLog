#include "TutorialNumObject.h"
#include "Application/AppPaths.h"
#include "../Engine/Scene/SceneManager.h"


void TutorialNumObject::OnCreate()
{
	GameObject* obj = new GameObject();
	//	obj->GetTransform().SetUnityCoords(false);
	obj->SetRenderLayer(EngineData::RenderLayer::UI);

	baseNum = obj->AddComponent<BitmapRenderer>();
	baseNum->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Number\\3_text.png");
	baseNum->SetOrderInLayer(150);

	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj, "baseNumber");

	GameObject* obj2 = new GameObject();
	//	obj2->GetTransform().SetUnityCoords(false);
	obj2->SetRenderLayer(EngineData::RenderLayer::UI);

	slash = obj2->AddComponent<BitmapRenderer>();
	slash->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Number\\slash_text.png");
	slash->SetOrderInLayer(150);

	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj2, "slash");

	std::wstring files[] = {
		L"0_text.png",
		L"1_text.png",
		L"2_text.png",
		L"3_text.png",
	};

	for (int i = 0; i < std::size(files); ++i) {
		GameObject* ob = new GameObject();
		//		ob->GetTransform().SetUnityCoords(false);
		ob->SetRenderLayer(EngineData::RenderLayer::UI);

		auto com = ob->AddComponent<BitmapRenderer>();
		com->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Number\\" + files[i]);
		com->SetOrderInLayer(150);

		currentNum.push_back(com);
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(ob, "currentNum." + i);
	}

	//	SetPos({ 0,0 });
	//	Show(1);
	Hide();
}


void TutorialNumObject::OnStart()
{

}

void TutorialNumObject::OnUpdate()
{

}

void TutorialNumObject::Show(int n)
{
	baseNum->SetActive(true);
	slash->SetActive(true);

	for (int i = 0; i < currentNum.size(); ++i) {
		if (i == n)
			currentNum[i]->SetActive(true);
		else
			currentNum[i]->SetActive(false);
	}
}

void TutorialNumObject::Hide()
{
	baseNum->SetActive(false);
	slash->SetActive(false);

	for (auto& it : currentNum) {
		it->SetActive(false);
	}
}

void TutorialNumObject::SetPos(Vector2 pos)
{
	slash->owner->GetTransform().SetPosition(pos.x, pos.y);
	baseNum->owner->GetTransform().SetPosition(pos.x + 50.0f, pos.y);
	for (auto& it : currentNum) {
		it->owner->GetTransform().SetPosition(pos.x - 50.0f, pos.y);
	}
}
