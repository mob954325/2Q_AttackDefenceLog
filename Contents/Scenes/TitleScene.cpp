#include "TitleScene.h"
#include "../Engine/Components/Logic/InputSystem.h"

void TitleScene::OnEnterImpl()
{
	std::cout << "타이틀씬 진입" << std::endl;
}

void TitleScene::OnExitImpl()
{
}

void TitleScene::UpdateImpl()
{
	if (Input::leftButtonDown) {
		Singleton<SceneManager>::GetInstance().LoadScene(MENU);
	}
}
