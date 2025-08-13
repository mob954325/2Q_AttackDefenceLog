#include "InputObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "../Engine/Components/Logic/InputSystem.h"

void InputObject::OnStart()
{
	owner->AddComponent<InputSystem>();


	GameObject* camI = new GameObject;
	camI->AddComponent<CamInstance>();
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(camI, "CAM"); // 나중에 쿼리로 호출해서 흔들어줘야함(중요)

}

void InputObject::OnUpdate()
{

}

void InputObject::OnDestroy()
{
}


