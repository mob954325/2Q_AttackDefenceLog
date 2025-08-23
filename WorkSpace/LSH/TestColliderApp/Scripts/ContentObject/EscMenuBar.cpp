#include "EscMenuBar.h"
#include "Scene/SceneManager.h"
#include "Utils/GameTime.h"
#include "Application/AppPaths.h"

void EscMenuBar::OnCreate()
{
	br = owner->AddComponent<BitmapRenderer>();
	br->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_bar.png");
}

void EscMenuBar::OnStart()
{
	CreateMenuObjects();
	objs[0]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_continue.png");
	objs[1]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_exit.png");
	objs[2]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_sound.png");

	for (int i = 0; i < objs.size(); i++)
	{
		objs[i]->owner->GetTransform().SetPosition(width / 3 * i, 0);
		objs[i]->AddEvent([&]() { std::cout << "외부등록 " << std::endl; });
	}

}

void EscMenuBar::CreateMenuObjects()
{
	for (int i = 0; i < 3; i++)
	{
		GameObject* obj = new GameObject();
		obj->SetName("menuObj" + std::to_string(i));
		obj->GetTransform().SetParent(&(this->owner->GetTransform()));

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		auto comp = obj->AddComponent<SliceableMenu>();
		objs.push_back(comp);
	}
}
