#include "Enemy.h"
#include <random>
#include <cmath>

#include "Components/Base/GameObject.h"
#include "../CsvData/DataClass/EnemyData.h"
#include "../CsvData/CsvDataManager.h"
#include "../Component/StateController.h"
#include "Utils/GameTime.h"

#include "../Engine/Scene/SceneManager.h" // 테스트 씬 전환용 8.09 추가

#include "Application/AppPaths.h"
#include "Scripts/GameManager.h"
#include "Objects/Scenes/Stage/StageResult/StageResult.h"


// 각 값은 해당 함수가 출력 중일때, 각 플레그 변화
//														     
//                    IonStartI 다음 루프ㅣ 공격 노드추가ㅣ			    I
//  isPattenCooldoown I   F   I    T      I     F		  I      F      I  
//


void Enemy::OnStart() 
{
	m_State = owner->GetComponent<StateController>();
	m_PattenManager = owner->GetQuery()->FindByName("AttackPattenManager")->GetComponent<AttackPatternManager>();

	SetStatData(Enemy_ID);				// 객체 데이터 불러오기
	OnCreateState();					// 상태들 구성
	m_State->SetState("Enemy_Idle");	// 초기 상태로 초기화

	SelectPattern(); //  패턴 세팅
	SetCoolTime();	
	SetBitmap();

	isPatternLive = true;
	groggyTime = 0.0f;

	enemy_Attack->SetActive(false);
	enemy_Damaged->SetActive(false);
	enemy_Guard->SetActive(false);

	Hiteff = owner->AddComponent<HitEffect>();
	GuardEff = owner->AddComponent<EnemyAttackEffect>();

}

// 업데이트에서 시간 받기???? -> 필요없음, 수정하기!!!
void Enemy::OnUpdate() 
{
	// Game 상태가 Pause면 모든 Update 무시
	if (Singleton<GameManager>::GetInstance().GetGameState() == GameState::Pause)
	{
		return;
	}

	// 적이 죽지 않고 그로기(Groggy) 상태 일때
	if (nowStateName != "Enemy_Dead" && (!isGroggy))
	{
		CalSpiritTime();		// 1초마다 기세게이지 증가
		AddPattenLoop();		// 
		
	}
	StateAct();            //  
	DiffState();            // 이전 상태와 현재 상태를 비교
	// PrintConsole();

	if (nowStateName == "Enemy_Dead") // 적 사망 시 -> 씬 이동
	{
		switch (nameIndex)
		{
		case 0:
			Singleton<GameManager>::GetInstance().SetStageClear(1);
			break;
		case 1:
			Singleton<GameManager>::GetInstance().SetStageClear(2);
			break;
		case 2:
			Singleton<GameManager>::GetInstance().SetStageClear(3);
			break;
		}
		ChecKChnageScene();
	}

	//SetNameDiff("Stage1", "easy");
}


// onChangePatten에 TransitionTime 변경하기!!!

//밖에서 미리 값을 입력해서 ID를 입력할 수 있게 함
void Enemy::SetNameDiff(std::string Stage, std::string difficulty) {
	int indexID = 0;
	int diffindex = 0;
	if (Stage == "Stage1") { nameIndex = 0; }
	else if (Stage == "Stage2") { nameIndex = 1; }
	else if (Stage == "Stage3") { nameIndex = 2; }
	else { nameIndex = 100; }

	if (difficulty == "easy") { diffindex = 1; }
	else if (difficulty == "normal") { diffindex = 2; }
	else if (difficulty == "hard") { diffindex = 3; }
	else { diffindex = 100; }

	indexID = nameIndex * 3 + diffindex;
	if (nameIndex == 100 || diffindex == 100) return;

	Enemy_ID = "EI_00" + std::to_string(indexID);
}



//이후 StateManager에 추가하는거 만들기
void Enemy::SetState(std::string setStateName) {
	if (!(nowStateName == "Enemy_Dead" || nowStateName == "Enemy_Groggy")) {
		m_State->SetState(setStateName);
	}
}

