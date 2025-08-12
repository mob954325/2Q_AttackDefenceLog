#include "MenuScene.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"

#include "Objects/Common/TestObject.h"
#include "Objects/Common/MouseTrailObject.h"
#include "Objects/Scenes/MenuScene/MenuSceneBGI.h"
#include "Objects/Scenes/MenuScene/StageSelectManager.h"
#include "Objects/Sound/SoundTittle.h"

void MenuScene::OnEnterImpl()
{
	std::cout << "메뉴씬 진입" << std::endl;

	testObj = new GameObject();
	testObj->AddComponent<TestObject>();
	AddGameObject(testObj);

	inputObj = new GameObject();
	inputObj -> AddComponent<InputObject>();
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
	AddGameObject(SoundMenuObj, "SoundMenu");
}

void MenuScene::OnExitImpl()
{
	std::cout << "메뉴씬 이탈" << std::endl;
}

void MenuScene::UpdateImpl()
{
	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('1')) {
		Singleton<SceneManager>::GetInstance().LoadScene(STAGE1);
	}
}
