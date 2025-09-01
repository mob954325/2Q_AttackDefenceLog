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
		br->SetOrderInLayer(i + 300);
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
		return; // 처음(좌클릭 하기 전까지만) pause 허용 -> ESC 누르고 나가기 누를 수 있게 해주는 장치
	}

	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();

	inputMouse = owner->GetComponent<InputSystem>()->IsMouseButtonDown(Left);

	if (inputMouse && !cachedInputMouse) { // 지금 눌림 + 이전 안눌림
		std::cout << "튜토리얼 마우스 눌림 감지됨" << std::endl;
		//====================================================================
		//인덱스 사이즈 밖으로 나간 상태로 좌클릭시, 씬 넘김
		if (index < slideImages.size() ) { // 31 -> 32까지만 구현

			// 조건에 해당하지 않으면, 좌클릭을 했다고 해서 인덱스가 증가하지 않음

			if (index != 18 && !oneSecPlay) { // 18번은 isDone을 기반으로 넘겨줌 + 대기 상태가 아닌 경우에만
				if ((!isPlayingAttack && !isPlayingDefence)) {
					if (index >= 1) slideImages[index - 1]->SetActive(false); // 첫 노드가 아니면, 이전 비트맵 끄기
					else {
						escPanel->SetInputEnable(false); // 아니라면, ESC 막고
						escPanel->DisablePanel(); // 패널 끄기
						Singleton<GameManager>::GetInstance().SetGameState(Pause); // 일시정지 ON
						Clear.Invoke();
					}

					slideImages[index]->SetActive(true); // 이미지 키고
					index++; // 인덱스 증가(순서 상, 사이즈 +1이 들어가 있을 수 있음, 자연스럽게 다음루프에서 로드 씬으로 연결됨)

					if (index == 18) { // 만약 18, 즉, 17 -> 18이 된 시점(다음 루프에 켜질게 18이라는 의미임)
						Singleton<GameManager>::GetInstance().SetGameState(Play); // 재생 키고

						escPanel->SetInputEnable(true); // ESC 허용

						// 퀘스트(3번 패링, 가드, 공격) 켜기
						for (auto& it : nums) {
							it->Show(0);
						}

						for (auto& it : numText) {
							it->SetActive(true);
						}
					}

					if (index == 20) { // 20번째에, 기세가 0이된걸 보여줌, 그냥 지나가는 연출
						bt->SetSpiritNormallize(0.01f);
						std::cout << "기세 0.01 변경됨" << std::endl;
					}

					if (index == 26) { // 26번째에, 기세가 1이된걸 보여줌, 지나가는 연출
						bt->SetSpiritNormallize(0.99f);
						std::cout << "기세 0.99 변경됨" << std::endl;
					}

					if (index == 25) {
						// 간파 연습
						isPlayingDefence = true; // 플래그 켜주면, 외부에서 꺼줄때까지 못돌아옴	
						bt->SetSpiritNormallize(0.0f); // 간파 진입
					}

					if (index == 29) {
						// 연격 연습
						isPlayingAttack = true;
						bt->SetSpiritNormallize(1.0f); // 연격 진입
					}
				}
				else { // 연격 / 간파 연습일때, 좌클릭이 들어온다면					
					slideImages[index - 1]->SetActive(false); // 현재 슬라이드(이미 증가되서 한칸 전이 현재임) 끔
					Singleton<GameManager>::GetInstance().SetGameState(Play); // 재생 키고
					escPanel->SetInputEnable(true); // ESC 허용
					//외부에서 조건 충족 후 처리해줘야함					
				}
			}

			//====================================================================

		}
		else {
			Singleton<SceneManager>::GetInstance().LoadScene(MENU);
			// 사이즈 벗어난 상태에서 좌클릭 = 슬라이드쇼 종료 후 좌클릭(메뉴로 돌아가기)
		}

		//====================================================================
	}

	cachedInputMouse = inputMouse; // 마우스 인풋 캐싱

	if (isDone) { // 18 인덱스에 해당함, Check()함수 내부에 플래그 키는 기능이 있음
		timer2 += delta;
		if (timer2 > 1.0f) {
			timer2 = 0.0f;
			isDone = false; // 플래그 꺼주기(1회만 보장)

			slideImages[index - 1]->SetActive(false);
			slideImages[index]->SetActive(true);
			index++; // 여기까지가 기존 진행, 슬라이드 넘기기			

			escPanel->SetInputEnable(false); // ESC 막고
			escPanel->DisablePanel();  // 끄고
			Singleton<GameManager>::GetInstance().SetGameState(Pause); //정지

			Clear.Invoke(); // 외부에 정리함수 호출(배틀 매니저 등)
			//isDone은 Check함수에서만 켜지는데, 인덱스 18일때만 작동함
		}
	}

	//====================================================================

	if (oneSecPlay) { // 만약, 플레이어가 시간 안에 연격 / 간파를 하지 못했을 경우, 1초 후 다시 연격에 진입시켜줌
		timer += delta;
		if (timer > 1.0f) {
			timer = 0.0f;
			oneSecPlay = false;
			//플래그 켜진 시점으로 1초뒤에 1회 호출되는 부분임

			if (isPlayingAttack)
			{ // 연격을 하는데, 시간초과된거임
				bt->SetSpiritNormallize(1.0f); // 연격 진입
			}
			else if (isPlayingDefence) {
				// 간파를 하는데, 시간이 초과된 경우
				bt->SetSpiritNormallize(0.0f); // 간파 진입
			}
			else {
				// 1초뒤에 연출적으로 넣어주고 싶어서 사용함(마지막 일격 후 1초)
				slideImages[index]->SetActive(true);
				index++;

				escPanel->SetInputEnable(false); // ESC 막고
				escPanel->DisablePanel();  // 끄고
				Singleton<GameManager>::GetInstance().SetGameState(Pause); //정지
				Clear.Invoke();
			}
		}
	}
}
