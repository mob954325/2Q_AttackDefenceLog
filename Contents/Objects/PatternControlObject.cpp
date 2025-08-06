#include "PatternControlObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "../Objects/Stage/NodeObject.h"
#include "../Engine/Components/Rendering/PatternDrawerComponent.h"
#include "../Objects/MouseTrailObject.h"
#include "../Engine/Components/Rendering/ChainDrawerComponent.h"

void PatternControlObject::OnCreate()
{
	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(trail, "MouseTrail");

	for (int i = 0; i < 9; ++i) {
		m_nodes[i] = new GameObject();
		auto nodeComponent = m_nodes[i]->AddComponent<NodeObject>();
		std::string name = "Node." + std::to_string(i + 1);
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(m_nodes[i], name);
	}

	guideline = new GameObject();
	guideline->SetRenderLayer(EngineData::RenderLayer::None);
	auto c = guideline->AddComponent<ChainDrawerComponent>();
	c->SetBitmap(L"../Workspace/HSK/Test/TestArrow_2.png");
	c->SetFillBitmap(L"../Workspace/HSK/Test/TestArrow_1.png");
	c->SetOrderInLayer(0);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(guideline);
	//auto asd = m_nodes[4]->GetComponent<NodeObject>()->GetSize();
}

void PatternControlObject::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);
	auto d = owner->AddComponent<PatternDrawerComponent>();
	d->SetOrderInLayer(80);
	d->SetBitmap(L"../WorkSpace/HSK/Test/test5.png");

	float n = 200.0f; // 노드간의 간격
	for (int i = 0; i < 9; ++i) {
		int col = i % 3 - 1; // -1 0 1
		int row = i / 3 - 1; // -1 0 1

		float x = 960.0f + col * n;
		float y = 540.0f + row * n;

		m_nodes[i]->GetTransform().SetPosition(x, y);
	}

	PM.SetNodes(m_nodes, 45.0f);
	auto c = guideline->GetComponent<ChainDrawerComponent>();

	c->SetupNodes(m_nodes[4]->GetTransform().GetPosition(), n, { 91.0f , 101.0f }); // 스타트에서 하기
}

void PatternControlObject::OnUpdate()
{
	auto t = trail->GetComponent<TrailComponent>();
	t->isOutFromBox = PM.CheckOutOfBox({ Input::MouseX, Input::MouseY }); // 마우스 좌표 기반으로, 박스 밖으로 나갔는지 확인

	if (t->isNewCached) { // 새로운 노드 발생하면		

		PM.CheckTrails(t->CheckingCachedTrails());
		const auto& vec = PM.GetPatternPathPositions(); // 여기에 담김!!! 1 3 2 4 이런거 <<<<< (연결지점)

		auto c = guideline->GetComponent<ChainDrawerComponent>();
		auto d = owner->GetComponent<PatternDrawerComponent>();
		d->SetLine(vec);
		if (!vec.empty()) // 노드가 그어졌다면, 바로 삭제해서 가시성 up
			t->Clear();


		c->SliceRect(PM.GetPattern());
		c->Progress(0.5f);

		for (int value : PM.GetPattern()) { std::cout << value << "-"; }
		std::cout << std::endl << std::endl;
	}
}

void PatternControlObject::OnDestroy()
{


}