void Enemy::OnCreateState() 
{
	m_State->CreateState("Enemy_Idle");							// 평소 상태 - Default State  

	m_State->CreateState("Enemy_AttackSuccess");				// 공격 성공
	m_State->SetNextState("Enemy_AttackSuccess", "Enemy_Idle");	// Enemy_AttackSuccess -> Enemy_Idle
	m_State->SetTransitionTime("Enemy_AttackSuccess", 1.0f);	// 1.0f 뒤 변경

	m_State->CreateState("Enemy_AttackFail");					// 공격 실패 
	m_State->SetNextState("Enemy_AttackFail", "Enemy_Idle");	// Enemy_AttackFail -> Enemy_Idle
	m_State->SetTransitionTime("Enemy_AttackFail", 1.0f);		// 1.0f 뒤 변경

	m_State->CreateState("Enemy_Hit");							// 패턴 파회 X, 맞음
	m_State->SetNextState("Enemy_Hit", "Enemy_Idle");			// Enemy_Hit -> Enemy_Idle
	m_State->SetTransitionTime("Enemy_Hit", 1.0f);				// 1.0f 뒤 변경

	m_State->CreateState("Enemy_Defence");						// 패턴 파회 X, 막음
	m_State->SetNextState("Enemy_Defence", "Enemy_Idle");		// Enemy_Defence -> Enemy_Idle
	m_State->SetTransitionTime("Enemy_Defence", 1.0f);			// 1.0f 뒤 변경

	m_State->CreateState("Enemy_Groggy");						// 패턴 파회 X, 막음
	m_State->SetNextState("Enemy_Groggy", "Enemy_Idle");		// Enemy_Groggy -> Enemy_Idle
	m_State->SetTransitionTime("Enemy_Groggy", 2.0f);			// 2.0f 뒤 변경

	m_State->CreateState("Enemy_Dead");							// 죽음
}

// 플레이어 데이터에는 기세가 없음으로 적을 생성 후, 기세를 매개변수에 넣어주기!!
// 패턴을 세팅하는 것은 처음?

// 매개변수를 통해 데이터의 키값을 받아서 데이터를 찾고 데이터의 값을 적에게 전부 인가
void Enemy::SetStatData(std::string tmp) 
{
	nowEnemyData = CsvDataManager::GetInstance().getDataImpl(nowEnemyData, tmp);

	Object_ID = nowEnemyData->enemyID;					   // ID
	Object_Name = nowEnemyData->enemyName;				   // 이름
	Object_Hp = nowEnemyData->enemyHealth;		           // 체력
	Object_TotalHp = Object_Hp;							  // 전체 체력
	Object_Attack = nowEnemyData->enemyDamage;			   // 공격력
	Object_SpiritAttack = nowEnemyData->enemySpiritdamage; // 기세 공격력
	Object_DefenseRate = nowEnemyData->enemyGuardRate;	   // 방어율
	Object_SpiritAmount = nowEnemyData->enemySpiritamount; // 기세
	Object_NowSpiritAmount = Object_SpiritAmount / 2.0f;   // 현재 기세 설정
	Difficulty = nowEnemyData->enemyDifficulty;			   // 난이도 -> 아마 필요없을듯?

	PattenID = nowEnemyData->enemyPattern;				   // 적이 가지고 있는 벡터

	TotalPatternID = CsvDataManager::GetInstance().GetIDData(nowEnemyPattenData);  // 적 공격 전체의 데이터

	// 적이 가지고 있는 공격과 적 패턴 전체의 벡터를 매핑
	for (int i = 0; i < nowEnemyData->enemyPattern.size(); i++) 
	{
		int index = 0;
		auto it = std::find(TotalPatternID.begin(), TotalPatternID.end(), nowEnemyData->enemyPattern[i]); // 
		if (it != TotalPatternID.end()) 
		{
			index = std::distance(TotalPatternID.begin(), it); // 인덱스 계산
		}

		PattenMap[nowEnemyData->enemyPattern[i]] = index;      // 적의 패턴과 적의 전체 패턴을 매핑
	}

	Object_CoolTime = nowEnemyData->enemyCooldown;         // 적의 쿨타임 가져오기;
	Object_nowCoolTime = nowEnemyData->enemyCooldown;	   // 현재 적의 쿨타임
	Object_PlayingAttackTime = 0.0f;					   // 패턴의 입력 대기 시간
	Object_nowPlayingAttackTime = 0.0f;					   // 현재 패턴의 입력 대기 시간

	std::wstring enemy_CommonPath = L"\\..\\Resource\\ContentsResource\\";	// 적의 공통 이미지 경로

	// 적의 이미지 이름 받기
	enemy_IdlePath = enemy_CommonPath + nowEnemyData->enemySprite[0] + L"_fin.png";        
	enemy_AttackPath = enemy_CommonPath + nowEnemyData->enemySprite[1] + L"_fin.png";
	enemy_GuardPath = enemy_CommonPath + nowEnemyData->enemySprite[2] + L"_fin.png";
	enemy_DamagedPath = enemy_CommonPath + nowEnemyData->enemySprite[3] + L"_fin.png";
}


