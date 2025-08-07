#include "PatternControlObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "../Objects/Stage/NodeObject.h"
#include "../Engine/Components/Rendering/PatternDrawerComponent.h"
#include "../Objects/MouseTrailObject.h"
#include "../Engine/Components/Rendering/ChainDrawerComponent.h"
#include "../Engine/Utils/GameTime.h"

//성빈씨꺼
#include "Scripts/LogicManager/BettleManager.h"
#include "Scripts/LogicManager/AttackPatternManager.h" 
#include "Scripts/LiveObject/Enemy.h"
#include "Scripts/LiveObject/Player.h"
#include "Scripts/CsvData/CsvDataManager.h" // 싱글벙글

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
	//===================================================================================================

	enemyGuideline = new GameObject();
	enemyGuideline->SetRenderLayer(EngineData::RenderLayer::None);
	auto ca = enemyGuideline->AddComponent<ChainDrawerComponent>();
	ca->SetBitmap(L"../Workspace/HSK/Test/TestArrow_2.png");
	ca->SetFillBitmap(L"../Workspace/HSK/Test/TestArrow_1.png");
	ca->SetOrderInLayer(0);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(enemyGuideline);

	playerGuidelineA = new GameObject();
	playerGuidelineA->SetRenderLayer(EngineData::RenderLayer::None);
	auto cb = playerGuidelineA->AddComponent<ChainDrawerComponent>();
	cb->SetBitmap(L"../Workspace/HSK/Test/TestArrow_2.png");
	cb->SetFillBitmap(L"../Workspace/HSK/Test/TestArrow_1.png");
	cb->SetOrderInLayer(0);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(playerGuidelineA);

	playerGuidelineB = new GameObject();
	playerGuidelineB->SetRenderLayer(EngineData::RenderLayer::None);
	auto cc = playerGuidelineB->AddComponent<ChainDrawerComponent>();
	cc->SetBitmap(L"../Workspace/HSK/Test/TestArrow_2.png");
	cc->SetFillBitmap(L"../Workspace/HSK/Test/TestArrow_1.png");
	cc->SetOrderInLayer(0);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(playerGuidelineB);
	//auto asd = m_nodes[4]->GetComponent<NodeObject>()->GetSize();

	//===================================================================================================

	PlayerAtkPetternData* tmp1 = nullptr;
	CsvDataManager::GetInstance().SetCSV<EnemyData>("../Resource/DataTable/적 데이터 테이블.csv"); // 데이터 파일 읽어오기

	EnemyAtkPattenData* tmp2 = nullptr;
	CsvDataManager::GetInstance().SetCSV<EnemyAtkPattenData>("../Resource/DataTable/적 공격 패턴 테이블.csv"); // 데이터 파일 읽어오기

	AllNodePattenClass* tmp3 = nullptr;
	CsvDataManager::GetInstance().SetCSV<AllNodePattenClass>("../Resource/DataTable/노드 전체 패턴 테이블.csv"); // 데이터 파일 읽어오기

	PlayerAtkPetternData* tmp4 = nullptr;
	CsvDataManager::GetInstance().SetCSV<PlayerAtkPetternData>("../Resource/DataTable/플레이어 공격 패턴 테이블.csv"); // 데이터 파일 읽어오기

	PlayerData* tmp5 = nullptr;
	CsvDataManager::GetInstance().SetCSV<PlayerData>("../Resource/DataTable/플레이어 데이터 테이블.csv"); // 데이터 파일 읽어오기

	//===================================================================================================
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//===================================================================================================



	//===================================================================================================
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//===================================================================================================

	attackPattenManager = new GameObject();                    // GameObject 객체 생성
	attackPattenManager->AddComponent<AttackPatternManager>(); // MonoBehaivor 등록
	attackPattenManager->SetName("AttackPattenManager");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(attackPattenManager);                           // Scene에 GameObject 추가

	enemy = new GameObject();      // GameObject 객체 생성
	auto enemytmp = enemy->AddComponent<Enemy>(); // MonoBehaivor 등록
	enemytmp->m_State = enemy->AddComponent<StateController>();
	enemy->SetName("Enemytmp");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(enemy);          // Scene에 GameObject 추가

	player = new GameObject();      // GameObject 객체 생성
	auto playertmp = player->AddComponent<Player>(); // MonoBehaivor 등록
	playertmp->m_State = player->AddComponent<StateController>();
	player->SetName("Playertmp");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(player);            // Scene에 GameObject 추가

	bettleManager = new GameObject();             // GameObject 객체 생성
	auto bettletmp = bettleManager->AddComponent<BettleManager>(); // MonoBehaivor 등록
	bettletmp->m_Enemy = enemytmp;
	bettletmp->m_Player = playertmp;
	bettleManager->SetName("BettleManager");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(bettleManager);                  // Scene에 GameObject 추가
}

