#include "Stage1.h"
#include "Objects/Common/InputObject.h"
#include "Objects/Scenes/Stage/StageBGI.h"
#include "Objects/Common/PatternControlObject.h"

#include "Objects/Scenes/Stage/EscMenu/StageESCPanel.h"
#include "Objects/Scenes/Stage/EscMenu/EscContinueButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscExitButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscMuteButton.h"
#include "Objects/Sound/SoundPlayScene.h"
#include "Objects/Scenes/Stage/BackboardObject.h"
#include "../Engine/Systems/AudioSystem.h"
#include "Application/AppPaths.h"
#include "Scripts/BubbleBox/BubbleBox.h"
#include "Scripts/GameManager.h"

void Stage1::OnEnterImpl()
{


	std::cout << "스테이지1 진입" << std::endl;

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj, "InputStage1");

	PCO = new GameObject();
	auto comp = PCO->AddComponent<PatternControlObject>();
	AddGameObject(PCO , "PatternControlObject");
	comp->GetEnemy()->SetNameDiff("Stage1", Singleton<GameManager>::GetInstance().GetDifficultyString());

	stageBGI = new GameObject();
	stageBGI->AddComponent<StageBGI>();
	AddGameObject(stageBGI, "StageBGI1");

	GameObject* nodePanel = new GameObject();
	nodePanel->AddComponent<BackboardObject>();
	AddGameObject(nodePanel);

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

	Singleton<AudioSystem>::GetInstance().ReSetChannel();

	SoundStageOne = new GameObject();
	SoundStageOne->AddComponent<SoundPlayScene>();
	AddGameObject(SoundStageOne, "SoundMenu1");

	SoundStageOne->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Stage01");
	SoundStageOne->GetComponent<SoundPlayScene>()->PlaySound();
	
	Textbox = new GameObject();
	Textbox->AddComponent<BubbleBox>();
	AddGameObject(Textbox, "Textbox");

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
