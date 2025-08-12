#include "SelectScene.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"
#include "Objects/Common/TestObject.h"
#include "Objects/Common/MouseTrailObject.h"
#include "Application/AppPaths.h"
#include "Objects/Scenes/SelectScene/LevelSelectManager.h"
#include "Objects/Scenes/SelectScene/SelectSceneBGI.h"
#include "Objects/Scenes/SelectScene/SelectEffectManager.h"
#include "Objects/Scenes/Stage/CloudManager.h"

void SelectScene::OnEnterImpl()
{
	std::cout << "선택씬 진입" << std::endl;

	selectEffectManager = new GameObject();
	auto tem = selectEffectManager->AddComponent<SelectEffectManager>();
	AddGameObject(selectEffectManager, "SelectEffectManager");

	cloudManager = new GameObject();
	auto cloud = cloudManager->AddComponent<CloudManager>();
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
}

void SelectScene::OnExitImpl()
{
	std::cout << "선택씬 이탈" << std::endl;
}

void SelectScene::UpdateImpl()
{
}
