#include "Stage1.h"
#include "../Objects/InputObject.h"
#include "../Objects/Stage/StageBGI.h"
#include "../Objects/PatternControlObject.h"

void Stage1::OnEnterImpl()
{
	std::cout << "스테이지1 진입" << std::endl;



	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj, "InputStage1");

	PCO = new GameObject();
	PCO->AddComponent<PatternControlObject>();
	AddGameObject(PCO , "PatternControlObject");

	stageBGI = new GameObject();
	stageBGI->AddComponent<StageBGI>();
	AddGameObject(stageBGI);
}

void Stage1::OnExitImpl()
{
	std::cout << "스테이지1 이탈" << std::endl;
}

void Stage1::UpdateImpl()
{					
	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('2')) {
		Singleton<SceneManager>::GetInstance().LoadScene(END);
	}
}
