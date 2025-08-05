#include "Stage2.h"
#include "../Engine/Components/Logic/InputSystem.h"
#include "../Objects/InputObject.h"

void Stage2::OnEnterImpl()
{
	std::cout << "스테이지2 진입" << std::endl;
	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);
}

void Stage2::OnExitImpl()
{
	std::cout << "스테이지2 이탈" << std::endl;
}

void Stage2::UpdateImpl()
{
	if (Input::leftButtonDown) {
		Singleton<SceneManager>::GetInstance().LoadScene(END);
	}
	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('6')) {
		Singleton<SceneManager>::GetInstance().LoadScene(END);
	}
}
