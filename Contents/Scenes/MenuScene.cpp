#include "MenuScene.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"
#include "../Engine/Systems/AudioSystem.h"

#include "Objects/Common/TestObject.h"
#include "Objects/Common/MouseTrailObject.h"
#include "Objects/Scenes/MenuScene/MenuSceneBGI.h"
#include "Objects/Scenes/MenuScene/StageSelectManager.h"
#include "Objects/Scenes/SelectScene/SelectEffectManager.h"
#include "Objects/Scenes/Stage/CloudManager.h"
#include "Objects/Sound/SoundTittle.h"

#include "Scripts/GameManager.h"

void MenuScene::OnEnterImpl()
{
	std::cout << "메뉴씬 진입" << std::endl;

	Singleton<AudioSystem>::GetInstance().ReSetChannel();

	selectEffectManager = new GameObject();
	selectEffectManager->AddComponent<SelectEffectManager>(); // 이름 잘못지었음, 로비엿슴 아니? 사실 맞는거 같은데 몰루
	AddGameObject(selectEffectManager, "SelectEffectManager");


	cloudManager = new GameObject();
	cloudManager->AddComponent<CloudManager>();
	AddGameObject(cloudManager, "CloudManagerMenu");

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);

	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	AddGameObject(trail);

	backGroundImg = new GameObject();
	backGroundImg->AddComponent<MenuSceneBGI>();
	AddGameObject(backGroundImg, "MenuBGI");

	selectManager = new GameObject();
	selectManager->AddComponent<StageSelectManager>();
	AddGameObject(selectManager, "selectManager");

	SoundMenuObj = new GameObject();
	SoundMenuObj->AddComponent<SoundTittle>();
	AddGameObject(SoundMenuObj, "SOUNDMENU"); // SOUNDMENU << 이름 유지해주세요

	if (Singleton<GameManager>::GetInstance().IsStage1Clear() && Singleton<GameManager>::GetInstance().IsStage2Clear() && Singleton<GameManager>::GetInstance().IsStage3Clear())
	{
		isDone = true;
	}

	isFirst = true;

	SoundMenuObj->GetComponent<SoundTittle>()->SetKeyHandle(L"Lobby");
	SoundMenuObj->GetComponent<SoundTittle>()->PlaySound();
}

void MenuScene::OnExitImpl()
{
	std::cout << "메뉴씬 이탈" << std::endl;
}


void MenuScene::UpdateImpl()
{
	if (isFirst) {
		selectEffectManager->GetComponent<SelectEffectManager>()->Start();
		cloudManager->GetComponent<CloudManager>()->ReverseStart();
		isFirst = false;
	}

	auto input = inputObj->GetComponent<InputSystem>();

	// 1 : 스테이지 1로 진입
	if (input->IsKeyPressed('1')) 
	{
		Singleton<SceneManager>::GetInstance().LoadScene(STAGE1);
	}

	// 배경 디버그 코드
	if (input->IsKeyPressed('2')) 
	{
		selectEffectManager->GetComponent<SelectEffectManager>()->Start();
		cloudManager->GetComponent<CloudManager>()->ReverseStart();
	}

	// 스테이지 클리어 치트 코드 | B : 1, N : 2, M : 3
	if (input->IsKeyPressed('B'))
	{
		Singleton<GameManager>::GetInstance().SetStageClear(1);
	}

	if (input->IsKeyPressed('N'))
	{
		Singleton<GameManager>::GetInstance().SetStageClear(2);
	}

	if (input->IsKeyPressed('M'))
	{
		Singleton<GameManager>::GetInstance().SetStageClear(3);
	}

	// ending 가기
	if (isDone)
	{
		timer += Singleton<GameTime>::GetInstance().GetDeltaTime();

		if (timer > maxTimer)
		{
			Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::END); // endScene 호출
		}
	}

	Singleton<AudioSystem>::GetInstance().Update();
}
