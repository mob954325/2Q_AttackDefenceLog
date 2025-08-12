#include "Stage3.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"
#include "Objects/Sound/SoundPlayScene.h"
#include "../Engine/Systems/AudioSystem.h"

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
