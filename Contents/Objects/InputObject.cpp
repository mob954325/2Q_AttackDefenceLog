#include "InputObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "../Engine/Components/Logic/InputSystem.h"

void InputObject::OnStart()
{
	owner->AddComponent<InputSystem>();
}

void InputObject::OnUpdate()
{

}

void InputObject::OnDestroy()
{
}


