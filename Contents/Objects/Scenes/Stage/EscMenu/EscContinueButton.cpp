#include "EscContinueButton.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

void EscContinueButton::OnCreate()
{
	continueButton = owner->AddComponent<Button>();
	owner->GetTransform().SetUnityCoords(false);
}

void EscContinueButton::OnStart()
{
	continueButton->SetNormalImage(L"../Resource/UI/MenuUI/esc_menu_ui_continue.png");
	continueButton->SetHoverImage(L"../Resource/UI/MenuUI/esc_menu_ui_continue.png");
	continueButton->SetPressedImage(L"../Resource/UI/MenuUI/esc_menu_ui_continue.png");

	D2D1_SIZE_F size = continueButton->GetNormalImage()->GetResource()->GetBitmap()->GetSize();
	continueButton->SetRect(size.width, size.height);
}
