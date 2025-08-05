#include "Stage1.h"
//Components
//#include "../Engine/Components/Logic/InputSystem.h"
//#include "../Engine/Components/Rendering/TrailComponent.h"
//#include "../Engine/Components/Rendering/PatternDrawerComponent.h"
//Object
#include "../Objects/InputObject.h"
#include "../Objects/Stage/NodeObject.h"
#include "../Objects/MouseTrailObject.h"
#include "../Objects/Stage/StageBGI.h"


void Stage1::OnEnterImpl()
{
	std::cout << "스테이지1 진입" << std::endl;

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj, "InputStage1");
	
	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	AddGameObject(trail, "MouseTrail");

	//===================================================================

	for (int i = 0; i < 9; ++i) {
		m_nodes[i] = new GameObject();
		auto nodeComponent = m_nodes[i]->AddComponent<NodeObject>();
		std::string name = "Node." + std::to_string(i + 1);
		AddGameObject(m_nodes[i], name);
	}

	//===================================================================

	float n = 200.0f; // 노드간의 간격

	for (int i = 0; i < 9; ++i) {
		int col = i % 3 - 1; // -1 0 1
		int row = i / 3 - 1; // -1 0 1

		float x = 960.0f + col * n;
		float y = 540.0f + row * n;

		m_nodes[i]->GetTransform().SetPosition(x, y);
	}

	stageBGI = new GameObject();
	stageBGI->AddComponent<StageBGI>();
	AddGameObject(stageBGI);
}

void Stage1::OnExitImpl()
{

	std::cout << "스테이지1 이탈" << std::endl;
}

bool isNodeInitialized = false; // 상남자 초기화

void Stage1::UpdateImpl()
{	// 어쨌든 한번 초기화했죠?		
	if (!isNodeInitialized) { PM.SetNodes(m_nodes, 45.0f); isNodeInitialized = true; }
	//===================================================================

	auto t = trail->GetComponent<TrailComponent>();
	t->isOutFromBox = PM.CheckOutOfBox({ Input::MouseX, Input::MouseY }); // 마우스 좌표 기반으로, 박스 밖으로 나갔는지 확인
		
	if (t->isNewCached) { // 새로운 노드 발생하면		

		PM.CheckTrails(t->CheckingCachedTrails());
		const auto& vec = PM.GetPatternPathPositions(); // 여기에 담김!!! 1 3 2 4 이런거 <<<<< (연결지점)

		auto d = trail->GetComponent<PatternDrawerComponent>();
		d->SetLine(vec);
		if (!vec.empty()) // 노드가 그어졌다면, 바로 삭제해서 가시성 up
			t->Clear();

		for (int value : PM.GetPattern()) { std::cout << value << "-"; }
		std::cout << std::endl << std::endl;

	}		

	//===================================================================

	auto input = inputObj->GetComponent<InputSystem>();
	if (input->IsKeyPressed('3')) {
		Singleton<SceneManager>::GetInstance().LoadScene(END);
	}
}