void Enemy::SetBitmap() 
{

	enemy_Idle = owner->AddComponent<BitmapRenderer>();
	enemy_Idle->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + enemy_IdlePath);

	enemy_Attack = owner->AddComponent<BitmapRenderer>();
	enemy_Attack->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + enemy_AttackPath);


	enemy_Damaged = owner->AddComponent<BitmapRenderer>();
	enemy_Damaged->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + enemy_DamagedPath);

	enemy_Guard = owner->AddComponent<BitmapRenderer>();
	enemy_Guard->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + enemy_GuardPath);

	D2D1_SIZE_F size = enemy_Idle->GetResource()->GetBitmap()->GetSize(); // 크기 같음으로 그냥 해도 될듯?
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);
	owner->GetTransform().SetScale(1.0f, 1.0f); //  크기 맞추기
	owner->GetTransform().SetPosition(580.0f, 150.0f);
}

// 플래그를 정하는 함수
void Enemy::AddPattenLoop() 
{
	// isPatternLive : T  -> 쿨타임을 계산
	// isPatternLive : F  -> 계산 X
	if (isPatternLive) // 패턴이 아직 살아있으면
	{
		// 패턴의 입력대기시간 카운트
		Object_nowCoolTime -= GameTime::GetInstance().GetDeltaTime();

		if (Object_nowCoolTime <= 0.0f) 
		{
			isPatternLive = false; // 패턴 지속 시간이 끝나면 false
		}
	}
	else // 현재 패턴의 지속 시간이 끝났으면
	{
		SelectPattern(); // 패턴 정하기!!
		SetCoolTime();	// 적일때는 수정하기!!
		SetNowPattern(); // 공격대기시간 + 데이터 주기!!
		isPatternLive = true;
	}
}

void Enemy::RestoreGroggy()
{
	if (!isGroggy) return;          // 그로기 아니면 무시
	if (restoredThisCycle) return;  // 이번 사이클에서 이미 복구했으면 무시
	restoredThisCycle = true;

	// === 즉시 복구 처리 (재진입 방지) ===
	isGroggy = false;               // 바로 그로기 해제
	ResetSpiritAmount();           

	// 부가 플래그/타이머 정리
	groggyTime = 0.0f;
	OtherGroggyTime = 0.0f;
	IsOtherGroggy = false;

	// 베틀매니저 공통 회복 루틴용 플래그(멱등)
	isRestore = true;

	ResetEnemy();
}

// 배틀 매니저에서 사용될 함수
void Enemy::SelectPattern() //각 객체가 사용할 패턴을 고름
{   
	if (nowEnemyPattenData != nullptr) 
	{
		preEnemyPattenData = nowEnemyPattenData;
		preRandomValue = nowRandomValue;
	}
	if (nowEnemyPattenData != nullptr && preEnemyPattenData->eComboCoolDown != 0) 
	{
		++patternCount;
		SetAttackPattenData(TotalPatternID[PattenMap[PattenID[nowRandomValue]] + patternCount]);
	}

	else 
	{
		patternCount = 0;
		if (enemyAttackPatternFix.substr(0, 2) != "EP") 
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, PattenID.size() - 1);
			nowRandomValue = dist(gen);
			SetAttackPattenData(PattenID[nowRandomValue]);


			// 이전 패턴과 안겹치게 할때 사용하기!
			//if (preEnemyPattenData != nowEnemyPattenData)
			//	break;
			//}
		}
		else 
		{
			SetAttackPattenData(enemyAttackPatternFix);
		}
	}
}

