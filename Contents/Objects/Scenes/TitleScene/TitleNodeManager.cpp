#include "TitleNodeManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Datas/EngineData.h"
#include "Platform/Input.h"
#include "Utils/GameTime.h"
#include "Scripts/SceneCore.h"
#include "Application/AppPaths.h"
#include "../Contents/Objects/Sound/SoundTittle.h"

void TitleNodeManager::OnCreate()
{
	owner->GetTransform().SetUnityCoords(false);
	owner->SetRenderLayer(EngineData::RenderLayer::UI);
	patternDrawer = owner->AddComponent<PatternDrawerComponent>();	
	patternDrawer->SetBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\test1.png");
	patternDrawer->SetOrderInLayer(100);

	for (int i = 0; i < 2; i++)
	{
		GameObject* obj = new GameObject();
		obj->SetName("obj" + std::to_string(i));
		obj->GetTransform().SetPosition(gap * i, 0);
		obj->GetTransform().SetParent(&owner->GetTransform());
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);

		auto comp = obj->AddComponent<NodeObject>();
		nodes.push_back(comp);
		nodeOverlap.push_back(false);
	}

	// 연출 에니메이션 추가
	GameObject* animObj = new GameObject();
	animObj->GetTransform().SetUnityCoords(true);
	animObj->SetRenderLayer(EngineData::RenderLayer::UI);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(animObj);

	whiteAnim = animObj->AddComponent<AnimationRenderer>();
	whiteAnim->SetOrderInLayer(111100);
	whiteAnim->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\attack_line_spreadsheet.png");
	whiteAnim->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\WhiteAttack\\attack_line_spreadsheet_sprites.json");
	whiteAnim->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\WhiteAttack\\attack_line_anim.json");
	whiteAnim->SetActive(false);
	whiteAnim->GetAnimationPlayer()->Pause();
	whiteAnim->GetAnimationPlayer()->SetLoop(false);

	//whiteAnim->SetFlipX(true);
}

void TitleNodeManager::OnStart()
{
	D2D1_SIZE_F size = nodes[0]->owner->GetComponent<BitmapRenderer>()->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetPosition(EngineData::SceenWidth / 2 - gap / 2 - size.width / 2, EngineData::SceenHeight / 2);
}

void TitleNodeManager::OnUpdate()
{
	HandleSliceNode();
	HandleSceneChangeTimer();
}

void TitleNodeManager::HandleSliceNode()
{
	if (Input::leftButtonDown) // 마우스 왼쪽 클릭 시 
	{
		for (int i = 0; i < 2; i++)
		{
			if (nodes[i]->IsOverlap())
			{
				if (firstHitIndex == -1)
				{
					firstHitIndex = i; // 첫번째 닿은 노드 인덱스 저장
				}

				nodeOverlap[i] = true;
			}
		}
	}
	else // 마우스 왼쪽 클릭 땔 때
	{
		for (int i = 0; i < 2; i++)
		{
			if (!nodeOverlap[i]) // 겹친 인덱스 없으면 취소
			{
				firstHitIndex = -1;
				return;
			}
		}

		// 모든 노드를 건듦
		isSlice = true;

		D2D1_MATRIX_3X2_F node1Mat = nodes[0]->owner->GetTransform().ToWorldMatrix();
		D2D1_MATRIX_3X2_F node2Mat = nodes[1]->owner->GetTransform().ToWorldMatrix();

		patternDrawer->SetLine({ {{ node1Mat.dx, node1Mat.dy }, { node2Mat.dx ,node2Mat.dy }}});

		if (!isPlayAnim)
		{
			if (firstHitIndex == 1)
			{
				whiteAnim->SetFlipX(true);
				Vector2 pos = nodes[1]->owner->GetTransform().GetPosition();
				whiteAnim->owner->GetTransform().SetPosition(pos.x - EngineData::SceenWidth * 0.2f, pos.y);
			}
			else
			{
				Vector2 pos = nodes[0]->owner->GetTransform().GetPosition();
				whiteAnim->owner->GetTransform().SetPosition(pos.x, pos.y);
			}

			whiteAnim->SetActive(true);
			whiteAnim->GetAnimationPlayer()->Reset();
			whiteAnim->GetAnimationPlayer()->Play();

			auto SoundCom = owner->GetQuery()->FindByName("SOUNDMENU");
			if (SoundCom) {
				SoundCom->GetComponent<SoundTittle>()->SetKeyHandle(L"Attack01");
				SoundCom->GetComponent<SoundTittle>()->PlaySound();;
			}

			isPlayAnim = true;
		}
	}

	if (isPlayAnim && (whiteAnim->GetAnimationPlayer()->GetCurrentFrame() == whiteAnim->GetAnimationPlayer()->GetMaxFrame() - 1))
	{
		whiteAnim->SetActive(false);
	}
}

void TitleNodeManager::HandleSceneChangeTimer()
{
	if (isSlice && timer < maxTimer)
	{
		timer += Singleton<GameTime>::GetInstance().GetDeltaTime();
	}

	if (!isSceneChange && timer >= maxTimer)
	{
		isSceneChange = true;
		//Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::MENU);
		onononStart.Invoke();
		for (int i = 0; i < nodes.size(); ++i) {
			nodes[i]->owner->GetComponent<BitmapRenderer>()->SetActive(false);
		}
		owner->GetComponent<PatternDrawerComponent>()->SetActive(false);
	}
}

// 각 노드(nodeObject)는 판정을 한다
// 1. 클릭 시 노드가 true면 해당 위치를 저장한다.
// 2 - 1. 클릭 종료 시 위치 두 개를 확인하여 위치 값이 2개가 있으면 PatternDrawerComponent에서 선을 그린다.
// 2 - 2. 만약 2 - 1번에서 위치 값 개수가 두 개가 아니면 모든 위치 값은 제거되고 위 반응을 계속 확인한다.
// 3. 선을 그린 뒤 1초 뒤에 씬이 넘어간다. -> 내부에서 타이머 체크하기