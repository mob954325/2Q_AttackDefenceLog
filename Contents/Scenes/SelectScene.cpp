#include "SelectScene.h"
#include "../Engine/Components/Logic/InputSystem.h"

void SelectScene::OnEnterImpl()
{
	std::cout << "선택씬 진입" << std::endl;
}

void SelectScene::OnExitImpl()
{
	std::cout << "선택씬 이탈" << std::endl;
}

int num = 0;

void SelectScene::UpdateImpl()
{
	if (Input::leftButtonDown) {
		num++;

		if(num == 1)
			Singleton<SceneManager>::GetInstance().LoadScene(STAGE1);
		if(num == 2)
			Singleton<SceneManager>::GetInstance().LoadScene(STAGE2);
		if (num == 3) {
			num = 0;
			Singleton<SceneManager>::GetInstance().LoadScene(STAGE3);
		}			
	}
}
