#include "EndScene.h"
#include "../Engine/Components/Logic/InputSystem.h"

#include "../Objects/InputObject.h"
#include "../Objects/MouseTrailObject.h"

void EndScene::OnEnterImpl()
{
	std::cout << "엔드씬 진입" << std::endl;

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);
	
	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	AddGameObject(trail, "MouseTrail");
}

void EndScene::OnExitImpl()
{
	std::cout << "엔드씬 이탈" << std::endl;
}

void EndScene::UpdateImpl()
{
	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('2')) {
		Singleton<SceneManager>::GetInstance().LoadScene(MENU);
	}
}

