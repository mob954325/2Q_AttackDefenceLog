#include "TutorialEnterObject.h"
#include "Application/AppPaths.h"
#include "../Engine/Scene/SceneManager.h"
#include "Scripts/GameManager.h"

void TutorialEnterObject::OnCreate()
{
	GameObject* yes = new GameObject();
	yesBtn = yes->AddComponent<Button>();
	yes->GetTransform().SetUnityCoords(false);
	yes->SetRenderLayer(EngineData::RenderLayer::UI);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(yes, "enterTutorialYesBtn");

	GameObject* no = new GameObject();
	noBtn = no->AddComponent<Button>();
	no->GetTransform().SetUnityCoords(false);
	no->SetRenderLayer(EngineData::RenderLayer::UI);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(no, "enterTutorialNoBtn");
}


void TutorialEnterObject::OnStart()
{
	// 보통 이미지, 호버이미지, 눌렀을 때 이미지 찾기
	yesBtn->SetNormalImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Tutorial\\yes_button_ui_basic.png");
	yesBtn->SetHoverImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Tutorial\\yes_button_ui_mouse.png");
	yesBtn->SetPressedImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Tutorial\\yes_button_ui_click.png");

	yesBtn->owner->GetTransform().SetPosition(475, 610);

	D2D1_SIZE_F sizeYes = yesBtn->GetNormalImage()->GetResource()->GetBitmap()->GetSize();
	yesBtn->SetRect(sizeYes.width, sizeYes.height); // 마우스가 감지할 크기 -> 내부에서 transform 위치값을 기준으로 rect 생성

	// 이미지 레이어 값 설정
	yesBtn->GetNormalImage()->SetOrderInLayer(2200);
	yesBtn->GetHoverImage()->SetOrderInLayer(2200);
	yesBtn->GetPressedImage()->SetOrderInLayer(2200);

	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(false);
	panel = owner->AddComponent<BitmapRenderer>();
	panel->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\Tutorial\\tutorial_32.png");
	panel->SetOrderInLayer(100);
	//panel->SetActive(false);
	// 
	// 버튼 이벤트 추가
	yesBtn->AddOnClickEvent([&]() {
		std::cout << "[YES]" << std::endl;
		Singleton<GameManager>::GetInstance().wasSelected = true;
		Singleton<GameManager>::GetInstance().SetGameState(Play);

		Singleton<SceneManager>::GetInstance().LoadScene(TUTORIAL);
		});



	// 보통 이미지, 호버이미지, 눌렀을 때 이미지 찾기
	noBtn->SetNormalImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Tutorial\\no_button_ui_basic.png");
	noBtn->SetHoverImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Tutorial\\no_button_ui_mouse.png");
	noBtn->SetPressedImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Tutorial\\no_button_ui_click.png");

	noBtn->owner->GetTransform().SetPosition(1125, 610);

	D2D1_SIZE_F sizeNo = noBtn->GetNormalImage()->GetResource()->GetBitmap()->GetSize();
	noBtn->SetRect(sizeNo.width, sizeNo.height); // 마우스가 감지할 크기 -> 내부에서 transform 위치값을 기준으로 rect 생성

	// 이미지 레이어 값 설정
	noBtn->GetNormalImage()->SetOrderInLayer(2200);
	noBtn->GetHoverImage()->SetOrderInLayer(2200);
	noBtn->GetPressedImage()->SetOrderInLayer(2200);

	// 버튼 이벤트 추가
	noBtn->AddOnClickEvent([&]() {
		std::cout << "[NO]" << std::endl;
		Hide();
		Singleton<GameManager>::GetInstance().wasSelected = true;
		Singleton<GameManager>::GetInstance().SetGameState(Play);		
		Singleton<SceneManager>::GetInstance().LoadScene(MENU); // 로드를 다시 때려버리면, 완벽한 초기화가 된다 이말씀임
		});


	if (Singleton<GameManager>::GetInstance().wasSelected) {
		Hide();
		Singleton<GameManager>::GetInstance().SetGameState(Play);
	}
	else {
		Singleton<GameManager>::GetInstance().SetGameState(Pause);
	}		
}

void TutorialEnterObject::OnUpdate() // 업데이트
{
	//쓸게없넹
}

void TutorialEnterObject::Show()
{
	panel->SetActive(true);
	yesBtn->EnableBitmaps();
	yesBtn->SetActive(true);
	noBtn->EnableBitmaps();
	noBtn->SetActive(true);
}

void TutorialEnterObject::Hide()
{
	panel->SetActive(false);
	yesBtn->DisableBitmaps();
	yesBtn->SetActive(false);
	noBtn->DisableBitmaps();
	noBtn->SetActive(false);
}
