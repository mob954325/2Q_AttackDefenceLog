#include "TutorialEffectObject.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"
//#include "Scene/SceneManager.h"
#include "Scripts/SceneCore.h"
#include "Scripts/GameManager.h"
#include "../Engine/Components/Logic/InputSystem.h"


void TutorialEffectObject::OnCreate()
{
}


void TutorialEffectObject::OnStart()
{
	owner->AddComponent<InputSystem>();
	//==================================================================================
	// 파일 조정하는 부분, 현재 2~31
	auto basePath = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\Tutorial\\";
	std::vector<std::wstring> files;
	for (int i = 2; i < 32; ++i)
		files.emplace_back(std::wstring(L"tutorial_") + std::to_wstring(i) + L".png");
	//==================================================================================

	for (int i = 0; i < files.size(); ++i) {
		GameObject* obj = new GameObject();
		obj->GetTransform().SetUnityCoords(false);
		obj->SetRenderLayer(EngineData::RenderLayer::UI);

		auto br = obj->AddComponent<BitmapRenderer>();
		br->CreateBitmapResource(basePath + files[i]);
		br->SetOrderInLayer(i + 10);
		br->SetActive(false);

		slideImages.push_back(br);
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj, "tutorialImage." + i);
	}

	index = 0;
	isPlay = true;

	float x = 850.0f;

	float y = -275.0f;

	std::wstring textPath = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Number\\";
	std::wstring textFiles[] = {
		L"parrying_3times_text.png",
		L"defence_3times_text.png",
		L"attack_3times_text.png"		
	};

	for (int i = 0; i < 3; ++i) {
		GameObject* obj = new GameObject();		
		obj->SetRenderLayer(EngineData::RenderLayer::UI);
		obj->GetTransform().SetPosition(x - 400.0f, y + i * 65.0f);

		auto br = obj->AddComponent<BitmapRenderer>();
		br->CreateBitmapResource(textPath + textFiles[i]);
		br->SetOrderInLayer(100);
		br->SetActive(false); // 나중에 조정해주자
		numText.push_back(br);

		auto com = obj->AddComponent<TutorialNumObject>();
		com->SetPos({ x, y + i * 65.0f }); // 간격 65		
		nums.push_back(com);

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj, "tutorialNums." + i);
	}

	//escPanelForTutorial << 이름
	auto esc = owner->GetQuery()->FindByName("escPanelForTutorial");
	if (esc) {
		escPanel = esc->GetComponent<StageESCPanel>();
	}
	else {
		std::cout << "비상!!!!!!비상!!!!!!!" << std::endl;
	}

	//TutorialBettleManager << 이름
	auto bettle = owner->GetQuery()->FindByName("TutorialBettleManager");
	if (bettle) {
		bt = bettle->GetComponent<BettleManager>();
	}
	else {
		std::cout << "비상!!!!!!비상!!!!!!!" << std::endl;
	}
}

void TutorialEffectObject::OnUpdate() // 업데이트
{
	if (!isPlay) return;

	if (Singleton<GameManager>::GetInstance().GetGameState() == GameState::Pause && index < 1)
	{
		return; // 처음에만 pause 허용
	}

	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();

	inputMouse = owner->GetComponent<InputSystem>()->IsMouseButtonDown(Left);

	if (inputMouse && !cachedInputMouse) { // 지금 눌림 + 이전 안눌림
		std::cout << "튜토리얼 마우스 눌림 감지됨" << std::endl;
		//====================================================================
		if (index < slideImages.size()) { // 31 -> 32까지만 구현

			if (!(index == 18)) {
				if (index >= 1) slideImages[index - 1]->SetActive(false);
				else {
					escPanel->SetInputEnable(false);
					escPanel->DisablePanel();
					Singleton<GameManager>::GetInstance().SetGameState(Pause);
				}

				slideImages[index]->SetActive(true);
				index++;
				if (index == 18) {
					Singleton<GameManager>::GetInstance().SetGameState(Play);

					escPanel->SetInputEnable(true);

					for (auto& it : nums) {
						it->Show(0);
					}

					for (auto& it : numText) {
						it->SetActive(true);
					}

				}
				if (index == 20) {
					bt->SetSpiritNormallize(0.0f);
					std::cout << "기세 0 된것임" << std::endl;
					oneSecPlay = true;
				}
				if (index == 26) {
					bt->SetSpiritNormallize(1.0f);
					std::cout << "기세 100 된것임" << std::endl;
					oneSecPlay = true;
				}

			}
		}
		else {
			Singleton<SceneManager>::GetInstance().LoadScene(MENU);
			//씬 전환 일단 메뉴로 해둠, 나중에 난이도 선택으로 연결 가능
		}

		//====================================================================
	}
	cachedInputMouse = inputMouse;

	if (isDone) { // 18 인덱스에 해당함
		slideImages[index - 1]->SetActive(false);
		slideImages[index]->SetActive(true);
		index++;
		isDone = false;

		escPanel->SetInputEnable(false);
		escPanel->DisablePanel();
		Singleton<GameManager>::GetInstance().SetGameState(Pause);

		Clear.Invoke(); // 외부에 정리함수 호출
		//isDone은 Check함수에서만 켜지는데, 인덱스 18일때만 작동함
	}

	//====================================================================

	if (isPlayingAttack) {
		slideImages[index - 1]->SetActive(false);
		slideImages[index]->SetActive(true);
		index++;
		isPlayingAttack = false;

		escPanel->SetInputEnable(false);
		escPanel->DisablePanel();
		Singleton<GameManager>::GetInstance().SetGameState(Pause);

		Clear.Invoke();
	}

	//====================================================================

	if (isPlayingDefence) {
		slideImages[index - 1]->SetActive(false);
		slideImages[index]->SetActive(true);
		index++;
		isPlayingDefence = false;

		escPanel->SetInputEnable(false);
		escPanel->DisablePanel();
		Singleton<GameManager>::GetInstance().SetGameState(Pause);

		Clear.Invoke();
	}

	//====================================================================

	if (oneSecPlay) { // 이거 왜 안되는거징
		timer += delta;
		if (timer > 1.0f) {
			timer = 0.0f;
			oneSecPlay = false;
		}
	}

}