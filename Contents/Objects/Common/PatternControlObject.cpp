#include "PatternControlObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Objects/Scenes/Stage/NodeObject.h"
#include "../Engine/Components/Rendering/PatternDrawerComponent.h"
#include "Objects/Common/MouseTrailObject.h"
#include "../Engine/Components/Rendering/ChainDrawerComponent.h"
#include "../Engine/Utils/GameTime.h"
#include "../Engine/Components/Rendering/AnimatedChainEffect.h" 

//성빈씨꺼
#include "Scripts/LogicManager/BettleManager.h"
#include "Scripts/LogicManager/AttackPatternManager.h" 
#include "Scripts/LiveObject/Enemy.h"
#include "Scripts/LiveObject/Player.h"
#include "Scripts/CsvData/CsvDataManager.h" // 싱글벙글
#include "Application/AppPaths.h"

void PatternControlObject::OnCreate()
{
	//===================================================================================================
	// 트레일 + 노드 오브젝트 생성
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
	// 가이드라인 A B 생성
	playerGuidelineA = new GameObject();
	playerGuidelineA->SetRenderLayer(EngineData::RenderLayer::None);
	auto cb = playerGuidelineA->AddComponent<ChainDrawerComponent>(); // 빨강(상단) 초록(중단) 하단(파랑)
	cb->SetBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_guide_line 3.png");
	cb->SetTypeBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_guide_line 1.png", Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_guide_line 2.png");
	cb->SetOrderInLayer(0);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(playerGuidelineA);

	playerGuidelineB = new GameObject();
	playerGuidelineB->SetRenderLayer(EngineData::RenderLayer::None);
	auto cc = playerGuidelineB->AddComponent<ChainDrawerComponent>();
	cc->SetBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_guide_line 3.png");
	cc->SetTypeBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_guide_line 1.png", Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource/player_guide_line 2.png");
	cc->SetOrderInLayer(0);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(playerGuidelineB);

	//===================================================================================================
	// 데?이터 읽어오는거

	char buffer[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, buffer);
	std::string path = buffer;

	PlayerAtkPetternData* tmp1 = nullptr;
	CsvDataManager::GetInstance().SetCSV<EnemyData>(path + "\\..\\Resource\\DataTable\\적 데이터 테이블.csv"); // 데이터 파일 읽어오기

	EnemyAtkPattenData* tmp2 = nullptr;
	CsvDataManager::GetInstance().SetCSV<EnemyAtkPattenData>(path + "\\..\\Resource\\DataTable\\적 공격 패턴 테이블.csv"); // 데이터 파일 읽어오기

	AllNodePattenClass* tmp3 = nullptr;
	CsvDataManager::GetInstance().SetCSV<AllNodePattenClass>(path + "\\..\\Resource\\DataTable\\노드 전체 패턴 테이블.csv"); // 데이터 파일 읽어오기

	PlayerAtkPetternData* tmp4 = nullptr;
	CsvDataManager::GetInstance().SetCSV<PlayerAtkPetternData>(path + "\\..\\Resource\\DataTable\\플레이어 공격 패턴 테이블.csv"); // 데이터 파일 읽어오기

	PlayerData* tmp5 = nullptr;
	CsvDataManager::GetInstance().SetCSV<PlayerData>(path + "\\..\\Resource\\DataTable\\플레이어 데이터 테이블.csv"); // 데이터 파일 읽어오기

	//===================================================================================================
	// 어택 패턴 매니저 생성
	attackPattenManager = new GameObject();                    // GameObject 객체 생성
	auto apm = attackPattenManager->AddComponent<AttackPatternManager>(); // MonoBehaivor 등록
	attackPattenManager->SetName("AttackPattenManager");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(attackPattenManager);                           // Scene에 GameObject 추가

	lid_OnPatternCancel = apm->OnPatternCancel.Add([this](const std::string& id) {
		ChainDrawerComponent* target = nullptr;
		for (auto* go : enemyGuidelines) {
			if (auto* cdc = go->GetComponent<ChainDrawerComponent>()) {
				if (cdc->patternID == id) { target = cdc; break; }
			}
		}
		if (target) target->CancelByID(id);
		});

	// ===================

	float n = 200.0f; // 노드간의 간격
	float r = 45.0f; // 반경
	for (int i = 0; i < 9; ++i) {
		int col = i % 3 - 1; // -1 0 1
		int row = i / 3 - 1; // -1 0 1

		float x = 960.0f + col * n;
		float y = 540.0f + row * n;

		m_nodes[i]->GetTransform().SetPosition(x, y);
		m_nodes[i]->GetComponent<NodeObject>()->SetRadius(r);
		nodePositions.push_back({ x, y });
	}

	PM.SetNodes(m_nodes, r);

	// effect 9
	for (int i = 0; i < 9; i++)
	{
		GameObject* obj = new GameObject;
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		auto comp = obj->AddComponent<EffectInstance>();
		comp->SetAnimePosition(nodePositions);
		effs.push_back(comp);
	}

	//===================================================================================================
	// 적 + 플레이어 + 배틀매니저 생성
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
	bettletmp->onParry.Add([this](int nodeIndex)
		{
			this->effs[nodeIndex - 1]->DoParry(nodeIndex - 1); // 1. 여기서 위치 초기화가 제대로 안된다
		});

	bettletmp->onGuard.Add([this](int nodeIndex) {
		this->effs[nodeIndex - 1]->DoGuard(nodeIndex - 1); // 1. 여기서 위치 초기화가 제대로 안된다
		});

	bettletmp->m_Enemy = enemytmp;
	bettletmp->m_Player = playertmp;
	bettleManager->SetName("BettleManager");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(bettleManager);                  // Scene에 GameObject 추가


	GameObject* csm = new GameObject();
	csManager = csm->AddComponent<ChargedSlashManager>();
	csManager->SetUpNodePos(nodePositions);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(csm, "ChargedSlashManager"); // 이 오브젝트도 망망대해를 떠돌겠지
}

