#include "BubbleBox2.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"
#include "scripts/GameManager.h"
#include "../Engine/Systems/AudioSystem.h"
#include "Objects/Sound/SoundPlayScene.h"

void BubbleBox2::OnUpdate()
{
	if (StartCheck) CheckInput();
	delaytime += Singleton<GameTime>::GetInstance().GetDeltaTime();
}

void BubbleBox2::OnCreate()
{
	owner->SetRenderLayer(EngineData::UI);
	owner->GetTransform().SetPosition(-200.0f, 100.0f);


	input = owner->AddComponent<InputSystem>();

	owner->GetTransform().SetUnityCoords(false);
	TextBox = owner->AddComponent<BitmapRenderer>();
	Text_01 = owner->AddComponent<BitmapRenderer>();
	Text_02 = owner->AddComponent<BitmapRenderer>();
	Text_03 = owner->AddComponent<BitmapRenderer>();
	Text_04 = owner->AddComponent<BitmapRenderer>();
	Text_05 = owner->AddComponent<BitmapRenderer>();

	TextBox->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\bubbleBox\\textbox.png");
	Text_01->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\BoxText\\2stage\\01.png");
	Text_02->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\BoxText\\2stage\\02.png");
	Text_03->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\BoxText\\2stage\\03.png");
	Text_04->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\BoxText\\2stage\\05.png");
	Text_05->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\BoxText\\2stage\\05.png");

	TextBox->SetActive(true);
	Text_01->SetActive(true);
	Text_02->SetActive(false);
	Text_03->SetActive(false);
	Text_04->SetActive(false);
	Text_05->SetActive(false);

	Text_01->SetOrderInLayer(19000);
	Text_02->SetOrderInLayer(19000);
	Text_03->SetOrderInLayer(19000);
	Text_04->SetOrderInLayer(19000);
	Text_05->SetOrderInLayer(19000);

	count = 0;
	StartCheck = true;

	Singleton<GameManager>::GetInstance().SetGameState(Pause);
}

void BubbleBox2::OnStart()
{
	/*Singleton<GameManager>::GetInstance().SetGameState(Pause);
	Singleton<AudioSystem>::GetInstance().PauseSound();*/
}

void BubbleBox2::OnDestroy()
{
}

void BubbleBox2::CheckInput()
{
	if (Input::leftButtonDown && delaytime > 0.5f && count < 5)
	{
		delaytime = 0.0f;
		switch (count)
		{
		case 0:
			Text_01->SetActive(false);
			Text_02->SetActive(true);
			Text_03->SetActive(false);
			Text_04->SetActive(false);
			Text_05->SetActive(false);
			break;
		case 1:
			Text_01->SetActive(false);
			Text_02->SetActive(false);
			Text_03->SetActive(true);
			Text_04->SetActive(false);
			Text_05->SetActive(false);
			break;
		case 2:
			Text_01->SetActive(false);
			Text_02->SetActive(false);
			Text_03->SetActive(false);
			Text_04->SetActive(true);
			Text_05->SetActive(false);
			break;
		case 3:
			Text_01->SetActive(false);
			Text_02->SetActive(false);
			Text_03->SetActive(false);
			Text_04->SetActive(false);
			Text_05->SetActive(true);
			break;
		case 4:
			TextBox->SetActive(false);
			Text_01->SetActive(false);
			Text_02->SetActive(false);
			Text_03->SetActive(false);
			Text_04->SetActive(false);
			Text_05->SetActive(false);

			StartCheck = false;
			Singleton<GameManager>::GetInstance().SetGameState(Play);
			/*Singleton<AudioSystem>::GetInstance().AgainstSound();*/
			auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
			if (SoundCom) {
				SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Stage02");
				SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
			}

			escPanel->SetInputEnable(true);

			break;
		}
		++count;
	}
}

void BubbleBox2::SetEscPanel(StageESCPanel* pPanel)
{
	escPanel = pPanel;
}
