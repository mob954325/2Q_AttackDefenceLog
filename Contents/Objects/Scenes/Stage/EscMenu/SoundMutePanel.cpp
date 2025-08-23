#include "SoundMutePanel.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"
#include "Scene/SceneManager.h"
#include "Datas/EngineData.h"
#include "Systems/AudioSystem.h"

void SoundMutePanel::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);

	offsetX = EngineData::SceenWidth / 4;
	offsetY = EngineData::SceenHeight / 3;

	owner->GetTransform().SetUnityCoords(false);
	owner->GetTransform().Translate({ offsetX, offsetY });

	offUIImagePath = L"\\..\\Resource\\Sprites\\UI\\SoundControl\\sound_ui_off.png";
	onUIImagePath = L"\\..\\Resource\\Sprites\\UI\\SoundControl\\sound_ui_on.png";

	panelBitmap = owner->AddComponent<BitmapRenderer>();
	panelBitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\SoundControl\\sound_ui_pad.png");
	panelBitmap->SetOrderInLayer(10);

	D2D1_SIZE_F size = panelBitmap->GetResource()->GetBitmap()->GetSize();
	
	// 버튼 오즈벡트 등록
	muteButtonObj = new GameObject();
	muteButtonObj->SetRenderLayer(EngineData::RenderLayer::UI);
	muteButtonObj->GetTransform().SetUnityCoords(false);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(muteButtonObj);

	// 버튼 컴포넌트 추가
	muteButton = muteButtonObj->AddComponent<Button>();
	muteButton->AddOnClickEvent([&]() { MuteEvent(); });

	// 음향 슬라이더 세팅 // x 0.3 - 0.875f
	sliderButton = new GameObject();
	sliderButton->SetRenderLayer(EngineData::RenderLayer::UI);
	sliderButton->GetTransform().SetUnityCoords(false);

	sliderButtonBitmap = sliderButton->AddComponent<BitmapRenderer>();
	sliderButtonBitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\SoundControl\\sound_volumn_ui.png");
	sliderButtonBitmap->SetOrderInLayer(15);

	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(sliderButton);
	sliderButton->GetTransform().Translate({ offsetX + size.width * 0.3f , offsetY + size.width * 0.125f });

	soundSliceRect =
	{
		offsetX + size.width * 0.3f,
		offsetY + size.width * 0.10f,
		offsetX + size.width * 0.875f,
		offsetY + size.width * 0.15f + 25.0f
	};

	SetOpen(false);
}

void SoundMutePanel::OnStart()
{
	muteButton->SetNormalImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + offUIImagePath);
	muteButton->SetHoverImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + offUIImagePath);
	muteButton->SetPressedImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + offUIImagePath);

	D2D1_SIZE_F size = panelBitmap->GetResource()->GetBitmap()->GetSize();
	muteButtonObj->GetTransform().Translate({ offsetX, offsetY });
	muteButton->UseCustomRect(true);

	Vector2 ownerPosition = owner->GetTransform().GetPosition();
	muteButton->SetCustomRect({ ownerPosition.x + size.width * 0.5f,
								ownerPosition.y + size.height * 0.5f,
								ownerPosition.x + size.width * 0.5f + 230.0f,
								ownerPosition.y + size.height * 0.5f + 130.0f });

	muteButton->GetNormalImage()->SetOrderInLayer(15);
	muteButton->GetHoverImage()->SetOrderInLayer(15);
	muteButton->GetPressedImage()->SetOrderInLayer(15);

	muteButton->GetNormalImage()->SetActive(false);
	muteButton->GetHoverImage()->SetActive(false);
	muteButton->GetPressedImage()->SetActive(false);
	sliderButtonBitmap->SetActive(false);

	muteButton->SetActive(false);
}

