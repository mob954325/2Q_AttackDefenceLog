#include "MenuScene.h"
#include "../Engine/Platform/Input.h"

void MenuScene::OnEnterImpl()
{
	std::cout << "메뉴씬 진입" << std::endl;
}

void MenuScene::OnExitImpl()
{
}

void MenuScene::UpdateImpl()
{
	if (Input::leftButtonDown) {
		Singleton<SceneManager>::GetInstance().LoadScene(SELECT);
	}
}
