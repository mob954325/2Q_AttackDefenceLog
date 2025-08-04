#include "SelectScene.h"
#include "../Engine/Platform/Input.h"

void SelectScene::OnEnterImpl()
{
	std::cout << "선택씬 진입" << std::endl;
}

void SelectScene::OnExitImpl()
{
}

void SelectScene::UpdateImpl()
{
	if (Input::leftButtonDown) {
		Singleton<SceneManager>::GetInstance().LoadScene(STAGE1);
	}
}
