#include "EndScene.h"
#include "../Engine/Components/Logic/InputSystem.h"

void EndScene::OnEnterImpl()
{
	std::cout << "엔드씬 진입" << std::endl;
}

void EndScene::OnExitImpl()
{
}

void EndScene::UpdateImpl()
{
	if (Input::leftButtonDown) {
		Singleton<SceneManager>::GetInstance().LoadScene(MENU);
	}
}
