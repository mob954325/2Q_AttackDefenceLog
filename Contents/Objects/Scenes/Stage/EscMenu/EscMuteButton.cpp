#include "EscMuteButton.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

void EscMuteButton::OnCreate()
{
	muteButton = owner->AddComponent<Button>();
	owner->GetTransform().SetUnityCoords(false);

	muteButton->AddOnClickEvent([this]() { std::cout << "mute button event" << std::endl; }); // TODO : 나중에 소리 관련 내용 추가할 것
}

void EscMuteButton::OnStart()
{
	muteButton->SetNormalImage(L"../Resource/UI/MenuUI/esc_menu_ui_sound.png");
	muteButton->SetHoverImage(L"../Resource/UI/MenuUI/esc_menu_ui_sound.png");
	muteButton->SetPressedImage(L"../Resource/UI/MenuUI/esc_menu_ui_sound.png");

	D2D1_SIZE_F size = muteButton->GetNormalImage()->GetResource()->GetBitmap()->GetSize();
	muteButton->SetRect(size.width, size.height);
}
