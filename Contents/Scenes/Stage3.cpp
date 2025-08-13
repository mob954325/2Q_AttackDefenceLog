#include "Stage3.h"
#include "Application/AppPaths.h"
#include "../Engine/Systems/AudioSystem.h"

#include "Objects/Common/InputObject.h"
#include "Objects/Sound/SoundPlayScene.h"
#include "Objects/Scenes/Stage/EscMenu/StageESCPanel.h"
#include "Objects/Scenes/Stage/EscMenu/EscContinueButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscExitButton.h"
#include "Objects/Scenes/Stage/EscMenu/EscMuteButton.h"
#include "Objects/Common/PatternControlObject.h"
#include "Objects/Scenes/Stage/Stage3/StageBGI3.h"
#include "Objects/Scenes/Stage/StageTopUI.h"
#include "Objects/Scenes/Stage/StagePlayerProfile.h"
#include "Objects/Scenes/Stage/StageEnemyProfile.h"

#include "Scripts/LiveObject/Enemy.h"
#include "Scripts/GameManager.h"
#include "Scripts/BubbleBox/BubbleBox3.h"

#include "Components/Logic/InputSystem.h"

void Stage3::OnEnterImpl()
{
	Singleton<AudioSystem>::GetInstance().ReSetChannel();
	std::cout << "스테이지3 진입" << std::endl;
	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);

	Singleton<AudioSystem>::GetInstance().ReSetChannel();

	bgObj = new GameObject();
	bgObj->AddComponent<StageBGI3>();
	AddGameObject(bgObj, "StageBGI3");

	SoundStageThree = new GameObject();
	SoundStageThree->AddComponent<SoundPlayScene>();
	AddGameObject(SoundStageThree, "SOUNDSTAGE"); // SOUNDSTAGE << 이름 유지해주세요


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

	Textbox = new GameObject();
	auto bb = Textbox->AddComponent<BubbleBox3>();
	AddGameObject(Textbox, "Textbox");
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
	enemyProfileComp->SetProfileImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\ProfileUI\\enemy2_ui.png");
	enemyProfileComp->owner->GetTransform().SetPosition(EngineData::SceenWidth * 0.95f, 1);
	AddGameObject(enemyProfileUIObj, "enemyProfileUIObj");
}

void Stage3::OnExitImpl()
{
	std::cout << "스테이지3 이탈" << std::endl;
	Singleton<AudioSystem>::GetInstance().ReSetChannel();
}

void Stage3::UpdateImpl()
{
}
