#include "Stage3.h"
#include "../Engine/Components/Logic/InputSystem.h"

void Stage3::OnEnterImpl()
{
	std::cout << "스테이지3 진입" << std::endl;
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
}