//===================================================================================================
// START ////////////////////////////////////////////////////////////////////////////////////////////
//===================================================================================================

void PatternControlObject::OnStart() // 처음
{

	csManager->Start(1);
	owner->SetRenderLayer(EngineData::RenderLayer::UI);
	auto d = owner->AddComponent<PatternDrawerComponent>();
	d->SetOrderInLayer(80);
	d->SetBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\test5.png");

	//===================================================================================================

	float n = 200.0f; // 노드간의 간격
	float r = 45.0f; // 반경

	effInstance = owner->AddComponent<EffectInstance>();
	effInstance->SetAnimePosition(nodePositions);

	//===================================================================================================

	for (int i = 0; i < 10; ++i) {
		readyQueueForEnemyGuide.push(new GameObject());
		auto queueBack = readyQueueForEnemyGuide.back()->AddComponent<ChainDrawerComponent>();
		queueBack->SetBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\TestArrow_2.png");
		queueBack->SetFillBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\TestArrow_1.png");
		queueBack->SetOrderInLayer(0);
		readyQueueForEnemyGuide.back()->SetName("EnemyGuideline." + std::to_string(i));
		queueBack->SetupNodes(m_nodes[4]->GetTransform().GetPosition(), n); // 스타트에서 하기

		queueBack->OnInterrupted.Add([this, go = readyQueueForEnemyGuide.back()](const std::string& id) {
			for (auto it = enemyGuidelines.begin(); it != enemyGuidelines.end(); ++it) {
				if (*it == go) { enemyGuidelines.erase(it); break; }
			}
			readyQueueForEnemyGuide.push(go);
			});

		queueBack->OnFinished.Add([this, go = readyQueueForEnemyGuide.back()](const std::string&) {
			for (auto it = enemyGuidelines.begin(); it != enemyGuidelines.end(); ++it) {
				if (*it == go) { enemyGuidelines.erase(it); break; }
			}
			readyQueueForEnemyGuide.push(go);
			});

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(readyQueueForEnemyGuide.back());
	}

	//===================================================================================================

	for (int i = 0; i < 10; ++i) {
		readyQueueForAttackLine.push(new GameObject());
		readyQueueForAttackLine.back()->SetRenderLayer(EngineData::RenderLayer::UI);
		auto queueBack = readyQueueForAttackLine.back()->AddComponent<AnimatedChainEffect>();
		queueBack->SetOrderInLayer(130);

		readyQueueForAttackLine.back()->SetName("AttackEffectLine." + std::to_string(i));
		queueBack->SetupNodes(m_nodes[4]->GetTransform().GetPosition(), n);

		queueBack->OnFinished.Add([this, go = readyQueueForAttackLine.back()]() {
			for (auto it = attackLineEffects.begin(); it != attackLineEffects.end(); ++it) {
				if (*it == go) { attackLineEffects.erase(it); break; } // 백터에서 삭제함
			}
			readyQueueForAttackLine.push(go);
			});

		queueBack->OnNodeLightUp.Add([this](int index) { // 1 ~ 9 >> -1 0 ~ 8
			effInstance->CallAnime(index - 1); // 0~8 
			});

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(readyQueueForAttackLine.back());
	}

	//===================================================================================================

	auto PCA = playerGuidelineA->GetComponent<ChainDrawerComponent>();
	PCA->SetupNodes(m_nodes[4]->GetTransform().GetPosition(), n);
	auto PCB = playerGuidelineB->GetComponent<ChainDrawerComponent>();
	PCB->SetupNodes(m_nodes[4]->GetTransform().GetPosition(), n);
}

