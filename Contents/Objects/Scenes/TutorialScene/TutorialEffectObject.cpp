#include "TutorialEffectObject.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"
#include "Scene/SceneManager.h"
#include "../Engine/Components/Logic/InputSystem.h"
//#include "Objects/Scenes/TitleScene/EffectProgress.h"


void TutorialEffectObject::OnCreate()
{

}


void TutorialEffectObject::OnStart()
{
	owner->AddComponent<InputSystem>();
	//==================================================================================
	// 파일 조정하는 부분, 현재 2~31
	auto basePath = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\Tutorial\\";
	std::vector<std::wstring> files;
	for (int i = 2; i < 32; ++i)
		files.emplace_back(std::wstring(L"tutorial_") + std::to_wstring(i) + L".png");
	//==================================================================================

	for (int i = 0; i < files.size(); ++i) {
		GameObject* obj = new GameObject();
		obj->GetTransform().SetUnityCoords(false);
		obj->SetRenderLayer(EngineData::RenderLayer::UI);

		auto br = obj->AddComponent<BitmapRenderer>();
		br->CreateBitmapResource(basePath + files[i]);
		br->SetOrderInLayer(i + 10);
		br->SetActive(false);

		slideImages.push_back(br);
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj, "tutorialImage." + i);
	}

	index = 0;
	isPlay = true;
}

void TutorialEffectObject::OnUpdate() // 업데이트
{
	if (!isPlay) return;
	//여기에 pause 넣으면 안됨

	inputMouse = owner->GetComponent<InputSystem>()->IsMouseButtonDown(Left);

	if (inputMouse && !cachedInputMouse) { // 지금 눌림 + 이전 안눌림
		std::cout << "튜토리얼 마우스 눌림 감지됨" << std::endl;
		//====================================================================
		if (index < slideImages.size()) { // 31 -> 32까지만 구현

			if (index >= 1) slideImages[index - 1]->SetActive(false);	
			slideImages[index]->SetActive(true);
			index++;
		}
		//====================================================================
	}
	cachedInputMouse = inputMouse;
}