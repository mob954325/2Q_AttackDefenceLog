#include "HSKScene.h"
#include "Components/Logic/InputSystem.h"
#include "Components/Rendering/TrailComponent.h"
#include "NodeObj.h"
#include "Datas/EngineData.h"
#include "../Engine/Resources/ResourceManager.h"
#include "Components/Rendering/PatternDrawerComponent.h"

using namespace HSK;

void HSKScene::OnEnterImpl()
{
	obj = new GameObject();
	obj->SetRenderLayer(EngineData::RenderLayer::UI);
	
	auto t = obj->AddComponent<TrailComponent>();
	t->SetOrderInLayer(100);	

	auto d = obj->AddComponent<PatternDrawerComponent>();
	d->SetOrderInLayer(80);

	t->SetBitmap(L"../HSK/Test/test5.png");
	t->SetTailBitmap(L"../HSK/Test/test1.png");
	t->SetHeadBitmap(L"../HSK/Test/white_brush_test3.png");
	d->SetBitmap(L"../HSK/Test/test5.png");

	AddGameObject(obj, "trail");

	for (int i = 0; i < 9; ++i) {
		m_nodes[i] = new GameObject();
		auto nodeComponent = m_nodes[i]->AddComponent<NodeObj>();
		std::string name = "node" + std::to_string(i + 1);
		AddGameObject(m_nodes[i], name);
	}

	float n = 150.0f;
	for (int i = 0; i < 9; ++i) {
		int col = i % 3; // 0 1 2
		int row = i / 3; // 0 1 2

		float x = 720.0f + col * n; 
		float y = 405.0f + row * n; 

		m_nodes[i]->GetTransform().SetPosition(x, y);
	}
}

void HSKScene::OnExitImpl()
{



}

bool isNodeInitialized = false; // 상남자 코딩

void HSKScene::UpdateImpl()
{
	if (!isNodeInitialized) { // 어쨌든 한번 초기화했죠?
		PM.SetNodes(m_nodes, 45.0f);
		isNodeInitialized = true;
	}

	auto t = obj->GetComponent<TrailComponent>();
	auto d = obj->GetComponent<PatternDrawerComponent>();

	t->isDraw = Input::leftButtonDown;

	obj->GetTransform().SetPosition(Input::MouseX, Input::MouseY);
	t->isOutFromBox = PM.CheckOutOfBox({ Input::MouseX, Input::MouseY });

	if (t->isNewCached) {
		PM.CheckTrails(t->CheckingCachedTrails());
		const auto& vec = PM.GetPatternPathPositions();
		d->SetLine(PM.GetPatternPathPositions());
		if (!vec.empty())
			t->Clear();				

		for (int value : PM.GetPattern()) {
			std::cout << value << "-";
		}
		std::cout << std::endl << std::endl;
	}

}
