#include "MenuScene.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"

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


	selectEffectManager = new GameObject();
	selectEffectManager->AddComponent<SelectEffectManager>(); // 이름 잘못지었음, 로비엿슴 아니? 사실 맞는거 같은데 몰루
	AddGameObject(selectEffectManager, "SelectEffectManager");


	cloudManager = new GameObject();
	cloudManager->AddComponent<CloudManager>();
	AddGameObject(cloudManager, "CloudManagerMenu");


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
	
	if (input->IsKeyPressed('2')) {
		selectEffectManager->GetComponent<SelectEffectManager>()->Start();
		cloudManager->GetComponent<CloudManager>()->ReverseStart();
	}

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
}