void PatternControlObject::OnStart() // 처음
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
	auto c = enemyGuideline->GetComponent<ChainDrawerComponent>();

	c->SetupNodes(m_nodes[4]->GetTransform().GetPosition(), n); // 스타트에서 하기

	for (int i = 0; i < 10; ++i) {
		readyQueue.push(new GameObject());
		auto queueBack = readyQueue.back()->AddComponent<ChainDrawerComponent>();
		queueBack->SetBitmap(L"../Workspace/HSK/Test/TestArrow_2.png");
		queueBack->SetFillBitmap(L"../Workspace/HSK/Test/TestArrow_1.png");
		queueBack->SetOrderInLayer(0);
		readyQueue.back()->SetName("EnemyGuideline." + i);
		queueBack->SetupNodes(m_nodes[4]->GetTransform().GetPosition(), n); // 스타트에서 하기
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(readyQueue.back());
	}
}

float n = 0.0f;

void PatternControlObject::OnUpdate() // 업데이트
{
	auto t = trail->GetComponent<TrailComponent>();
	t->isOutFromBox = PM.CheckOutOfBox({ Input::MouseX, Input::MouseY }); // 마우스 좌표 기반으로, 박스 밖으로 나갔는지 확인

	//auto en = enemyGuideline->GetComponent<ChainDrawerComponent>();

	if (t->isNewCached) { // 새로운 노드 발생하면				
		PM.CheckTrails(t->CheckingCachedTrails());
		const auto& vec = PM.GetPatternPathPositions(); // 여기에 담김!!! 1 3 2 4 이런거 <<<<< (연결지점)

		auto d = owner->GetComponent<PatternDrawerComponent>();
		d->SetLine(vec);
		if (!vec.empty()) // 노드가 그어졌다면, 바로 삭제해서 가시성 up
			t->Clear();

		auto bt = bettleManager->GetComponent<BettleManager>();
		bt->SetInputNode(PM.GetPattern());

		//		en->SliceRect(PM.GetPattern()); // 테스트용 // 가이드라인 패턴 입력해주면 그 시각적으로 그려지고 // 패턴

		for (int value : PM.GetPattern()) { std::cout << value << "-"; }
		std::cout << std::endl << std::endl;
	}

	auto apm = attackPattenManager->GetComponent<AttackPatternManager>();
	if (apm->isNewPattern) {

		if (!readyQueue.empty()) {
			enemyGuidelines.push_back(readyQueue.front());
			readyQueue.pop();
			auto ec = enemyGuidelines.back()->GetComponent<ChainDrawerComponent>();

			std::vector<int> v; 			
			float t;
			apm->GetEnemyPattern(v, t);

			v.erase(std::remove(v.begin(), v.end(), 0), v.end());

			ec->Start(v, t);
		}
	}

	// enemyGuidelines(벡터임) 내부 진행도가 1.0(종료) 된 것들을 다시 큐로 반환해줌
	for (auto it = enemyGuidelines.begin(); it != enemyGuidelines.end(); ) {
		GameObject* obj = *it;
		auto cdc = obj->GetComponent<ChainDrawerComponent>();

		if (!cdc) { ++it; continue; }

		if (cdc->progress > 1.0f) { // 진행 완료시
			cdc->progress = 0.0f;
			cdc->isPlay = false;
			readyQueue.push(obj);
			it = enemyGuidelines.erase(it);
		}
		else
			++it;
	}
}

void PatternControlObject::OnDestroy()
{


}


