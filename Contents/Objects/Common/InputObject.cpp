#include "InputObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"


void InputObject::OnStart()
{
	inputs = owner->AddComponent<InputSystem>();


	GameObject* camI = new GameObject;
	camI->AddComponent<CamInstance>();
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(camI, "CAM"); // 나중에 쿼리로 호출해서 흔들어줘야함(중요)

}

void InputObject::OnUpdate()
{
	//if (inputs->IsKeyPressed('0')) {
	//	auto camIns = owner->GetQuery()->FindByName("CAM");
	//	if (camIns) { camIns->GetComponent<CamInstance>()->Start(5.0f, 10.0f, 10.0f, ShakeType::X); }
	//}

}

void InputObject::OnDestroy()
{
}


