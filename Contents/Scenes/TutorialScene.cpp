#include "TutorialScene.h"
#include "Application/AppPaths.h"
#include "../Engine/Systems/AudioSystem.h"

#include "Objects/Common/InputObject.h"
#include "Objects/Scenes/Stage/StageBGI.h"
#include "Objects/Common/PatternControlObject.h"
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


	std::cout << "스테이지1 진입" << std::endl;

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj, "InputStage1");

	GameObject* nodePanel = new GameObject();
	nodePanel->AddComponent<BackboardObject>();
	AddGameObject(nodePanel);

	PCO = new GameObject();
	auto comp = PCO->AddComponent<PatternControlObject>();
	AddGameObject(PCO , "PatternControlObject");
	comp->GetEnemy()->SetNameDiff("Stage1", Singleton<GameManager>::GetInstance().GetDifficultyString());

	stageBGI = new GameObject();
	stageBGI->AddComponent<StageBGI>();
	AddGameObject(stageBGI, "StageBGI1");

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
	AddGameObject(SoundStageOne, "SOUNDSTAGE"); // SOUNDSTAGE << 이름 유지해주세요

	/*SoundStageOne->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Stage01");
	SoundStageOne->GetComponent<SoundPlayScene>()->PlaySound();*/
	
	Textbox = new GameObject();
	auto bb = Textbox->AddComponent<BubbleBox>();
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
	enemyProfileComp->SetProfileImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\StageTop\\ProfileUI\\enemy3_ui.png");
	enemyProfileComp->owner->GetTransform().SetPosition(EngineData::SceenWidth * 0.95f, 1);
	AddGameObject(enemyProfileUIObj, "enemyProfileUIObj");

	//D2D1_RECT_F HiteffectPlayer = { 570.0f,  680.0f , 970.0f,  810.0f };
	//randomBox = new GameObject();  // 97
	//randomBox->AddComponent<BoxRenderer>();
	//AddGameObject(randomBox, "randombox");
	//randomBox->GetTransform().SetUnityCoords(false);
	//randomBox->GetComponent<BoxRenderer>()->SetOrderInLayer(90000);

	//D2D1_RECT_F A{};
	//A.left = 570.0f;
	//A.right = 970.0f;
	//A.top = 680.0f;
	//A.bottom = 810.0f;

	//randomBox->GetComponent<BoxRenderer>()->SetRect(A);

	GameObject* obj = new GameObject();
	auto vi = obj->AddComponent<Vignette>();
	AddGameObject(obj, "Vignette");
}

void TutorialScene::OnExitImpl()
{
	std::cout << "스테이지1 이탈" << std::endl;
	Singleton<AudioSystem>::GetInstance().ReSetChannel();
}

void TutorialScene::UpdateImpl()
{
	Singleton<AudioSystem>::GetInstance().Update();

	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('2')) {
		Singleton<SceneManager>::GetInstance().LoadScene(END);
	}
}