void SoundMutePanel::OnUpdate()
{
	if (!isOpen) return;

	if (!Input::leftButtonDown)
	{
		isPressed = false;
	}

	if (CheckMouseHoverOnSlider(Input::MouseX, Input::MouseY) && Input::leftButtonDown)
	{
		Vector2 currPosition = sliderButton->GetTransform().GetPosition();
		D2D1_SIZE_F size = panelBitmap->GetResource()->GetBitmap()->GetSize();

		if (currPosition.x < offsetX + size.width * 0.3f)
		{
			sliderButton->GetTransform().SetPosition(offsetX + size.width * 0.3f, currPosition.y);
		}

		if (currPosition.x > offsetX + size.width * 0.875f)
		{
			sliderButton->GetTransform().SetPosition(offsetX + size.width * 0.875f, currPosition.y);
		}

		Vector2 mouseDeltaVec = { Input::MouseX ,Input::MouseY };
		float delta = mouseDeltaVec.Magnitude();	// 마우스 움직인 크기

		float minX = offsetX + size.width * 0.3f;	// 슬라이드 최소 위치
		float maxX = offsetX + size.width * 0.85f;	// 슬라이드 최대 위치

		float ratio = Input::MouseX / maxX;			// 볼륨 현재 비율 - 위치값 비율

		sliderButton->GetTransform().SetPosition(maxX * ratio, currPosition.y);

		float volumRatio = ((Input::MouseX - offsetX + size.width * 0.3f) / (maxX - offsetX + size.width * 0.3f) * 2.0f) - 1.0f; // 0.0 - 1.0 : 실제 볼륨 값

		Singleton<AudioSystem>::GetInstance().Setvolume(volumRatio);
	}
}

void SoundMutePanel::SetStageESCPanel(StageESCPanel* pMono)
{
	panel = pMono;
}

void SoundMutePanel::SetOpen(bool value)
{
	if (value)
	{
		panelBitmap->SetActive(true);

		muteButton->GetNormalImage()->SetActive(true);
		muteButton->GetHoverImage()->SetActive(true);
		muteButton->GetPressedImage()->SetActive(true);
		sliderButtonBitmap->SetActive(true);

		muteButton->SetActive(true);

		// 슬라이더 버튼 위치 초기화 - 볼륨값과 동일하게 초기화
		Vector2 currPosition = sliderButton->GetTransform().GetPosition();
		D2D1_SIZE_F size = panelBitmap->GetResource()->GetBitmap()->GetSize();

		float soundVolum = 0;
		Singleton<AudioSystem>::GetInstance().Getvolume(soundVolum); // -1.0 ~ 1.0 범위
		float maxX = offsetX + size.width * 0.85f;

		float sliderX = (soundVolum + 1.0f) * 0.5f * (maxX - offsetX + size.width * 0.3f) + offsetX - size.width * 0.3f;

		sliderButton->GetTransform().SetPosition(sliderX, currPosition.y);

		isOpen = true;
	}
	else
	{
		panelBitmap->SetActive(false);

		muteButton->GetNormalImage()->SetActive(false);
		muteButton->GetHoverImage()->SetActive(false);
		muteButton->GetPressedImage()->SetActive(false);
		sliderButtonBitmap->SetActive(false);

		muteButton->SetActive(false);

		isOpen = false;
	}
}

bool SoundMutePanel::IsOpen()
{
	return isOpen;
}

void SoundMutePanel::MuteEvent() // TODO : 여기 음소거 기능 추가하기
{
	if (isPressed) return;

	if (isMute) // 음소거 활성화 -> 음소거 비활성화
	{
		muteButton->SetNormalImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + offUIImagePath);
		muteButton->SetHoverImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + offUIImagePath);
		muteButton->SetPressedImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + offUIImagePath);
		isMute = false;
	}
	else // 음소거 비활성화 -> 음소거 활성화하기
	{
		muteButton->SetNormalImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + onUIImagePath);
		muteButton->SetHoverImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + onUIImagePath);
		muteButton->SetPressedImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + onUIImagePath);
		isMute = true;
	}

	isPressed = true;
}

bool SoundMutePanel::CheckMouseHoverOnSlider(float x, float y)
{
	return	x >= soundSliceRect.left &&		// 왼쪽
			x <= soundSliceRect.right &&	// 오른쪽 
			y >= soundSliceRect.top &&		// 위
			y <= soundSliceRect.bottom;		// 아래
}