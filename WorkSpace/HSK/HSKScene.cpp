#include "HSKScene.h"
#include "Components/Logic/InputSystem.h"
#include "Components/Rendering/TrailComponent.h"
#include "NodeObj.h"
#include "Datas/EngineData.h"
using namespace HSK;

void HSKScene::OnEnterImpl()
{
	obj = new GameObject();
	obj->SetRenderLayer(EngineData::RenderLayer::UI);
	auto t = obj->AddComponent<TrailComponent>();
	t->SetOrderInLayer(100);
	t->SetBitmap(L"../HSK/Test/test5.png");
	AddGameObject(obj, "trail");

	m_node1 = new GameObject();
	m_node1->AddComponent<Node>();
	AddGameObject(m_node1, "node1");
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