//패턴 ID에 맞는 데이터를 포인터로 가리킴
void Enemy::SetAttackPattenData(std::string PattID) 
{
	nowEnemyPattenData = CsvDataManager::GetInstance().getDataImpl(nowEnemyPattenData, PattID);
	Object_PlayingAttackTime = nowEnemyPattenData->eAtkCoolDown;

}



//적의 가이드 패턴을 패턴매니저에 등록
void Enemy::SetNowPattern() 
{
	std::vector<int> tmp; // 저장할 벡터 선언

	tmpNode = CsvDataManager::GetInstance().getDataImpl(tmpNode, nowEnemyPattenData->eNodepattern);

	// 널 포인터 체크: tmpNode가 유효한지 확인
	if (tmpNode != nullptr) 
	{
		// tmpNode가 유효할 때만 벡터에 값을 추가
		tmp = tmpNode->Node_Number;

		// AddPattern 함수 호출
		m_PattenManager->AddPattern(nowEnemyPattenData->ePatternID, nowEnemyPattenData->eAtkCoolDown, tmp); // 
	}
}

//처음에 받은 기세 게이지로 복구
void Enemy::ResetSpiritAmount() 
{
	Object_NowSpiritAmount = Object_SpiritAmount / 2.0f;
}

//쿨타임을 세팅하는 함수
// 연격의 여부에 따라서 객체의 쿨타임이 변경됨
void Enemy::SetCoolTime() 
{
	if (nowEnemyPattenData->eComboCoolDown == 0) 
	{
		Object_nowCoolTime = (1.25f - Object_NowSpiritAmount  / Object_SpiritAmount / 2.0f) * Object_CoolTime + nowEnemyPattenData->eAtkCoolDown;
	}
	else 
    {
		Object_nowCoolTime = nowEnemyPattenData->eComboCoolDown;
	}

	if (IsOtherGroggy)
    {
		Object_nowCoolTime = Object_nowCoolTime / 2.0f;
	}
	// 현재 공격중인 시간
	Object_nowTotalCoolTime = Object_nowCoolTime;
}

void Enemy::CalSpiritTime() 
{
	if ( (!isGroggy ) && (!IsOtherGroggy) ) {
		if (Object_OverTimeSpirit >= 1)
		{
			Object_NowSpiritAmount += 0.3f;									 //초당 0.3씩 감소
			Object_OverTimeSpirit = std::fmod(Object_OverTimeSpirit, 1.0f);  //실수형 나머지 연산자
		}

		Object_OverTimeSpirit += GameTime::GetInstance().GetDeltaTime();
	}
}


void Enemy::DiffState() 
{
	if (m_State->GetNowName() != nowStateName)
	{
		preStateName = nowStateName;
		nowStateName = m_State->GetNowName();
	}

	// 상대(플레이어)가 그로기일 때 재는 타이머
	if (IsOtherGroggy)
	{
		OtherGroggyTime += GameTime::GetInstance().GetDeltaTime();
	}

	// 상대 그로기 10초 타임아웃: '신호'만 세우고, 내 Restore는 호출하지 않음
	if (OtherGroggyTime >= 10.0f)
	{
		IsOtherEndGroggy = true;   // 표시만
		OtherGroggyTime = 0.0f;   // 소진
		// RestoreGroggy();        
	}

	// === 내 그로기 판정 ===

	if (isRestore)
	{
		isGroggy = false;
	}
	else if (Object_NowSpiritAmount <= 0.0f)
	{
		isGroggy = true;
		restoredThisCycle = false;   // 새 사이클 시작
		Object_NowSpiritAmount = 0.0f;
		// SetState("Enemy_Groggy"); // 상태 전환은 네 로직에 맞게
	}
	else
	{
		isGroggy = false;
	}

	// 상한 클램프
	if (Object_NowSpiritAmount >= Object_SpiritAmount)
	{
		Object_NowSpiritAmount = Object_SpiritAmount;
	}
}



void Enemy::ResetEnemy() {
	OtherGroggyTime = 0.0f;
	SelectPattern(); // 공격을 했으면 다른 패턴 세팅
	SetCoolTime();
	isPattenCooldown = true;
	SetState("Enemy_Idle"); // 이거 플레이어 아니라 적으로 교체하기
}

