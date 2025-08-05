#pragma once
#include "Components/Base/GameObject.h"
#include "Components/Base/Component.h"
#include "Systems/ScriptSystem.h"
#include "Systems/RenderSystem.h"
#include "Scene/GameObjectQuery.h"
#include "Datas/CollisionInfo.h"
#include <vector>

/// <summary>
/// 현재 씬 상태 enum
/// </summary>
enum SceneState
{	
	Enter = 0,		// 씬 전환 후 시작 시
	Playing,		// 씬 업데이트 중이고 씬 교체가 없을 때
	ReadyToChange,	// 다음 프레임에 씬 교체가 시작될 때
	Exit,			// 씬 내 데이터 정리 후 Enter 전 
};

// NOTE : AddGameObject한 객체는 Scene내부에서 delete를 호출해서 메모리 해제를 함

/// <summary>
/// SceneMnaager가 관리하는 Scene 클래스
/// </summary>
class Scene : public IGameObjectQuery
{
friend class SceneManager; // NOTE: SceneManager가 직접적으로 접근하게 만들고싶어서 선언 (25.07.14)

public:
	/// <summary>
	/// 등록된 오브젝트의 Start문 실행
	/// </summary>
	void OnEnter();

	/// <summary>
	/// FixedUpdate 이전에 실행되는 함수
	/// </summary>
	void PostUpdate();

	/// <summary>
	/// 게임 오브젝트 파괴 리스트 순환 후 UpdateImpl() 호출
	/// </summary>
	void Update();

	/// <summary>
	/// 게임 물리 업데이트
	/// </summary>
	void FixedUpdate(std::vector<CollisionInfo>& collisionInfos);

	/// <summary>
	/// 모든 업데이트 끝나고 실행
	/// </summary>
	void LateUpdate();

	/// <summary>
	/// 등록된 오브젝트 OnDestroy() 실행
	/// </summary>
	void OnExit();	

	/// <summary>
	/// 제거 목록에 등록된 모든 게임 오브젝트 제거
	/// </summary>
	void CleanUpDestroyedObjects();

	// GameObject 제어 함수
	void AddGameObject(GameObject* gameObject);
	void AddGameObject(GameObject* gameObject, const std::string& name);
	void FindRemoveObject();

	GameObject* FindByName(const std::string& name) const override;

protected:
	void AddCreatedObjects();
	void CheckGameObjectStartQueue();

	/// <summary>
	/// Scene을 상속 받은 클래스가 씬 시작 시 실행할 내용
	/// </summary>
	virtual void OnEnterImpl() = 0;

	/// <summary>
	/// Scene을 상속 받은 클래스가 씬 종료 시 실행할 내용
	/// </summary>
	virtual void OnExitImpl() = 0;

	/// <summary>
	/// Scene 상속 받은 클래스가 Update문 실행할 내용 ( Scene::Update() 에서 호출 )
	/// </summary>
	virtual void UpdateImpl() = 0;

	std::vector<GameObject*> activeObjects;		// 매 프레임마다 업데이트되는 오브젝트들
	std::vector<GameObject*> objectsToDestroy;	// 모든 업데이트가 끝난 시점에서 제거될 오브젝트들
	std::vector<GameObject*> objectsToAdd;		// 다음 프레임에 activeObjects에 포함될 오브젝트들

	SceneState state = SceneState::Exit;
};