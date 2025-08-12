#include "SoundMutePanel.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"
#include "Scene/SceneManager.h"
#include "Datas/EngineData.h"
#include "Platform/Input.h"

void SoundMutePanel::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);

	float offsetX = EngineData::SceenWidth / 4;
	float offsetY = EngineData::SceenHeight / 3;

	owner->GetTransform().SetUnityCoords(false);
	owner->GetTransform().Translate({ offsetX, offsetY });

	offUIImagePath = L"\\..\\Resource\\UI\\Sound\\sound_ui_off.png";
	onUIImagePath = L"\\..\\Resource\\UI\\Sound\\sound_ui_on.png";

	bitmap = owner->AddComponent<BitmapRenderer>();
	bitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Sound\\sound_ui_pad.png");
	bitmap->SetOrderInLayer(10);
	
	// 버튼 오즈벡트 등록
	muteButtonObj = new GameObject();
	muteButtonObj->SetRenderLayer(EngineData::RenderLayer::UI);
	muteButtonObj->GetTransform().SetUnityCoords(false);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(muteButtonObj);

	// 버튼 컴포넌트 추가
	muteButton = muteButtonObj->AddComponent<Button>();
	muteButton->AddOnClickEvent([&]() { MuteEvent(); });

	SetOpen(false);
}

void SoundMutePanel::OnStart()
{
	float offsetX = EngineData::SceenWidth / 4;
	float offsetY = EngineData::SceenHeight / 3;

	muteButton->SetNormalImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + offUIImagePath);
	muteButton->SetHoverImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + offUIImagePath);
	muteButton->SetPressedImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + offUIImagePath);

	D2D1_SIZE_F size = bitmap->GetResource()->GetBitmap()->GetSize();
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

	muteButton->SetActive(false);
}

void SoundMutePanel::OnUpdate()
{
	if (!Input::leftButtonDown)
	{
		isPressed = false;
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
		bitmap->SetActive(true);

		muteButton->GetNormalImage()->SetActive(true);
		muteButton->GetHoverImage()->SetActive(true);
		muteButton->GetPressedImage()->SetActive(true);

		muteButton->SetActive(true);

		isOpen = true;
	}
	else
	{
		bitmap->SetActive(false);

		muteButton->GetNormalImage()->SetActive(false);
		muteButton->GetHoverImage()->SetActive(false);
		muteButton->GetPressedImage()->SetActive(false);

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