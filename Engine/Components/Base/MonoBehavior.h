#pragma once
#include "Components/Logic/ScriptComponent.h"
#include "Components/Base/ActiveComponent.h"

/// <summary>
/// 사용자 정의 컴포넌트 
/// </summary>
class MonoBehavior : public ActiveComponent
{
public:	
	virtual void OnUpdate() {};
	virtual void OnFixedUpdate() {};

	// 충돌처리 함수, 매개변수는 충돌 대상
	virtual void OnColliderEnter(GameObject* collider) {}
	virtual void OnColliderStay(GameObject* collider) {}
	virtual void OnColliderExit(GameObject* collider) {}
	virtual void OnTriggerEnter(GameObject* collider) {}
	virtual void OnTriggerStay(GameObject* collider) {}
	virtual void OnTriggerExit(GameObject* collider) {}
};