#include "MenuScene.h"
#include "../Engine/Components/Logic/InputSystem.h"
#include "../Objects/InputObject.h"

#include "../Objects/TestObject.h"
#include "../Objects/MouseTrailObject.h"

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
}

void MenuScene::OnExitImpl()
{
	std::cout << "메뉴씬 이탈" << std::endl;
}

void MenuScene::UpdateImpl()
{
	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('2')) {
		Singleton<SceneManager>::GetInstance().LoadScene(SELECT);
	}
}
