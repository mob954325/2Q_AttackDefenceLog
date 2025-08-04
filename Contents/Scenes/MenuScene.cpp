#include "MenuScene.h"
#include "../Engine/Components/Logic/InputSystem.h"

#include "../Objects/TestObject.h"

void MenuScene::OnEnterImpl()
{
	std::cout << "메뉴씬 진입" << std::endl;

	testObj = new GameObject();
	testObj->AddComponent<TestObject>();
	AddGameObject(testObj, "testobj");
}

void MenuScene::OnExitImpl()
{
	std::cout << "메뉴씬 이탈" << std::endl;
}

void MenuScene::UpdateImpl()
{
	if (Input::leftButtonDown) {
		Singleton<SceneManager>::GetInstance().LoadScene(SELECT);
	}
}
