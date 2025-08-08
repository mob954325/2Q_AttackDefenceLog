#include "Scene.h"
#include "Utils/Singleton.h"
#include "Systems/TransformSystem.h"
#include "Systems/ScriptSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/PhysicSystem.h"
#include "Systems/MonoBehaviorSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Systems/UISystem.h"

#include "Utils/GameTime.h"

#pragma region Event Update
void Scene::OnEnter()
{
	state = SceneState::Enter;
	OnEnterImpl();

	state = SceneState::Playing;
}

void Scene::PostUpdate()
{
	AddCreatedObjects();										// 생성된 게임 오브젝트 활성화 오브젝트로 변경
	Singleton<MonoBehaviorSystem>::GetInstance().ProcessPendingComponents(); // MonoBehavior 지연 등록 확인
	CheckGameObjectStartQueue();								// component OnStart 처리, NOTE: Fixed 쪼개면 PostUpdate 만들어서 넣기 
}

void Scene::FixedUpdate(std::vector<CollisionInfo>& collisionInfos)
{
	Singleton<MonoBehaviorSystem>::GetInstance().FixedUpdate();		// MonoBehavior 처리
	Singleton<CollisionSystem>::GetInstance().FixedUpdate(collisionInfos);
	Singleton<PhysicSystem>::GetInstance().FixedUpdate(collisionInfos);
}

void Scene::Update()
{
	Singleton<MonoBehaviorSystem>::GetInstance().Update();		// MonoBehavior 처리
	Singleton<ScriptSystem>::GetInstance().Update();			// 컴포넌트 기반 스크립트 처리
	Singleton<TransformSystem>::GetInstance().Update();			// Transform 연산
	//if (state == SceneState::ReadyToChange) return;

	UpdateImpl();
	// if (state == SceneState::ReadyToChange) return;
}

void Scene::LateUpdate()
{
	Singleton<CameraManager>::GetInstance().Update();	// 카메라 순서 업데이트
	Singleton<UISystem>::GetInstance().Update();		// UI 업데이트
}

void Scene::OnExit()
{
	OnExitImpl();

	// 모든 오브젝트 제거

	for (GameObject* obj : objectsToAdd)
	{
		obj->Destroy();
	}

	for (GameObject* obj : activeObjects)
	{
		obj->Destroy();
	}

	for (GameObject* obj : objectsToDestroy)
	{
		obj->Destroy();
	}

	objectsToAdd.clear();
	activeObjects.clear();
	objectsToDestroy.clear();
	state = SceneState::Exit;
}
#pragma endregion

#pragma region Control GameObject
void Scene::CleanUpDestroyedObjects()
{
	FindRemoveObject();

	for (GameObject* targetObject : objectsToDestroy)
	{
		auto it = std::find(activeObjects.begin(), activeObjects.end(), targetObject);
		if (it != activeObjects.end())
		{
			GameObject* obj = *it;
			activeObjects.erase(it);	// 먼저 erase
			obj->Destroy();			// obj의 Destroy 호출
			delete obj;				// 그 다음 delete
		}
	}
	objectsToDestroy.clear();
}

void Scene::AddGameObject(GameObject* gameObject)
{
	objectsToAdd.push_back(gameObject);
	gameObject->SetQuery(this);

	// Singleton<TransformSystem>::GetInstance().Register(&gameObject->GetTransform()); // NOTE: 0709추가 TransformSystem에 transform 추가
}

void Scene::AddGameObject(GameObject* gameObject, const std::string& name)
{
	AddGameObject(gameObject);
	gameObject->SetQuery(this);

	// Singleton<TransformSystem>::GetInstance().Register(&gameObject->GetTransform());
}

void Scene::FindRemoveObject()
{
	std::vector<GameObject*>::iterator it = activeObjects.begin();

	for (; it != activeObjects.end(); it++)
	{
		if ((*it)->IsMarkedForRemoval()) // 제거할 오브젝트 찾음
		{
			objectsToDestroy.push_back(*it);
		}
	}
}

GameObject* Scene::FindByName(const std::string& name) const
{
	for (auto object : activeObjects)
	{
		if (name == object->GetName())
		{
			return object;
		}
	}

	return nullptr;
}

void Scene::AddCreatedObjects()
{
	for (GameObject* obj : objectsToAdd)
	{
		activeObjects.push_back(obj);
		obj->MarkSetupComplete();	
	}

	objectsToAdd.clear();
}

void Scene::CheckGameObjectStartQueue()
{
	for (GameObject* obj : activeObjects)
	{
		obj->ProcessStartQeue();
	}
}

#pragma endregion