//===================================================================================================
// UPDATE ///////////////////////////////////////////////////////////////////////////////////////////
//===================================================================================================

void PatternControlObject::OnUpdate() // 업데이트
{
	auto t = trail->GetComponent<TrailComponent>();
	t->isOutFromBox = PM.CheckOutOfBox({ Input::MouseX, Input::MouseY }); // 마우스 좌표 기반으로, 박스 밖으로 나갔는지 확인

	//===================================================================================================
	// [1] 입력 발생하면

	if (t->isNewCached) { // 새로운 노드 발생하면				


		PM.CheckTrails(t->CheckingCachedTrails());
		const auto& vec = PM.GetPatternPathPositions(); // 여기에 담김!!! 1 3 2 4 이런거 <<<<< (연결지점)

		auto d = owner->GetComponent<PatternDrawerComponent>();
		d->SetLine(vec);
		if (!vec.empty()) // 노드가 그어졌다면, 바로 삭제해서 가시성 up
			t->Clear();

		auto bt = bettleManager->GetComponent<BettleManager>();
		bt->SetInputNode(PM.GetPattern());

		for (int value : PM.GetPattern()) { std::cout << value << "-"; }
		std::cout << std::endl << std::endl;
	}

	//===================================================================================================
	// [2] 가이드라인 갱신되면

	std::vector<int> pca;
	std::vector<int> pcb;

	auto apm = attackPattenManager->GetComponent<AttackPatternManager>();
	apm->GetPlayerPatten(pca, pcb);

	if (pca != cachedVecA) {
		cachedVecA = pca;
		pca.erase(std::remove(pca.begin(), pca.end(), 0), pca.end());
		std::reverse(pca.begin(), pca.end());
		auto PCA = playerGuidelineA->GetComponent<ChainDrawerComponent>();
		PCA->StartByType(pca);
	}

	if (pcb != cachedVecB) {
		cachedVecB = pcb;
		pcb.erase(std::remove(pcb.begin(), pcb.end(), 0), pcb.end());
		std::reverse(pcb.begin(), pcb.end());
		auto PCB = playerGuidelineB->GetComponent<ChainDrawerComponent>();
		PCB->StartByType(pcb);
	}

	//===================================================================================================
	// [3] 적패턴 갱신되면
	if (apm->isNewPattern) {
		std::vector<int> v;
		float t;
		std::string ID;

		apm->GetEnemyPattern(v, t, ID);
		v.erase(std::remove(v.begin(), v.end(), 0), v.end());

		if (!readyQueueForEnemyGuide.empty()) {
			enemyGuidelines.push_back(readyQueueForEnemyGuide.front());
			readyQueueForEnemyGuide.pop();
			auto ec = enemyGuidelines.back()->GetComponent<ChainDrawerComponent>();

			ec->Start(v, t, ID);
		}
	}

	//===================================================================================================
	// [4] 공격이 성공한 경우 - 이펙트 출력용

	if (apm->isAttack) {
		if (!readyQueueForAttackLine.empty()) {
			attackLineEffects.push_back(readyQueueForAttackLine.front());
			readyQueueForAttackLine.pop();
			auto ac = attackLineEffects.back()->GetComponent<AnimatedChainEffect>();
			ac->PlayOnce(apm->CheckIsAttck());
		}
	}

	auto bt = bettleManager->GetComponent<BettleManager>();





}

//===================================================================================================

void PatternControlObject::OnDestroy()
{
	if (auto* apm = attackPattenManager->GetComponent<AttackPatternManager>()) {
		if (lid_OnPatternCancel) {
			apm->OnPatternCancel.RemoveByID(lid_OnPatternCancel);
			lid_OnPatternCancel = 0;
		}
	}
}
