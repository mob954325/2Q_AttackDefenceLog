#include "TitleScene.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"
#include "Objects/Common/MouseTrailObject.h"
#include "Objects/Scenes/TitleScene/TitleSceneBGI.h"
#include "Objects/Scenes/TitleScene/TitleNodeManager.h"


#include "Objects/Scenes/Stage/EscMenu/StageESCPanel.h"
#include "Objects/Scenes/Stage/EscMenu/EscContinueButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscExitButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscMuteButton.h"

void TitleScene::OnEnterImpl()
{
	std::cout << "타이틀씬 진입" << std::endl;

	nodeManager = new GameObject();
	nodeManager->AddComponent<TitleNodeManager>();
	AddGameObject(nodeManager, "node");

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj, "input");

	backGroundImg = new GameObject();
	backGroundImg->AddComponent<TitleSceneBGI>();
	AddGameObject(backGroundImg, "TitleBGI");
	
	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	AddGameObject(trail, "MouseTrail");

	// esc Panel init
	GameObject* continueBtn = new GameObject();
	auto continuBtnComp = continueBtn->AddComponent<EscContinueButton>();
	AddGameObject(continueBtn, "continueBtn");

	GameObject* exitBtn = new GameObject();
	auto exitBtnComp = exitBtn->AddComponent<EscExitButton>();
	AddGameObject(exitBtn, "exitBtn");

	GameObject* muteBtn = new GameObject();
	auto muteBtnComp = muteBtn->AddComponent<EscMuteButton>();
	AddGameObject(muteBtn, "muteBtn");

	escPanel = new GameObject();
	auto esc = escPanel->AddComponent<StageESCPanel>();
	AddGameObject(escPanel, "escPanel");
	esc->SetButtons({ continueBtn, exitBtn, muteBtn });
	esc->SetButtonsPosition();
}

void TitleScene::OnExitImpl()
{
	std::cout << "타이틀씬 이탈" << std::endl;
}

void TitleScene::UpdateImpl()
{
	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('1')) {
		Singleton<SceneManager>::GetInstance().LoadScene(MENU);
	}
}
