#include "BubbleBoxTittle.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"
#include "scripts/GameManager.h"
#include "../Engine/Systems/AudioSystem.h"

void BubbleBoxTittle::OnUpdate()
{
	if (StartCheck) CheckInput();
	delaytime += Singleton<GameTime>::GetInstance().GetDeltaTime();
}

void BubbleBoxTittle::OnCreate()
{
	owner->SetRenderLayer(EngineData::UI);
	owner->GetTransform().SetPosition(-200.0f, 100.0f);


	input = owner->AddComponent<InputSystem>();

	owner->GetTransform().SetUnityCoords(false);
	Text_01 = owner->AddComponent<BitmapRenderer>();
	Text_02 = owner->AddComponent<BitmapRenderer>();
	Text_03 = owner->AddComponent<BitmapRenderer>();
	Text_04 = owner->AddComponent<BitmapRenderer>();
	Text_05 = owner->AddComponent<BitmapRenderer>();
	Text_06 = owner->AddComponent<BitmapRenderer>();
	Text_07 = owner->AddComponent<BitmapRenderer>();
	Text_08 = owner->AddComponent<BitmapRenderer>();
	Text_09 = owner->AddComponent<BitmapRenderer>();
	Text_10 = owner->AddComponent<BitmapRenderer>();
	Text_11 = owner->AddComponent<BitmapRenderer>();


	Text_01->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\01.png");
	Text_02->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\02.png");
	Text_03->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\03.png");
	Text_04->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\04.png");
	Text_05->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\05.png");
	Text_06->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\06.png");
	Text_07->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\07.png");
	Text_08->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\08.png");
	Text_09->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\09.png");
	Text_10->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\10.png");
	Text_11->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\BoxText\\tittle\\11.png");

	Text_01->SetActive(true);
	Text_02->SetActive(false);
	Text_03->SetActive(false);
	Text_04->SetActive(false);
	Text_05->SetActive(false);
	Text_06->SetActive(false);
	Text_07->SetActive(false);
	Text_08->SetActive(false);
	Text_09->SetActive(false);
	Text_10->SetActive(false);
	Text_11->SetActive(false);

	Text_01->SetOrderInLayer(19000);
	Text_02->SetOrderInLayer(19000);
	Text_03->SetOrderInLayer(19000);
	Text_04->SetOrderInLayer(19000);
	Text_05->SetOrderInLayer(19000);
	Text_06->SetOrderInLayer(19000);
	Text_07->SetOrderInLayer(19000);
	Text_08->SetOrderInLayer(19000);
	Text_09->SetOrderInLayer(19000);
	Text_10->SetOrderInLayer(19000);
	Text_11->SetOrderInLayer(19000);

	count = 0;
	StartCheck = true;
}

void BubbleBoxTittle::OnStart()
{
	Singleton<GameManager>::GetInstance().SetGameState(Pause);
	Singleton<AudioSystem>::GetInstance().PauseSound();
}

void BubbleBoxTittle::OnDestroy()
{
}

void BubbleBoxTittle::CheckInput()
{
	if (Input::leftButtonDown && delaytime > 3.0f && count < 11)
	{
		delaytime = 0.0f;
		switch (count)
		{
		case 0:
			Text_02->SetActive(true);
			break;
		case 1:
			Text_03->SetActive(true);
			break;
		case 2:
			Text_04->SetActive(true);
			break;
		case 3:
			Text_05->SetActive(true);
			break;
		case 4:
			Text_06->SetActive(false);
			break;
		case 5:
			Text_07->SetActive(false);
			break;
		case 6:
			Text_08->SetActive(false);
			break;
		case 7:
			Text_09->SetActive(false);
			break;
		case 8:
			Text_10->SetActive(false);
			break;
		case 9:
			Text_01->SetActive(false);
			Text_02->SetActive(false);
			Text_03->SetActive(false);
			Text_04->SetActive(false);
			Text_05->SetActive(false);
			Text_06->SetActive(false);
			Text_07->SetActive(false);
			Text_08->SetActive(false);
			Text_09->SetActive(false);
			Text_10->SetActive(false);
			Text_11->SetActive(true);
			break;
		case 10:
			StartCheck = false;
			Singleton<AudioSystem>::GetInstance().AgainstSound();
			break;
		}
		++count;
	}
}
