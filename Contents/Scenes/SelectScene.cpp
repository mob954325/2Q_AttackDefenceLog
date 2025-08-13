#include "SelectScene.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"
#include "Objects/Common/TestObject.h"
#include "Objects/Common/MouseTrailObject.h"
#include "Application/AppPaths.h"
#include "Objects/Scenes/SelectScene/LevelSelectManager.h"
#include "Objects/Scenes/SelectScene/SelectSceneBGI.h"
#include "Objects/Sound/SoundTittle.h"
#include "../Engine/Systems/AudioSystem.h"
#include "Scripts/GameManager.h"

#include "Objects/Scenes/Stage/CloudManager.h"

void SelectScene::OnEnterImpl()
{
	Singleton<AudioSystem>::GetInstance().ReSetChannel();

	std::cout << "선택씬 진입" << std::endl;

	cloudManager = new GameObject();
	cloudManager->AddComponent<CloudManager>();
	AddGameObject(cloudManager, "CloudManagerSelcet");

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);

	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	AddGameObject(trail, "MouseTrail");


	auto bg = new GameObject();
	bg->AddComponent<SelectSceneBGI>();
	AddGameObject(bg, "backgroundImg");

	selectManager = new GameObject();
	selectManager->AddComponent<LevelSelectManager>();
	AddGameObject(selectManager, "LevelSelectManager");

	SoundSeletObj = new GameObject();
	SoundSeletObj->AddComponent<SoundTittle>();
	AddGameObject(SoundSeletObj, "SOUNDMENU"); // SOUNDMENU << 이름 유지해주세요

	SoundSeletObj->GetComponent<SoundTittle>()->SetKeyHandle(L"Lobby");
	SoundSeletObj->GetComponent<SoundTittle>()->PlaySound();
}

void SelectScene::OnExitImpl()
{
	std::cout << "선택씬 이탈" << std::endl;
}

void SelectScene::UpdateImpl()
{
	auto input = inputObj->GetComponent<InputSystem>();


	if (input->IsKeyPressed('3')) {
		cloudManager->GetComponent<CloudManager>()->Start();
	}

	if (input->IsKeyPressed('4')) {
		cloudManager->GetComponent<CloudManager>()->ReverseStart();
	}

}

// select에서 스테이지 클리어 검사해서 만족하면 바로 엔딩씬으로 가기