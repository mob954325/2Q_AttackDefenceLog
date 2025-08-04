#include "EndScene.h"
#include "../Engine/Components/Logic/InputSystem.h"

#include "../Objects/InputObject.h"

void EndScene::OnEnterImpl()
{
	std::cout << "엔드씬 진입" << std::endl;

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);
}

void EndScene::OnExitImpl()
{
	std::cout << "엔드씬 이탈" << std::endl;
}

void EndScene::UpdateImpl()
{
	if (Input::leftButtonDown) {
		Singleton<SceneManager>::GetInstance().LoadScene(MENU);
	}


	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('1')) {
		Singleton<SceneManager>::GetInstance().LoadScene(MENU);
	}
}
