#include "PatternControlObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Objects/Scenes/Stage/NodeObject.h"
#include "../Engine/Components/Rendering/PatternDrawerComponent.h"
#include "Objects/Common/MouseTrailObject.h"
#include "../Engine/Components/Rendering/ChainDrawerComponent.h"
#include "../Engine/Utils/GameTime.h"
#include "../Engine/Components/Rendering/AnimatedChainEffect.h" 
#include "../Engine/Math/GameRandom.h"
#include "Objects/Scenes/Stage/StageBGI.h"

//성빈씨꺼
#include "Scripts/LogicManager/BettleManager.h"
#include "Scripts/LogicManager/AttackPatternManager.h" 
#include "Scripts/LiveObject/Enemy.h"
#include "Scripts/LiveObject/Player.h"
#include "Scripts/CsvData/CsvDataManager.h" // 싱글벙글
#include "Application/AppPaths.h"

#include "Scripts/GameManager.h"

void PatternControlObject::OnCreate()
{
	//===================================================================================================
	// 1. 트레일 + 노드 오브젝트 생성
	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(trail, "MouseTrail");

	for (int i = 0; i < 9; ++i)
	{
		m_nodes[i] = new GameObject();
		auto nodeComponent = m_nodes[i]->AddComponent<NodeObject>();
		std::string name = "Node." + std::to_string(i + 1);
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(m_nodes[i], name);
	}

	//===================================================================================================
	// 2. 가이드라인 A B 생성
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
	// 3. 데이터 읽어오는거

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
	// 4. 어택 패턴 매니저 생성
	attackPattenManager = new GameObject();
	auto apm = attackPattenManager->AddComponent<AttackPatternManager>();
	attackPattenManager->SetName("AttackPattenManager");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(attackPattenManager);

	// OnPatterCancel 이벤트 등록
	lid_OnPatternCancel = apm->OnPatternCancel.Add([this](const std::string& id)
		{
			ChainDrawerComponent* target = nullptr;
			for (auto* go : enemyGuidelines)
			{
				if (auto* cdc = go->GetComponent<ChainDrawerComponent>()) // 매개변수의 id를 가가진 Chain Drawer 컴포넌트 찾기
				{
					if (cdc->patternID == id) { target = cdc; break; }
				}
			}
			if (target) // 찾으면 취소 함수 호출
			{
				target->CancelByID(id);
			}
		});

	//===================================================================================================
	// 5. 노드 오브젝트 추가

	float n = 200.0f; // 노드간의 간격
	float r = 45.0f; // 반경
	for (int i = 0; i < 9; ++i)
	{
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
		effectInstances.push_back(comp);
	}

	//===================================================================================================
	// 6. 적 + 플레이어 + 배틀매니저 생성

	// 적 오브젝트 생성 (Enemy.h)
	enemy = new GameObject();
	auto enemytmp = enemy->AddComponent<Enemy>();
	enemytmp->m_State = enemy->AddComponent<StateController>();
	enemy->SetName("Enemytmp");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(enemy);

	// 플레이어 오브젝트 생성 (Player.h)
	player = new GameObject();
	auto playertmp = player->AddComponent<Player>();
	playertmp->m_State = player->AddComponent<StateController>();
	player->SetName("Playertmp");

	// player.onTimeOut 이벤트 연결
	playertmp->onTimeOut.Add([this]()
		{
			chargedSlashManager->Cancel(); // 플레이어 쪽에서 그로기 타이머를 관리하고 있어서, 캔슬연결함	
			isSkipped = false;

			trail->GetComponent<TrailComponent>()->Clear(); // 이거 해줘야함
			for (int i = 0; i < m_nodes.size(); ++i) {
				m_nodes[i]->GetComponent<BitmapRenderer>()->SetActive(true);
			}

		});

	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(player);

	// 7. BattleManager 추가
	bettleManager = new GameObject();
	auto bettletmp = bettleManager->AddComponent<BettleManager>();

	bettletmp->onStartBlow.Add([this]() { // 비네트 ON
		auto bgi = owner->GetQuery()->FindByName("StageBGI1");
		if (bgi) { bgi->GetComponent<StageBGI>()->Start(); } 
		});

	// OnParry 이벤트 추가
	bettletmp->onParry.Add([this](int nodeIndex)
		{
			this->effectInstances[nodeIndex - 1]->DoParry(nodeIndex - 1);
		});

	// OnGuard 이벤트 추가
	bettletmp->onGuard.Add([this](int nodeIndex)
		{
			this->effectInstances[nodeIndex - 1]->DoGuard(nodeIndex - 1);
		});

	// OnFinalBlow 이벤트 추가
	bettletmp->onFinalBlow.Add([this]()
		{ // 한붓그리기 완료되는 시점에, 랜덤으로 Start 호출됨
			auto bgi = owner->GetQuery()->FindByName("StageBGI1");
			if (bgi) { bgi->GetComponent<StageBGI>()->End(); }
			
			//auto bt = bettleManager->GetComponent<BettleManager>();
			//bt->usedStartBlow = false;

			int n = GameRandom::RandomRange(0, 4); // 0 ~ 3
		
			switch (n)
			{
			case 0: n = 1; break;
			case 1: n = 3; break;
			case 2: n = 7; break;
			case 3: n = 9; break;
			default: break;
			}

			chargedSlashManager->Start(n);
			isSkipped = true;

			for (int i = 0; i < m_nodes.size(); ++i) {
				m_nodes[i]->GetComponent<BitmapRenderer>()->SetActive(false);
			}

		});

	// OntimeOut 이벤트 추가 - slash가 시간 경과시 캔슬됨
	bettletmp->onTimeout.Add([this]()
		{		
			auto bgi = owner->GetQuery()->FindByName("StageBGI1");
			if (bgi) { bgi->GetComponent<StageBGI>()->End(); }

			//auto bt = bettleManager->GetComponent<BettleManager>();
			//bt->usedStartBlow = false;

			chargedSlashManager->Cancel();
			isSkipped = false;
			trail->GetComponent<TrailComponent>()->Clear(); // 이거 해줘야함

			for (int i = 0; i < m_nodes.size(); ++i) {
				m_nodes[i]->GetComponent<BitmapRenderer>()->SetActive(true);
			}
		});

	// Manager의 Player와 Enemy 참조
	bettletmp->m_Enemy = enemytmp;
	bettletmp->m_Player = playertmp;
	bettleManager->SetName("BettleManager");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(bettleManager);

	// ChargedSlashManager 추가
	GameObject* csm = new GameObject();
	chargedSlashManager = csm->AddComponent<ChargedSlashManager>();
	chargedSlashManager->SetUpNodePos(nodePositions);

	// OnFinisherSuccess 이벤트 추가
	chargedSlashManager->onFinisherSuccess.Add([this]()
		{
			auto btt = bettleManager->GetComponent<BettleManager>();
			btt->FinalAttackToEnemy();

			auto emm = enemy->GetComponent<Enemy>();
			emm->RestoreGroggy();

			auto pll = player->GetComponent<Player>();
			pll->RestoreGroggy();
		});

	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(csm, "ChargedSlashManager");
}

