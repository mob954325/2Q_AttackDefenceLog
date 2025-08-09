#include "Stage3.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"

void Stage3::OnEnterImpl()
{
	std::cout << "스테이지3 진입" << std::endl;
	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);
}

void Stage3::OnExitImpl()
{
	std::cout << "스테이지3 이탈" << std::endl;
}

void Stage3::UpdateImpl()
{
	if (Input::leftButtonDown) {
		Singleton<SceneManager>::GetInstance().LoadScene(END);
	}
	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('6')) {
		Singleton<SceneManager>::GetInstance().LoadScene(END);
	}
}
