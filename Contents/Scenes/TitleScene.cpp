#include "TitleScene.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"
#include "Objects/Common/MouseTrailObject.h"
#include "Objects/Scenes/TitleScene/TitleSceneBGI.h"
#include "Objects/Scenes/TitleScene/TitleNodeManager.h"
#include "Objects/Scenes/TitleScene/TitleEffectManager.h"

void TitleScene::OnEnterImpl()
{
	std::cout << "타이틀씬 진입" << std::endl;

	nodeManager = new GameObject();
	nodeManager->AddComponent<TitleNodeManager>();
	AddGameObject(nodeManager, "node");

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj, "input");

	backGroundImg = new GameObject();
	backGroundImg->AddComponent<TitleSceneBGI>();
	AddGameObject(backGroundImg, "TitleBGI");	

	titleEffectManager = new GameObject();
	titleEffectManager->AddComponent<TitleEffectManager>();
	AddGameObject(titleEffectManager, "TItleEffectManager");

	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	AddGameObject(trail, "MouseTrail");
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
}
