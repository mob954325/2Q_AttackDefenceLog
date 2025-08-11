#include "Stage1.h"
#include "Objects/Common/InputObject.h"
#include "Objects/Scenes/Stage/StageBGI.h"
#include "Objects/Common/PatternControlObject.h"

#include "Objects/Scenes/Stage/EscMenu/StageESCPanel.h"
#include "Objects/Scenes/Stage/EscMenu/EscContinueButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscExitButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscMuteButton.h"


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

	GameObject* continueBtn = new GameObject();
	continueBtn->SetRenderLayer(EngineData::UI);
	auto continuBtnComp = continueBtn->AddComponent<EscContinueButton>();
	AddGameObject(continueBtn, "continueBtn");

	GameObject* exitBtn = new GameObject();
	exitBtn->SetRenderLayer(EngineData::UI);
	auto exitBtnComp = exitBtn->AddComponent<EscExitButton>();
	AddGameObject(exitBtn, "exitBtn");

	GameObject* muteBtn = new GameObject();
	muteBtn->SetRenderLayer(EngineData::UI);
	auto muteBtnComp = muteBtn->AddComponent<EscMuteButton>();
	AddGameObject(muteBtn, "muteBtn");

	escPanel = new GameObject();
	escPanel->SetRenderLayer(EngineData::UI);
	auto esc = escPanel->AddComponent<StageESCPanel>();
	AddGameObject(escPanel, "escPanel");
	esc->SetButtons({ continueBtn, exitBtn, muteBtn });
	esc->SetButtonsPosition();
}

void Stage1::OnExitImpl()
{
	std::cout << "스테이지1 이탈" << std::endl;
}

void Stage1::UpdateImpl()
{					
	//auto input = inputObj->GetComponent<InputSystem>();
	//if (input->IsKeyPressed('2')) {
	//	Singleton<SceneManager>::GetInstance().LoadScene(END);
	//}
}
