#include "BubbleBox.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"
#include "scripts/GameManager.h"
#include "../Engine/Systems/AudioSystem.h"
#include "Objects/Sound/SoundPlayScene.h"


void BubbleBox::OnUpdate()
{
	if(StartCheck) CheckInput();
	delaytime += Singleton<GameTime>::GetInstance().GetDeltaTime();
}

void BubbleBox::OnCreate()
{
	owner->SetRenderLayer(EngineData::UI);
	owner->GetTransform().SetPosition(-200.0f, 100.0f);


	input = owner->AddComponent<InputSystem>();

	owner->GetTransform().SetUnityCoords(false);
	TextBox = owner->AddComponent<BitmapRenderer>();
	Text_01 = owner->AddComponent<BitmapRenderer>();
	Text_02 = owner->AddComponent<BitmapRenderer>();
	Text_03 = owner->AddComponent<BitmapRenderer>();

	TextBox->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\bubbleBox\\textbox.png");
	Text_01->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\1stage\\01.png");
	Text_02->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\1stage\\02.png");
	Text_03->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\1stage\\03.png");
	
	TextBox->SetActive(true);
	Text_01->SetActive(true);
	Text_02->SetActive(false);
	Text_03->SetActive(false);
	
	Text_01->SetOrderInLayer(19000);
	Text_02->SetOrderInLayer(19000);
	Text_03->SetOrderInLayer(19000);
	

	count = 0;
	StartCheck = true;

	Singleton<GameManager>::GetInstance().SetGameState(Pause);
}

void BubbleBox::OnStart()
{
	Singleton<AudioSystem>::GetInstance().PauseSound();
}

void BubbleBox::OnDestroy()
{

}

void BubbleBox::CheckInput()
{
	if (Input::leftButtonDown && delaytime > 0.5f && count < 3)
	{
		delaytime = 0.0f;
		switch (count)
		{
		case 0:
			Text_01->SetActive(false);
			Text_02->SetActive(true);
			Text_03->SetActive(false);
			break;
		case 1:
			Text_01->SetActive(false);
			Text_02->SetActive(false);
			Text_03->SetActive(true);
			break;
		case 2:
			TextBox->SetActive(false);
			Text_01->SetActive(false);
			Text_02->SetActive(false);
			Text_03->SetActive(false);
			StartCheck = false;
			Singleton<GameManager>::GetInstance().SetGameState(Play);
			auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
			if (SoundCom) {
				SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Stage01");
				SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
			}

			escPanel->SetInputEnable(true);
			break;
		}
		++count;
	}
}

void BubbleBox::SetEscPanel(StageESCPanel* pPanel)
{
	escPanel = pPanel;
}
