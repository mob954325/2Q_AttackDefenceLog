#include "HSKScene.h"
#include "Components/Logic/InputSystem.h"
#include "TrailComponent.h"

using namespace HSK;
void HSKScene::OnEnterImpl()
{
	obj = new GameObject();
	obj->SetName("trailTestObj");
	obj->AddComponent<TrailComponent>();
	AddGameObject(obj);


}

void HSKScene::OnExitImpl()
{





}

void HSKScene::UpdateImpl()
{

	obj->GetTransform().SetPosition(1.0f, 1.0f);




}