//===================================================================================================
// START ////////////////////////////////////////////////////////////////////////////////////////////
//===================================================================================================

void PatternControlObject::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);
	auto patternDrawerComp = owner->AddComponent<PatternDrawerComponent>();
	patternDrawerComp->SetOrderInLayer(80);
	patternDrawerComp->SetBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\test5.png");

	//===================================================================================================
	// PatternControlObject에 effInstance 추가

	float n = 200.0f;	// 노드간의 간격 -> 바로 위에서 보기 위해 일부로 OnCreate와 OnStart에 지역변수 중복 선언
	float r = 45.0f;	// 반경

	effInstance = owner->AddComponent<EffectInstance>();
	effInstance->SetAnimePosition(nodePositions);

	//===================================================================================================

	// 적 공격 패링 가이드 세팅 - 빨강색 패링 이미지 
	for (int i = 0; i < 10; ++i)
	{
		readyQueueForEnemyGuide.push(new GameObject());

		auto queueBack = readyQueueForEnemyGuide.back()->AddComponent<ChainDrawerComponent>();
		queueBack->SetBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\TestArrow_2.png");
		queueBack->SetFillBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\TestArrow_1.png");
		queueBack->SetOrderInLayer(0);

		readyQueueForEnemyGuide.back()->SetName("EnemyGuideline." + std::to_string(i));
		queueBack->SetupNodes(m_nodes[4]->GetTransform().GetPosition(), n); // 스타트에서 하기

		// OnInterrupted 이벤트 추가 ( 중단 시 )
		queueBack->OnInterrupted.Add([this, go = readyQueueForEnemyGuide.back()]()
			{
				for (auto it = enemyGuidelines.begin(); it != enemyGuidelines.end(); ++it)
				{
					if (*it == go) // 매개변수 go를 가진 가이드 라인을 찾으면 제거
					{
						enemyGuidelines.erase(it);
						break;
					}
				}

				readyQueueForEnemyGuide.push(go);
			});

		// OnFinished 이벤트 추가 - 연격 패턴이 끝나고 마우스가 홀드가 된 상태
		queueBack->OnFinished.Add([this, go = readyQueueForEnemyGuide.back()]()
			{
				for (auto it = enemyGuidelines.begin(); it != enemyGuidelines.end(); ++it)
				{
					if (*it == go)
					{
						enemyGuidelines.erase(it);
						break;
					}
				}

				readyQueueForEnemyGuide.push(go);
			});

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(readyQueueForEnemyGuide.back());
	}

	//===================================================================================================

	// 공격 가이드 세팅 - 파랑 빨강 화살표 이미지
	for (int i = 0; i < 10; ++i)
	{
		readyQueueForAttackLine.push(new GameObject());
		readyQueueForAttackLine.back()->SetRenderLayer(EngineData::RenderLayer::UI);
		auto queueBack = readyQueueForAttackLine.back()->AddComponent<AnimatedChainEffect>();
		queueBack->SetOrderInLayer(130);

		readyQueueForAttackLine.back()->SetName("AttackEffectLine." + std::to_string(i));
		queueBack->SetupNodes(m_nodes[4]->GetTransform().GetPosition(), n);

		// OnFinished 이벤트 추가
		queueBack->OnFinished.Add([this, go = readyQueueForAttackLine.back()]()
			{
				for (auto it = attackLineEffects.begin(); it != attackLineEffects.end(); ++it)
				{
					if (*it == go)
					{
						attackLineEffects.erase(it);
						break;
					}
				}
				readyQueueForAttackLine.push(go);
			});

		// OnNodeLightUp 추가 - 아마 라인 긋고 흰색 이펙트로 추정됨
		queueBack->OnNodeLightUp.Add([this](int index)
			{ // 1 ~ 9 >> -1 0 ~ 8
				effInstance->CallAnime(index - 1); // 0~8 
			});
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(readyQueueForAttackLine.back());
	}

	//===================================================================================================
	// 공격 가이드 초기 세팅 - 아마 테스트 용으로 추정

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
	// 게임 상태가 Pause면 Update 중단
	if (Singleton<GameManager>::GetInstance().GetGameState() == GameState::Pause)
	{
		return;
	}

	auto t = trail->GetComponent<TrailComponent>();
	t->isOutFromBox = PM.CheckOutOfBox({ Input::MouseX, Input::MouseY }); // 마우스 좌표 기반으로, 박스 밖으로 나갔는지 확인

	//===================================================================================================
	// [1] 입력 발생하면

	if (t->isNewCached && !isSkipped) // 새로운 노드 발생하면	+ 스킵 상태가 아니라며
	{
		PM.CheckTrails(t->CheckingCachedTrails());		// trail 찍힌 위치들을 확인하고 저장함
		const auto& vec = PM.GetPatternPathPositions(); // 여기에 담김!!! 1 3 2 4 이런거 <<<<< (연결지점)

		auto d = owner->GetComponent<PatternDrawerComponent>();
		d->SetLine(vec);

		if (!vec.empty()) // 노드가 그어졌다면, 바로 삭제해서 가시성 up
		{
			t->Clear();
		}

		auto bt = bettleManager->GetComponent<BettleManager>();
		bt->SetInputNode(PM.GetPattern());

		for (int value : PM.GetPattern()) { std::cout << value << "-"; } // Debug
		std::cout << std::endl << std::endl;
	}

	//===================================================================================================
	// [2] 가이드라인 갱신되면

	std::vector<int> pca;
	std::vector<int> pcb;

	auto apm = attackPattenManager->GetComponent<AttackPatternManager>();
	apm->GetPlayerPatten(pca, pcb);

	if (pca != cachedVecA)
	{
		cachedVecA = pca;
		pca.erase(std::remove(pca.begin(), pca.end(), 0), pca.end());
		std::reverse(pca.begin(), pca.end());
		auto PCA = playerGuidelineA->GetComponent<ChainDrawerComponent>();
		PCA->StartByType(pca);
	}

	if (pcb != cachedVecB)
	{
		cachedVecB = pcb;
		pcb.erase(std::remove(pcb.begin(), pcb.end(), 0), pcb.end());
		std::reverse(pcb.begin(), pcb.end());
		auto PCB = playerGuidelineB->GetComponent<ChainDrawerComponent>();
		PCB->StartByType(pcb);
	}

	//===================================================================================================
	// [3] 적패턴 갱신되면

	if (apm->isNewPattern)
	{
		std::vector<int> enemyPatterns;
		float time;
		std::string ID;

		apm->GetEnemyPattern(enemyPatterns, time, ID);
		enemyPatterns.erase(std::remove(enemyPatterns.begin(), enemyPatterns.end(), 0), enemyPatterns.end());

		if (!readyQueueForEnemyGuide.empty())
		{
			enemyGuidelines.push_back(readyQueueForEnemyGuide.front());
			readyQueueForEnemyGuide.pop();
			auto ec = enemyGuidelines.back()->GetComponent<ChainDrawerComponent>();

			ec->Start(enemyPatterns, time, ID); // ChainDrawer 시작
		}
	}

	//===================================================================================================
	// [4] 공격이 성공한 경우 - 이펙트 출력용

	if (apm->isAttack)
	{
		if (!readyQueueForAttackLine.empty())
		{
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
	if (auto* apm = attackPattenManager->GetComponent<AttackPatternManager>())
	{
		if (lid_OnPatternCancel)
		{
			apm->OnPatternCancel.RemoveByID(lid_OnPatternCancel);
			lid_OnPatternCancel = 0;
		}
	}
}

Enemy* PatternControlObject::GetEnemy()
{
	return enemy->GetComponent<Enemy>();
}
