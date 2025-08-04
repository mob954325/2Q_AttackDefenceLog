#include "TitleScene.h"
#include "../Engine/Components/Logic/InputSystem.h"
#include "Objects/InputObject.h"

void TitleScene::OnEnterImpl()
{
	std::cout << "타이틀씬 진입" << std::endl;
	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);
}

void TitleScene::OnExitImpl()
{
	std::cout << "타이틀씬 이탈" << std::endl;
}

void TitleScene::UpdateImpl()
{
	if (Input::leftButtonDown) {
		Singleton<SceneManager>::GetInstance().LoadScene(MENU);
	}

	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('7')) {
		Singleton<SceneManager>::GetInstance().LoadScene(MENU);
	}
}
