#include "EscExitButton.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"

void EscExitButton::OnCreate()
{
	toTitleButton = owner->AddComponent<Button>();
	owner->GetTransform().SetUnityCoords(false);

	toTitleButton->AddOnClickEvent([this]() { Singleton<SceneManager>::GetInstance().LoadScene(1); });
}

void EscExitButton::OnStart()
{
	toTitleButton->SetNormalImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\MenuUI\\esc_menu_ui_exit.png");
	toTitleButton->SetHoverImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\MenuUI\\esc_menu_ui_exit.png");
	toTitleButton->SetPressedImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\MenuUI\\esc_menu_ui_exit.png");

	D2D1_SIZE_F size = toTitleButton->GetNormalImage()->GetResource()->GetBitmap()->GetSize();
	toTitleButton->SetRect(size.width, size.height);
}
