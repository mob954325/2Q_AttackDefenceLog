#include "Stage2.h"
#include "Application/AppPaths.h"
#include "../Engine/Systems/AudioSystem.h"

#include "Objects/Common/InputObject.h"
#include "Objects/Sound/SoundPlayScene.h"
#include "Objects/Scenes/Stage/EscMenu/StageESCPanel.h"
#include "Objects/Scenes/Stage/EscMenu/EscContinueButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscExitButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscMuteButton.h"
#include "Objects/Common/PatternControlObject.h"
#include "Objects/Scenes/Stage/Stage2/StageBGI2.h"
#include "Objects/Scenes/Stage/StageTopUI.h"
#include "Objects/Scenes/Stage/StagePlayerProfile.h"
#include "Objects/Scenes/Stage/StageEnemyProfile.h"

#include "Scripts/LiveObject/Enemy.h"
#include "Scripts/GameManager.h"
#include "Scripts/BubbleBox/BubbleBox2.h"

#include "Components/Logic/InputSystem.h"

void Stage2::OnEnterImpl()
{
	std::cout << "스테이지2 진입" << std::endl;
	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);

	Singleton<AudioSystem>::GetInstance().ReSetChannel();

	bgObj = new GameObject();
	bgObj->AddComponent<StageBGI2>();
	AddGameObject(bgObj, "StageBGI2");

	SoundStageTwo = new GameObject();
	SoundStageTwo->AddComponent<SoundPlayScene>();
	AddGameObject(SoundStageTwo, "SOUNDSTAGE"); // SOUNDSTAGE << 이름 유지해주세요

	PCO = new GameObject();
	auto comp = PCO->AddComponent<PatternControlObject>();
	AddGameObject(PCO, "PatternControlObject");
	comp->GetEnemy()->SetNameDiff("Stage2", Singleton<GameManager>::GetInstance().GetDifficultyString());

	SoundStageTwo->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Stage02");
	SoundStageTwo->GetComponent<SoundPlayScene>()->PlaySound();

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

	Textbox = new GameObject();
	Textbox->AddComponent<BubbleBox2>();
	AddGameObject(Textbox, "Textbox");

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
	enemyProfileComp->SetProfileImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\ProfileUI\\enemy1_ui.png");
	enemyProfileComp->owner->GetTransform().SetPosition(EngineData::SceenWidth * 0.95f, 1);
	AddGameObject(enemyProfileUIObj, "enemyProfileUIObj");
}

void Stage2::OnExitImpl()
{
	std::cout << "스테이지2 이탈" << std::endl;
}

void Stage2::UpdateImpl()
{
}
