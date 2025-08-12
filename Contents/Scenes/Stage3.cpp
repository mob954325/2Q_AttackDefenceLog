#include "Stage3.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"
#include "Objects/Sound/SoundPlayScene.h"
#include "../Engine/Systems/AudioSystem.h"

#include "Objects/Scenes/Stage/EscMenu/StageESCPanel.h"
#include "Objects/Scenes/Stage/EscMenu/EscContinueButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscExitButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscMuteButton.h"
#include "Objects/Common/PatternControlObject.h"
#include "Scripts/LiveObject/Enemy.h"
#include "Scripts/GameManager.h"

void Stage3::OnEnterImpl()
{
	std::cout << "스테이지3 진입" << std::endl;
	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);

	Singleton<AudioSystem>::GetInstance().ReSetChannel();

	SoundStageThree = new GameObject();
	SoundStageThree->AddComponent<SoundPlayScene>();
	AddGameObject(SoundStageThree, "SoundMenu3");

	SoundStageThree->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Stage03");
	SoundStageThree->GetComponent<SoundPlayScene>()->PlaySound();

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

	PCO = new GameObject();
	auto comp = PCO->AddComponent<PatternControlObject>();
	AddGameObject(PCO, "PatternControlObject");
	comp->GetEnemy()->SetNameDiff("Stage3", Singleton<GameManager>::GetInstance().GetDifficultyString());
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
	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('6')) {
		Singleton<SceneManager>::GetInstance().LoadScene(END);
	}
}
