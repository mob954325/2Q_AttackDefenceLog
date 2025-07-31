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
	t->SetBitmap(L"../HSK/Test/white_brush_test3.png");
	AddGameObject(obj, "trail");

	for (int i = 0; i < 9; ++i) {
		m_nodes[i] = new GameObject();
		auto nodeComponent = m_nodes[i]->AddComponent<NodeObj>();
		std::string name = "node" + std::to_string(i + 1);
		AddGameObject(m_nodes[i], name);
	}

	m_nodes[0]->GetTransform().SetPosition(300, 200);
	m_nodes[1]->GetTransform().SetPosition(450, 200);
	m_nodes[2]->GetTransform().SetPosition(600, 200);
	m_nodes[3]->GetTransform().SetPosition(300, 350);
	m_nodes[4]->GetTransform().SetPosition(450, 350);
	m_nodes[5]->GetTransform().SetPosition(600, 350);
	m_nodes[6]->GetTransform().SetPosition(300, 500);
	m_nodes[7]->GetTransform().SetPosition(450, 500);
	m_nodes[8]->GetTransform().SetPosition(600, 500);
}

void HSKScene::OnExitImpl()
{



}

bool isNodeInitialized = false; // 상남자 코딩

void HSKScene::UpdateImpl()
{
	if (!isNodeInitialized) {
		PM.SetNodes(m_nodes, 45.0f);
		isNodeInitialized = true;
	}

	auto t = obj->GetComponent<TrailComponent>();
	t->isDraw = Input::leftButtonDown;
	t->isOutFromBox = Input::rightButtonDown;
	obj->GetTransform().SetPosition(Input::MouseX, Input::MouseY);
	t->isOutFromBox = PM.CheckOutOfBox({ Input::MouseX, Input::MouseY }); // AABB < 마우스 나갔는지만 판단해주면 충분함

	if (t->isNewCached) {
		PM.CheckTrails(t->cachedTrails);
		t->isNewCached = false; // 사용했다고 알림

		for (int value : PM.GetPattern()) {
			std::cout << value << "-";
		}
		std::cout << std::endl << std::endl;
	}
}
