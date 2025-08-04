#include "Stage2.h"
#include "../Engine/Components/Logic/InputSystem.h"

void Stage2::OnEnterImpl()
{
	std::cout << "스테이지2 진입" << std::endl;
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
}
