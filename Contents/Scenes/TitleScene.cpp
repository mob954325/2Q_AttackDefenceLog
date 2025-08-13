#include "TitleScene.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"
#include "Objects/Common/MouseTrailObject.h"
#include "Objects/Scenes/TitleScene/TitleSceneBGI.h"
#include "Objects/Scenes/TitleScene/TitleNodeManager.h"
#include "Objects/Scenes/TitleScene/TitleEffectManager.h"
#include "Objects/Scenes/Stage/CloudManager.h"
#include "Objects/Sound/SoundTittle.h"
#include "Objects/Scenes/Stage/StageResult/StageResult.h"

void TitleScene::OnEnterImpl()
{
	std::cout << "타이틀씬 진입" << std::endl;

	titleEffectManager = new GameObject();
	auto tem = titleEffectManager->AddComponent<TitleEffectManager>();
	AddGameObject(titleEffectManager, "TItleEffectManager");

	cloudManager = new GameObject();
	auto cloud = cloudManager->AddComponent<CloudManager>();
	AddGameObject(cloudManager, "CloudManagerTitle");


	nodeManager = new GameObject();
	auto tm = nodeManager->AddComponent<TitleNodeManager>();
	tm->onononStart.Add([this]() {
		titleEffectManager->GetComponent<TitleEffectManager>()->Start();		

		});
	AddGameObject(nodeManager, "node");

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj, "input");

	backGroundImg = new GameObject();
	backGroundImg->AddComponent<TitleSceneBGI>();
	AddGameObject(backGroundImg, "TitleBGI");



	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	AddGameObject(trail, "MouseTrail");
	
	//사운드 추가
	SoundTittleObj = new GameObject();
	SoundTittleObj->AddComponent<SoundTittle>();
	AddGameObject(SoundTittleObj, "SoundTittle");

	SoundTittleObj->GetComponent<SoundTittle>()->SetKeyHandle(L"Lobby");
	SoundTittleObj->GetComponent<SoundTittle>()->PlaySound();

	// Test - result 오브젝트 생성 함수
	// GameObject* result = new GameObject();
	// result->AddComponent<StageResult>();
	// AddGameObject(result, "result");
}

void TitleScene::OnExitImpl()
{
	std::cout << "타이틀씬 이탈" << std::endl;
}

void TitleScene::UpdateImpl()
{
	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('1')) {
		Singleton<SceneManager>::GetInstance().LoadScene(MENU);

	}
	if (input->IsKeyPressed('2')) {
		titleEffectManager->GetComponent<TitleEffectManager>()->Start();
		
	}
// 	if (input->IsKeyDown('3')) {
// 		cloudManager->GetComponent<CloudManager >()->ReverseStart();
// 	}
	if (input->IsKeyDown('3')) {
		cloudManager->GetComponent<CloudManager >()->Start();
	}
}
