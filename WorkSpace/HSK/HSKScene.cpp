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

	for (int i = 0; i < 9; ++i) {
		m_nodes[i] = new GameObject();
		auto nodeComponent = m_nodes[i]->AddComponent<NodeObj>();
		std::string name = "node" + std::to_string(i + 1);
		AddGameObject(m_nodes[i], name);
	}

	m_nodes[0]->GetTransform().SetPosition(100, 0);
	m_nodes[1]->GetTransform().SetPosition(400, 0);
	m_nodes[2]->GetTransform().SetPosition(700, 0);
	m_nodes[3]->GetTransform().SetPosition(100, 300);
	m_nodes[4]->GetTransform().SetPosition(400, 300);
	m_nodes[5]->GetTransform().SetPosition(700, 300);
	m_nodes[6]->GetTransform().SetPosition(100, 600);
	m_nodes[7]->GetTransform().SetPosition(400, 600);
	m_nodes[8]->GetTransform().SetPosition(700, 600);
}

void HSKScene::OnExitImpl()
{



}

bool isNodeInitialized = false; // 상남자 코딩

void HSKScene::UpdateImpl()
{
	if (!isNodeInitialized) {
		PM.SetNodes(m_nodes, 80.0f);		
		isNodeInitialized = true;
	}
	//Input::leftButtonDown ;
	//Input::rightButtonDown;
	//Input::middleButtonDown;
	auto t = obj->GetComponent<TrailComponent>();
	t->isDraw = Input::leftButtonDown;
	t->isOutFromBox = Input::rightButtonDown;
	obj->GetTransform().SetPosition(Input::MouseX, Input::MouseY);

	if (t->isNewCached) {
		PM.CheckTrails(t->cachedTrails);
		t->isNewCached = false;

		for (int value : PM.GetPattern()) {
			std::cout << value << "-";
		}

		std::cout << std::endl;

	}



}
