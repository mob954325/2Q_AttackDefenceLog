#include "EndScene.h"
#include "../Engine/Components/Logic/InputSystem.h"
#include "../Engine/Systems/AudioSystem.h"

#include "Objects/Common/InputObject.h"
#include "Objects/Common/MouseTrailObject.h"
#include "Objects/Common/TestObject.h"
#include "Objects/Sound/SoundEnd.h"
#include "../Engine/Systems/AudioSystem.h"
#include "Scripts/End/EndBackground.h"
#include "Scripts/BubbleBox/BubbleEnd.h"
#include "../Contents/Scripts/GameManager.h"

void EndScene::OnEnterImpl()
{
	std::cout << "엔드씬 진입" << std::endl;

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);
	
	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	AddGameObject(trail, "MouseTrail");

	//testObj = new GameObject();
	//testObj->AddComponent<TestObject>();
	//AddGameObject(testObj);

	Singleton<AudioSystem>::GetInstance().ReSetChannel();

	SoundEndObj = new GameObject();
	SoundEndObj->AddComponent<SoundEnd>();
	AddGameObject(SoundEndObj, "EndSound");

	SoundEndObj->GetComponent<SoundEnd>()->SetKeyHandle(L"End");
	SoundEndObj->GetComponent<SoundEnd>()->PlaySound();

	GameObject* ebg = new GameObject();
	ebg->AddComponent<EndBackground>();
	AddGameObject(ebg, "EndBackGround");

	GameObject* bbe = new GameObject();
	bbe->AddComponent<BubbleEnd>();
	AddGameObject(bbe, "BubbleEnd");


	Singleton<GameManager>::GetInstance().Reset();
}

void EndScene::OnExitImpl()
{
	std::cout << "엔드씬 이탈" << std::endl;
	Singleton<AudioSystem>::GetInstance().ReSetChannel();
}

void EndScene::UpdateImpl()
{
	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('2')) {
		Singleton<SceneManager>::GetInstance().LoadScene(MENU);
	}

	Singleton<AudioSystem>::GetInstance().Update();
}

