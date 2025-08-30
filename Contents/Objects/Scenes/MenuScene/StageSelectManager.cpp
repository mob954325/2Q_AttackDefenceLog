#include "StageSelectManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "Utils/GameTime.h"
#include "Scripts/GameManager.h"
#include "Scripts/SelectSeal/SelectSeal.h"

#include "Objects/Scenes/TitleScene/EffectProgress.h"
#include "Objects/Scenes/TutorialScene/TutorialEnterObject.h"

void StageSelectManager::OnCreate()
{
}

void StageSelectManager::OnStart()
{
	progress = 0.0f; //8.27 추가
	isDone = false; // 해당 값을 기반으로, Update에서 알파값을 올려줄꺼임

	CreateMenuObjects();

	GameObject* obj = new GameObject();
	obj->SetName("tutorialEnterSlice");
	obj->GetTransform().SetParent(&(this->owner->GetTransform()));

	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	tutorial = obj->AddComponent<SliceableObject>();
	tutorial->SetOpacity(0.0f);
	obj->GetTransform().SetPosition(-800, -100);
	tutorial->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\enemySelect\\tutorial_ui.png");

	tutorial->AddEvent([this]()
		{
			if (Singleton<GameManager>::GetInstance().IsStage1Clear()) return;
			if (Singleton<GameManager>::GetInstance().IsStage2Clear()) return;
			if (Singleton<GameManager>::GetInstance().IsStage3Clear()) return; // 상남자 코딩

			if (!isSceneChange)
			{
				isSceneChange = true;
				isTutorialEnter = true;
			}
		});


	objs[0]->owner->GetTransform().SetPosition(-400, 200);
	objs[1]->owner->GetTransform().SetPosition(0, 0);
	objs[2]->owner->GetTransform().SetPosition(400, 400);

	ChangeImageByClearState();

	objs[0]->AddEvent([this]()
		{
			if (Singleton<GameManager>::GetInstance().IsStage1Clear()) return;

			if (!isSceneChange)
			{
				Singleton<GameManager>::GetInstance().SetBattleStage(SceneCount::STAGE1);
				isSceneChange = true;
			}
		});
	objs[1]->AddEvent([this]()
		{
			if (Singleton<GameManager>::GetInstance().IsStage2Clear()) return;

			if (!isSceneChange)
			{
				Singleton<GameManager>::GetInstance().SetBattleStage(SceneCount::STAGE2);
				isSceneChange = true;
			}
		});
	objs[2]->AddEvent([this]()
		{
			if (Singleton<GameManager>::GetInstance().IsStage3Clear()) return;

			if (!isSceneChange)
			{
				Singleton<GameManager>::GetInstance().SetBattleStage(SceneCount::STAGE3);
				isSceneChange = true;
			}
		});


	objs[0]->SetActive(false);
	objs[1]->SetActive(false);
	objs[2]->SetActive(false);
}

void StageSelectManager::OnUpdate()
{
	// 게임 상태가 Pause면 Update 중단
	if (Singleton<GameManager>::GetInstance().GetGameState() == GameState::Pause)
	{
		return;
	}

	if (!isDone) {
		progress += 0.2f * Singleton<GameTime>::GetInstance().GetDeltaTime();
		if (progress >= 1.0f) {
			isDone = true;
		}

		float cap = EffectProgress::NormalizeProgress(progress, 0.8f, 0.9f);

		if (cap == 0.0f) {
			objs[0]->SetActive(false);
			objs[1]->SetActive(false);
			objs[2]->SetActive(false);
			tutorial->SetActive(false);
		}
		else {
			objs[0]->SetActive(true);
			objs[1]->SetActive(true);
			objs[2]->SetActive(true);
			tutorial->SetActive(true);
		}

		objs[0]->SetOpacity(cap);
		objs[1]->SetOpacity(cap);
		objs[2]->SetOpacity(cap); // 상남자 코딩(8.27.)		
		tutorial->SetOpacity(cap);
	}

	if (isSceneChange)
	{
		timer += Singleton<GameTime>::GetInstance().GetDeltaTime();

		if (timer >= maxTimer)
		{
			if (isTutorialEnter) {
				//Singleton<SceneManager>::GetInstance().LoadScene(TUTORIAL);
				
				auto enter = owner->GetQuery()->FindByName("tutorialEnter");
				if (enter) {
					Singleton<GameManager>::GetInstance().SetGameState(Pause);
					enter->GetComponent<TutorialEnterObject>()->Show();		
				}

				isSceneChange = false;
				isTutorialEnter = false;
				timer = 0.0f;
			}
			else {
				Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::SELECT);
			}

		}
	}
}

void StageSelectManager::OnDestroy()
{
	objs.clear();
}

void StageSelectManager::CreateMenuObjects()
{
	for (int i = 0; i < 3; i++)
	{
		GameObject* obj = new GameObject();
		obj->SetName("stage" + std::to_string(i + 1));
		obj->GetTransform().SetParent(&(this->owner->GetTransform()));

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		SliceableObject* comp = obj->AddComponent<SliceableObject>();
		comp->SetOpacity(0.0f); //  8.27.추가, 0.0f 불투명도로 시작
		objs.push_back(comp);
	}

}

void StageSelectManager::ChangeImageByClearState()
{
	if (!Singleton<GameManager>::GetInstance().IsStage1Clear())
	{
		objs[0]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\enemySelect\\robby_select_ui_namgung.png");
	}
	else
	{
		objs[0]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\enemySelect\\robby_select_ui_namgung.png");
		objs[0]->SetSliceable(false);

		GameObject* sealObject = new GameObject();
		auto sealComp = sealObject->AddComponent<SelectSeal>();
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(sealObject);

		Vector2 objPos = objs[0]->owner->GetTransform().GetPosition();
		D2D1_SIZE_F size = sealComp->owner->GetComponent<BitmapRenderer>()->GetResource()->GetBitmap()->GetSize();
		sealObject->GetTransform().SetPosition(objPos.x - size.width * 0.15f, objPos.y + size.width * 0.1f);
	}

	if (!Singleton<GameManager>::GetInstance().IsStage2Clear())
	{
		objs[1]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\enemySelect\\robby_select_ui_mountain_front.png");
	}
	else
	{
		objs[1]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\enemySelect\\robby_select_ui_mountain_front.png");
		objs[1]->SetSliceable(false);

		GameObject* sealObject = new GameObject();
		auto sealComp = sealObject->AddComponent<SelectSeal>();
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(sealObject);

		Vector2 objPos = objs[1]->owner->GetTransform().GetPosition();
		D2D1_SIZE_F size = sealComp->owner->GetComponent<BitmapRenderer>()->GetResource()->GetBitmap()->GetSize();
		sealObject->GetTransform().SetPosition(objPos.x - size.width * 0.15f, objPos.y + size.width * 0.1f);
	}

	if (!Singleton<GameManager>::GetInstance().IsStage3Clear())
	{
		objs[2]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\enemySelect\\robby_select_ui_mountain_peak.png");
	}
	else
	{
		objs[2]->SetImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\enemySelect\\robby_select_ui_mountain_peak.png");
		objs[2]->SetSliceable(false);

		GameObject* sealObject = new GameObject();
		auto sealComp = sealObject->AddComponent<SelectSeal>();
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(sealObject);

		Vector2 objPos = objs[2]->owner->GetTransform().GetPosition();
		D2D1_SIZE_F size = sealComp->owner->GetComponent<BitmapRenderer>()->GetResource()->GetBitmap()->GetSize();
		sealObject->GetTransform().SetPosition(objPos.x - size.width * 0.15f, objPos.y + size.width * 0.1f);
	}
}