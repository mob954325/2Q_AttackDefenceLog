#include "TitleNodeManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Datas/EngineData.h"
#include "Platform/Input.h"
#include "Utils/GameTime.h"
#include "Scripts/SceneCore.h"
#include "Application/AppPaths.h"

void TitleNodeManager::OnCreate()
{
	owner->GetTransform().SetUnityCoords(false);
	patternDrawer = owner->AddComponent<PatternDrawerComponent>();
	patternDrawer->SetBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprite\\Mushroom.png");

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
				nodeOverlap[i] = true;
			}
		}
	}
	else // 마우스 왼쪽 클릭 땔 때
	{
		for (int i = 0; i < 2; i++)
		{
			if (!nodeOverlap[i]) return;
		}

		// 모든 노드를 건듦
		isSlice = true;

		D2D1_MATRIX_3X2_F node1Mat = nodes[0]->owner->GetTransform().ToWorldMatrix();
		D2D1_MATRIX_3X2_F node2Mat = nodes[1]->owner->GetTransform().ToWorldMatrix();

		patternDrawer->SetLine({ {{ node1Mat.dx, node1Mat.dy }, { node2Mat.dx ,node2Mat.dy }}});
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
		Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::MENU);
	}
}

// 각 노드(nodeObject)는 판정을 한다
// 1. 클릭 시 노드가 true면 해당 위치를 저장한다.
// 2 - 1. 클릭 종료 시 위치 두 개를 확인하여 위치 값이 2개가 있으면 PatternDrawerComponent에서 선을 그린다.
// 2 - 2. 만약 2 - 1번에서 위치 값 개수가 두 개가 아니면 모든 위치 값은 제거되고 위 반응을 계속 확인한다.
// 3. 선을 그린 뒤 1초 뒤에 씬이 넘어간다. -> 내부에서 타이머 체크하기