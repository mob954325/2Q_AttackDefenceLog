#include "EscMuteButton.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"

void EscMuteButton::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);

	muteButton = owner->AddComponent<Button>();
	owner->GetTransform().SetUnityCoords(false);

	GameObject* obj = new GameObject();
	soundMutePanel = obj->AddComponent<SoundMutePanel>();
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
}

void EscMuteButton::OnStart()
{
	muteButton->SetNormalImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\SoundControl\\esc_menu_ui_sound.png");
	muteButton->SetHoverImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\SoundControl\\esc_menu_ui_sound.png");
	muteButton->SetPressedImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\SoundControl\\esc_menu_ui_sound.png");

	D2D1_SIZE_F size = muteButton->GetNormalImage()->GetResource()->GetBitmap()->GetSize();
	muteButton->SetRect(size.width, size.height);

	muteButton->GetNormalImage()->SetOrderInLayer(2200);
	muteButton->GetHoverImage()->SetOrderInLayer(2200);
	muteButton->GetPressedImage()->SetOrderInLayer(2200);
}

SoundMutePanel* EscMuteButton::GetSoundMutePanel()
{
	return soundMutePanel;
}
