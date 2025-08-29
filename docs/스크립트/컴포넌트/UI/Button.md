# InputSystem

---

경로 : Compnents/UI/Button

## 설명

버튼처럼 사용할 수 있는 UI 컴포넌트

## 예시 코드

버튼 컴포넌트 셋업

### .cpp

```cpp
#include "EscExitButton.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"

void EscExitButton::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);

	toTitleButton = owner->AddComponent<Button>();
	owner->GetTransform().SetUnityCoords(false);
}

void EscExitButton::OnStart()
{
  // 보통 이미지, 호버이미지, 눌렀을 때 이미지 찾기
	toTitleButton->SetNormalImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_exit.png");
	toTitleButton->SetHoverImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_exit.png");
	toTitleButton->SetPressedImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_exit.png");

	D2D1_SIZE_F size = toTitleButton->GetNormalImage()->GetResource()->GetBitmap()->GetSize();
	toTitleButton->SetRect(size.width, size.height); // 마우스가 감지할 크기 -> 내부에서 transform 위치값을 기준으로 rect 생성

  // 이미지 레이어 값 설정
	toTitleButton->GetNormalImage()->SetOrderInLayer(2200);
	toTitleButton->GetHoverImage()->SetOrderInLayer(2200);
	toTitleButton->GetPressedImage()->SetOrderInLayer(2200);

  // 버튼 이벤트 추가
	toTitleButton->AddOnClickEvent([&]() { std::cout << "button pressed !!" << std::endl; });
}

```
