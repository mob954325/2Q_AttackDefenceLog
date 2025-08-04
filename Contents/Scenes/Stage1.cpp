#include "Stage1.h"
#include "../Engine/Components/Logic/InputSystem.h"

void Stage1::OnEnterImpl()
{
	std::cout << "스테이지1 진입" << std::endl;
}

void Stage1::OnExitImpl()
{
	std::cout << "스테이지1 이탈" << std::endl;
}

void Stage1::UpdateImpl()
{
	if (Input::leftButtonDown) {
		Singleton<SceneManager>::GetInstance().LoadScene(END);
	}
}
