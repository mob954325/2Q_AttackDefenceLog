#include "BubbleEnd.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"
#include "scripts/GameManager.h"
#include "../Engine/Systems/AudioSystem.h"

void BubbleEnd::OnUpdate()
{
	timer += Singleton<GameTime>::GetInstance().GetDeltaTime();

	if (StartCheck) CheckInput();

	if (isDone) {
		if (timer > 2.0f && Input::leftButtonDown) // 2초뒤, 마우스 클릭하면 넘어가게 수정함(읽고싶은 사람 있을 수 있잖슴)
			Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::TITLE); // MenuScene으로 이동
	}
}

void BubbleEnd::OnCreate()
{
	owner->SetRenderLayer(EngineData::UI);
	owner->GetTransform().SetUnityCoords(false);
	owner->GetTransform().SetPosition(-200.0f, -100.0f);


	input = owner->AddComponent<InputSystem>();

	for (int i = 0; i < 9; i++)
	{
		texts.push_back(owner->AddComponent<BitmapRenderer>());

		std::wstring path = L"\\..\\Resource\\Sprites\\UI\\BoxText\\ending\\";
		std::wstring numStr = std::to_wstring(i + 1) + L".png";
		path += numStr;

		texts[i]->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + path);
		texts[i]->SetActive(false);
		texts[i]->SetOrderInLayer(19000);
		texts[i]->SetUseCustomRect(true);
	}

	count = 0;
	texts[count]->SetActive(true);
	timer = 0.0f;

	StartCheck = true;
}

void BubbleEnd::OnStart()
{
	/*Singleton<GameManager>::GetInstance().SetGameState(Pause);*/
	/*Singleton<AudioSystem>::GetInstance().PauseSound();*/
}

void BubbleEnd::OnDestroy()
{
}

void BubbleEnd::CheckInput()
{
	if (timer > delaytime) // 시간이 다 지났으면
	{
		if (Input::leftButtonDown) // 왼쪽 클릭 했으면
		{
			if (count < 8) // 0 ~ 9은 하나씩 출현하기 // 이거도 조건 잘못되었음 9 -> 8로 수정함
			{
				count++;
				texts[count]->SetActive(true);
				//count++; 아니 이거 순서 반대라서 작동 안하는거였음 ;
				timer = 0.0f;
			}

			if (count == 8 && !isDone)
			{
				timer = 0.0f;
				isDone = true; // 이거 계속 좌클릭 누르면, 영원히 안넘어감 ㅅㄱ				
			}
		}
	}
		
	if (count < 9 && texts[count]->IsActiveSelf() && timer < delaytime) // 위에서 밑으로 출력하기
	{
		rectY = texts[count]->GetResource()->GetBitmap()->GetSize().height * timer / delaytime;
		std::cout << rectY << std::endl;
	}

	if (count < 9)
	{
		texts[count]->SetDestRect({ 0, 0, texts[count]->GetResource()->GetBitmap()->GetSize().width, rectY });
		texts[count]->SetSrcRect({ 0, 0, texts[count]->GetResource()->GetBitmap()->GetSize().width, rectY });
	}
}
