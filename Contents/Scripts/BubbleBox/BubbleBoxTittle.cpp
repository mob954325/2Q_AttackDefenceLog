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
}

void BubbleBoxTittle::OnCreate()
{
	owner->SetRenderLayer(EngineData::UI);
	owner->GetTransform().SetUnityCoords(false);
	owner->GetTransform().SetPosition(-200.0f, -100.0f);


	input = owner->AddComponent<InputSystem>();

	for (int i = 0; i < 11; i++)
	{
		texts.push_back(owner->AddComponent<BitmapRenderer>());

		std::wstring path = L"\\..\\Resource\\UI\\BoxText\\tittle\\";
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
	timer += Singleton<GameTime>::GetInstance().GetDeltaTime();
	if (timer > delaytime) // 시간이 다 지났으면
	{
		if (Input::leftButtonDown) // 왼쪽 클릭 했으면
		{
			if (count < 10) // 0 ~ 9은 하나씩 출현하기
			{
				count++;
				texts[count]->SetActive(true);
				timer = 0.0f;
			}

			if (count == 10) // 10은 나머지 다 비활성화하고 혼자 출력
			{
				// 기존에 출력 되었던 텍스트 모두 비활성화
				for (int i = 0; i < 10; i++)
				{
					texts[count]->SetActive(false);
				}

				texts[count]->SetActive(true); // 마지막 텍스트 활성화
				count++;
			}

			if (count == 11) // 11번째 클릭에선 씬 전환
			{
				StartCheck = false;
				Singleton<AudioSystem>::GetInstance().AgainstSound();
				Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::MENU); // MenuScene으로 이동
			}
		}
	}

	if (texts[count]->IsActiveSelf() && timer < delaytime) // 위에서 밑으로 출력하기
	{
		rectY = texts[count]->GetResource()->GetBitmap()->GetSize().height * timer / delaytime;
		std::cout << rectY << std::endl;
	}
	texts[count]->SetDestRect({ 0, 0, texts[count]->GetResource()->GetBitmap()->GetSize().width, rectY });
	texts[count]->SetSrcRect({ 0, 0, texts[count]->GetResource()->GetBitmap()->GetSize().width, rectY });
}
