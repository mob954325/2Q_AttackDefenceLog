#include "TitleScene.h"
#include "../Engine/Components/Logic/InputSystem.h"
#include "Objects/InputObject.h"
#include "Objects/MouseTrailObject.h"
#include "Objects/TitleScene/TitleSceneBGI.h"

void TitleScene::OnEnterImpl()
{
	std::cout << "타이틀씬 진입" << std::endl;
	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);

	backGroundImg = new GameObject();
	backGroundImg->AddComponent<TitleSceneBGI>();
	AddGameObject(backGroundImg, "TitleBGI");
	
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
