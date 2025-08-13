#include "BubbleBox.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"
#include "scripts/GameManager.h"
#include "../Engine/Systems/AudioSystem.h"


void BubbleBox::OnUpdate()
{
	if(StartCheck) CheckInput();
	delaytime += Singleton<GameTime>::GetInstance().GetDeltaTime();
}

void BubbleBox::OnCreate()
{
	input = owner->AddComponent<InputSystem>();

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
	
	

	count = 0;
	StartCheck = true;
	Singleton<GameManager>::GetInstance().SetGameState(Pause);
	Singleton<AudioSystem>::GetInstance().PauseSound();
}

void BubbleBox::OnStart()
{

}

void BubbleBox::OnDestroy()
{

}

void BubbleBox::CheckInput()
{
	if (Input::leftButtonDown && delaytime > 3.0f && count < 3)
	{
		++count;
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
			Singleton<AudioSystem>::GetInstance().AgainstSound();
			break;
		}
	}
}
