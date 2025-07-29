#include "HSKScene.h"
#include "Components/Logic/InputSystem.h"
#include "TrailComponent.h"

using namespace HSK;

void HSKScene::OnEnterImpl()
{
	obj = new GameObject();
	obj->SetName("trailTestObj");
	auto t = obj->AddComponent<TrailComponent>();
	t->SetBitmap(L"../HSK/Test/test5.png");

	AddGameObject(obj);
}

void HSKScene::OnExitImpl()
{





}

void HSKScene::UpdateImpl()
{
	//Input::leftButtonDown ;
	//Input::rightButtonDown;
	//Input::middleButtonDown;
	auto t = obj->GetComponent<TrailComponent>();

	t->isDraw = Input::leftButtonDown;
	t->isOutFromBox = Input::rightButtonDown;

	obj->GetTransform().SetPosition(Input::MouseX, Input::MouseY);
}
