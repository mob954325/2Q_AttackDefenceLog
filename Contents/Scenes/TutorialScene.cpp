#include "TutorialScene.h"
#include "Application/AppPaths.h"
#include "../Engine/Systems/AudioSystem.h"

#include "Objects/Common/InputObject.h"
#include "Objects/Scenes/Stage/StageBGI.h"
#include "Objects/Scenes/TutorialScene/TutorialControlObject.h"
#include "Objects/Scenes/Stage/EscMenu/StageESCPanel.h"
#include "Objects/Scenes/Stage/EscMenu/EscContinueButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscExitButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscMuteButton.h"
#include "Objects/Sound/SoundPlayScene.h"
#include "Objects/Scenes/Stage/BackboardObject.h"
#include "Objects/Scenes/Stage/StageTopUI.h"
#include "Objects/Scenes/Stage/StagePlayerProfile.h"
#include "Objects/Scenes/Stage/StageEnemyProfile.h"

#include "Scripts/GameManager.h"
#include "Scripts/BubbleBox/BubbleBox.h"
#include "../Engine/Components/Rendering/BoxRenderer.h"
#include "Vignette.h"

void TutorialScene::OnEnterImpl()
{
	std::cout << "튜토리얼 진입" << std::endl;

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj, "InputStage1");

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
	AddGameObject(escPanel, "escPanelForTutorial");
	esc->SetButtons({ continueBtn, exitBtn, muteBtn });
	esc->SetButtonsPosition();

	PCO = new GameObject();
	auto comp = PCO->AddComponent<TutorialControlObject>();
	AddGameObject(PCO , "PatternControlObject");
	comp->GetEnemy()->SetNameDiff("Tutorial", Singleton<GameManager>::GetInstance().GetDifficultyString());

	stageBGI = new GameObject();
	stageBGI->AddComponent<StageBGI>();
	AddGameObject(stageBGI, "StageBGI1");

	Singleton<AudioSystem>::GetInstance().ReSetChannel();

	SoundStageOne = new GameObject();
	SoundStageOne->AddComponent<SoundPlayScene>();
	AddGameObject(SoundStageOne, "SOUNDSTAGE"); // SOUNDSTAGE << 이름 유지해주세요
	
	Textbox = new GameObject();
	auto bb = Textbox->AddComponent<BubbleBox>();
	bb->isTutorial = true;
	AddGameObject(Textbox, "TutorialText");
	bb->SetEscPanel(esc);

	GameObject* topUIObj = new GameObject();
	auto topUIComp = topUIObj->AddComponent<StageTopUI>();
	topUIComp->owner->GetTransform().SetPosition(-EngineData::SceenWidth * 0.1f, -EngineData::SceenHeight * 0.025f);
	AddGameObject(topUIObj, "topUIObj");

	GameObject* playerProfileUIObj = new GameObject();
	auto playerProfileComp = playerProfileUIObj->AddComponent<StagePlayerProfile>();
	playerProfileComp->owner->GetTransform().SetPosition(-EngineData::SceenWidth * 0.022f, 3);
	AddGameObject(playerProfileUIObj, "playerProfileUIObj");

	GameObject* enemyProfileUIObj = new GameObject();
	auto enemyProfileComp = enemyProfileUIObj->AddComponent<StageEnemyProfile>();
	enemyProfileComp->SetProfileImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\StageTop\\ProfileUI\\tuto_enemy_ui.png");
	enemyProfileComp->owner->GetTransform().SetPosition(EngineData::SceenWidth * 0.95f, 1);
	AddGameObject(enemyProfileUIObj, "enemyProfileUIObj");

	GameObject* obj = new GameObject();
	auto vi = obj->AddComponent<Vignette>();
	AddGameObject(obj, "Vignette");
	
}

void TutorialScene::OnExitImpl()
{
	std::cout << "튜토리얼 이탈" << std::endl;
	Singleton<AudioSystem>::GetInstance().ReSetChannel();
}

void TutorialScene::UpdateImpl()
{
	Singleton<AudioSystem>::GetInstance().Update();

	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('9')) {
		Singleton<SceneManager>::GetInstance().LoadScene(TITLE);
	}
}