void Enemy::CallPlayerHit(int num, Vector2 position, float rotate)
{
	Hiteff->CallAnime(num, position, rotate);
}



//일단 임시로 스테이트마다 스프라이트 설정
void Enemy::StateAct() 
{
	if (nowStateName == "Enemy_Idle") // idle
	{        
		enemy_Idle->SetActive(true);
		enemy_Attack->SetActive(false);
		enemy_Damaged->SetActive(false);
		enemy_Guard->SetActive(false);
	}
	else if (nowStateName == "Enemy_AttackSuccess" || nowStateName == "Enemy_AttackFail") // 적 공격 시 ( 실패 성공 상관없음 )
	{ 
		enemy_Idle->SetActive(false);
		enemy_Attack->SetActive(true);
		enemy_Damaged->SetActive(false);
		enemy_Guard->SetActive(false);
	}
	else if (nowStateName == "Enemy_Hit" || nowStateName == "Enemy_Groggy") // 적 피격이나 그로기 시
	{
		enemy_Idle->SetActive(false);
		enemy_Attack->SetActive(false);
		enemy_Damaged->SetActive(true);
		enemy_Guard->SetActive(false);

	}
	else if (nowStateName == "Enemy_Defence") // 패턴 파회 X, 막음
	{ 
		enemy_Idle->SetActive(false);
		enemy_Attack->SetActive(false);
		enemy_Damaged->SetActive(false);
		enemy_Guard->SetActive(true);
	}
	else if (nowStateName == "Enemy_Dead")	// 적 사망 시 
	{
		enemy_Idle->SetActive(false);
		enemy_Attack->SetActive(false);
		enemy_Damaged->SetActive(true);
		enemy_Guard->SetActive(false);
	}
}

//------------------------------------------------------------------------
// Debug

void Enemy::SetCursorPosition(int x, int y)
{
	COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Enemy::PrintConsole()
{
	SetCursorPosition(0, 0);
	std::cout << "" << std::endl;
	std::cout << "Enemy HP		    : " << Object_Hp << "                                                " << std::endl;
	std::cout << "Enemy Attack		    : " << Object_Attack << "                                                " << std::endl;
	std::cout << "Enemy SpiritAttack          : " << Object_SpiritAttack << "                                                " << std::endl;
	std::cout << "Enemy NowSpiritAmount       : " << Object_NowSpiritAmount << "                                                " << std::endl;
	std::cout << "Enemy Object_CoolTime	    : " << Object_CoolTime << "                                                " << std::endl;
	std::cout << "Enemy nowCoolTime	    : " << Object_nowCoolTime << "                                                " << std::endl;
	std::cout << "Enemy nowTotalCoolTime	    : " << Object_nowTotalCoolTime << "                                                " << std::endl;
	std::cout << "Enemy PlayingAttackTime	    : " << Object_PlayingAttackTime << "                                                " << std::endl;
	std::cout << "Enemy nowState              : " << nowStateName << "                                                " << std::endl;
	std::cout << "Enemy preState              : " << preStateName << "                                                " << std::endl;
	std::cout << "Enemy PatternID              : ";
	if (nowEnemyPattenData != nullptr)
		std::cout << nowEnemyPattenData->ePatternID << "                                                " << std::endl;
	std::cout << "Enemy PattenNode            :  ";
	if (tmpNode != nullptr) {
		for (int i = 0; i < tmpNode->Node_Number.size(); i++)
			std::cout << tmpNode->Node_Number[i] << ", ";
		std::cout << " " << "                                                " << std::endl;
	}

}

void Enemy::ChecKChnageScene()
{
	timer += Singleton<GameTime>::GetInstance().GetDeltaTime();

	if (!isCreatedResult)
	{
		GameObject* obj = new GameObject();
		obj->SetRenderLayer(EngineData::RenderLayer::UI);
		auto comp = obj->AddComponent<StageResult>();
		comp->SetPanelState(ResultPanelState::Win);
		isCreatedResult = true;
	}

	if (timer >= maxTimer)
	{
		Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::MENU);
	}
}

void Enemy::CallGuardEffect(int num, Vector2 vector)
{
	GuardEff->CallAnime(num, vector);
}
