#include "EscContinueButton.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"

void EscContinueButton::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);

	continueButton = owner->AddComponent<Button>();
	owner->GetTransform().SetUnityCoords(false);
}

void EscContinueButton::OnStart()
{
	continueButton->SetNormalImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_continue.png");
	continueButton->SetHoverImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_continue.png");
	continueButton->SetPressedImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_continue.png");

	D2D1_SIZE_F size = continueButton->GetNormalImage()->GetResource()->GetBitmap()->GetSize();
	continueButton->SetRect(size.width, size.height);

	continueButton->GetNormalImage()->SetOrderInLayer(2200);
	continueButton->GetHoverImage()->SetOrderInLayer(2200);
	continueButton->GetPressedImage()->SetOrderInLayer(2200);
}
