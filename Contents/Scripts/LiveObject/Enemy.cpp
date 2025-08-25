#include "Enemy.h"
#include <random>
#include <cmath>

#include "Components/Base/GameObject.h"
#include "../CsvData/DataClass/EnemyData.h"
#include "../CsvData/CsvDataManager.h"
#include "../Component/StateController.h"
#include "Utils/GameTime.h"

#include "../Engine/Scene/SceneManager.h" // 테스트 씬 전환용 8.09 추가
#include "Objects/Scenes/TitleScene/EffectProgress.h" // 보간 + 
#include "Application/AppPaths.h"
#include "Scripts/GameManager.h"
#include "Objects/Scenes/Stage/StageResult/StageResult.h"
#include "Math/EasingFunction.h"
#include "Math/GameRandom.h"

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
	

	SelectPattern(); //  패턴 세팅
	SetCoolTime();	
	SetBitmap();

	OnCreateState();					// 상태들 구성
	m_State->SetState("Enemy_Idle");	// 초기 상태로 초기화

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
	StateAct();            // 상태 변화시 sprite, transform 변화
	DiffState();            // 이전 상태와 현재 상태를 비교
	// PrintConsole();

	if (nowStateName == "Enemy_Dead") // 적 사망 시 -> 씬 이동
	{
		// 특정 씬 클리어 플래그 활성화
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

		// 사망 연출 및 씬 교체
		if (deadTimer < deadMaxTimer)
		{
			UpdateDeadAnimation();
		}
		else
		{
			CheckChangeScene();
		}
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

// 적 state에 따른 enter, exit 함수들
void Enemy::AtkSucEnter() 
{ 
	Vector2 tmpVect = { -20.0f, 10.0f };
	limitStateMoveTimer = 0.2f; 
	nowStateMoveTimer = 0.0f;
	fromPos = IdlePos;
	toPosX = IdlePos + tmpVect; // 분할 할 필요가 없으면 x에 몰빵
}

void Enemy::DefEnter()
{    
	limitStateMoveTimer = 0.6f; 
	nowStateMoveTimer = 0.0f;
	fromPos = IdlePos;
	toPosX = GetRandomPointOnShrinkingCircle(maxRadius, nowStateMoveTimer, limitStateMoveTimer, IdlePos);
	StatefreqTime = 12.0f;
	nowStatefreqTime = 0.0f;
}

void Enemy::HitEnter()
{    
	limitStateMoveTimer = 0.6f; 
	nowStateMoveTimer = 0.0f;
	fromPos = IdlePos;
	toPosX = GetRandomPointOnShrinkingCircle(maxRadius, nowStateMoveTimer, limitStateMoveTimer, IdlePos);
	StatefreqTime = 12.0f;
	nowStatefreqTime = 0.0f;
}

void Enemy::AtkSucExit()
{
	limitStateMoveTimer = 0.0f;
	nowStateMoveTimer = 0.0f;
	fromPos = {0.0f, 0.0f};
	toPosX = { 0.0f, 0.0f };
	toPosY = { 0.0f, 0.0f };
 }
void Enemy::DefExit(){
	limitStateMoveTimer = 0.0f;
	nowStateMoveTimer = 0.0f; 
	fromPos = { 0.0f, 0.0f };
	toPosX = { 0.0f, 0.0f };
	toPosY = { 0.0f, 0.0f };
	StateProgress = 0.0f;
	StatefreqTime = 0.0f;
	nowStatefreqTime = 0.0f;
	StatefreqTime = 0.0f;
	owner->GetTransform().SetPosition(IdlePos.x, IdlePos.y);
}
void Enemy::HitExit(){
	limitStateMoveTimer = 0.0f; 
	nowStateMoveTimer = 0.0f; 
	fromPos = { 0.0f, 0.0f };
	toPosX = { 0.0f, 0.0f };
	toPosY = { 0.0f, 0.0f };
	StateProgress = 0.0f;
	StatefreqTime = 0.0f;
	nowStatefreqTime = 0.0f;
	StatefreqTime = 0.0f;
	owner->GetTransform().SetPosition(IdlePos.x, IdlePos.y);
}


void Enemy::OnCreateState() 
{
	m_State->CreateState("Enemy_Idle");		
	// 평소 상태 - Default State  
	m_State->CreateState("Enemy_AttackSuccess");				// 공격 성공
	m_State->SetNextState("Enemy_AttackSuccess", "Enemy_Idle");	// Enemy_AttackSuccess -> Enemy_Idle
	m_State->SetTransitionTime("Enemy_AttackSuccess", 1.0f);	// 1.0f 뒤 변경
	//  함수 포인터로 해당 state의 Enter, exit 연결
	m_State->SetOnEnter("Enemy_AttackSuccess", std::bind(&Enemy::AtkSucEnter, this));
	m_State->SetOnExit("Enemy_AttackSuccess", std::bind(&Enemy::AtkSucExit, this));


	//m_State->CreateState("Enemy_AttackFail");					// 공격 실패 
	//m_State->SetNextState("Enemy_AttackFail", "Enemy_Idle");	// Enemy_AttackFail -> Enemy_Idle
	//m_State->SetTransitionTime("Enemy_AttackFail", 1.0f);		// 1.0f 뒤 변경


	m_State->CreateState("Enemy_Hit");							// 패턴 파회 X, 맞음
	m_State->SetNextState("Enemy_Hit", "Enemy_Idle");			// Enemy_Hit -> Enemy_Idle
	m_State->SetTransitionTime("Enemy_Hit", 1.0f);				// 1.0f 뒤 변경
	//  함수 포인터로 해당 state의 Enter, exit 연결
	m_State->SetOnEnter("Enemy_Hit", std::bind(&Enemy::HitEnter, this));
	m_State->SetOnExit("Enemy_Hit", std::bind(&Enemy::HitExit, this));


	m_State->CreateState("Enemy_Defence");						// 패턴 파회 X, 막음
	m_State->SetNextState("Enemy_Defence", "Enemy_Idle");		// Enemy_Defence -> Enemy_Idle
	m_State->SetTransitionTime("Enemy_Defence", 1.0f);			// 1.0f 뒤 변경
	//  함수 포인터로 해당 state의 Enter, exit 연결
	m_State->SetOnEnter("Enemy_Defence", std::bind(&Enemy::DefEnter, this));
	m_State->SetOnExit("Enemy_Defence", std::bind(&Enemy::DefExit, this));


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

	std::wstring enemy_CommonPath = L"\\..\\Resource\\Sprites\\Enemy\\";	// 적의 공통 이미지 경로

	// 적의 이미지 이름 받기
	enemy_IdlePath = enemy_CommonPath + nowEnemyData->enemySprite[0] + L"_fin.png";        
	enemy_AttackPath = enemy_CommonPath + nowEnemyData->enemySprite[1] + L"_fin.png";
	enemy_GuardPath = enemy_CommonPath + nowEnemyData->enemySprite[2] + L"_fin.png";
	enemy_DamagedPath = enemy_CommonPath + nowEnemyData->enemySprite[3] + L"_fin.png";

	eSpriteDamage_Second = nowEnemyData->Enemy_spriteDamage_Second;
}


void Enemy::SetBitmap()
{

	enemy_Idle = owner->AddComponent<BitmapRenderer>();
	enemy_Idle->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + enemy_IdlePath);


	enemy_Attack = owner->AddComponent<BitmapRenderer>();
	enemy_Attack->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + enemy_AttackPath);


	enemy_Damaged = owner->AddComponent<BitmapRenderer>();
	enemy_Damaged->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + enemy_DamagedPath);
	enemy_Damaged->SetClipingPosition
	({
		{EngineData::SceenWidth / 2 - 100.0f, 0.0f},
		{EngineData::SceenWidth / 2 - 100.0f, EngineData::SceenHeight / 2 + 130.0f},
		{(float)EngineData::SceenWidth, EngineData::SceenHeight / 2 + 130.0f},
		{(float)EngineData::SceenWidth, 0.0f}
		}); // 08.21 | 작성자 : 이성호 유니티 좌표계의 중심을 기준으로 우측상단의 화면의 약 1/4 크기의 클리핑 영역 만들기 -> 사망 시 피격 그림으로 사망함

	enemy_Guard = owner->AddComponent<BitmapRenderer>();
	enemy_Guard->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + enemy_GuardPath);

	D2D1_SIZE_F size = enemy_Idle->GetResource()->GetBitmap()->GetSize(); // 크기 같음으로 그냥 해도 될듯?
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);
	owner->GetTransform().SetScale(1.0f, 1.0f); //  크기 맞추기
	IdlePos = { 580.0f, 150.0f };
	owner->GetTransform().SetPosition(IdlePos.x, IdlePos.y);
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

		// tmpNode에서 0의 값을 제거!
		tmp.erase(std::remove(tmp.begin(), tmp.end(), 0), tmp.end());

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
			Object_NowSpiritAmount += eSpriteDamage_Second;					 //초당 0.3씩 감소
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
//Transform도 같이 설정
void Enemy::StateAct() 
{
	
	// 현재 transform 시간이 정해진 transform 시간보다 작다면, 현재 시간에 ++
	if (limitStateMoveTimer >= nowStateMoveTimer)
	{
		nowStateMoveTimer += GameTime::GetInstance().GetDeltaTime();
		StateProgress = nowStateMoveTimer / limitStateMoveTimer;  // 현재시간 / 정해진 시간 -> 0.0f ~ 1.0f 로 정규화
	}
	// 현재 시간이 정해진 시간 이상이라면 전부 한계치에서 고정
	if(limitStateMoveTimer < nowStateMoveTimer){
		nowStateMoveTimer = limitStateMoveTimer;
		StateProgress = 1.0f;
	}

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
		Vector2 nowPos = IdlePos;
		if (StateProgress <= 0.5f) {
			float fromProgress = EffectProgress::NormalizeProgress(StateProgress, 0.0f, 0.5f);
			nowPos = EffectProgress::Lerp(IdlePos, toPosX, fromProgress);
		}
		else {
			float fromProgress = EffectProgress::NormalizeProgress(StateProgress, 0.5f, 1.0f);
			nowPos = EffectProgress::Lerp(toPosX ,IdlePos, fromProgress);
		}
		owner->GetTransform().SetPosition(nowPos.x, nowPos.y); // 두 떨림 합
	}
	else if (nowStateName == "Enemy_Hit" || nowStateName == "Enemy_Groggy") // 적 피격이나 그로기 시
	{
		enemy_Idle->SetActive(false);
		enemy_Attack->SetActive(false);
		enemy_Damaged->SetActive(true);
		enemy_Guard->SetActive(false);
		//if (StateProgress <= 0.5f) {
		float fromProgress = EffectProgress::NormalizeProgress(StateProgress, 0.0f, 1.0f);
		Vector2 nowPos = owner->GetTransform().GetPosition();

		// 상태 주파수 시간에 맞춰 보간값 계산 
		if (nowStatefreqTime < limitStateMoveTimer / StatefreqTime) {
			// 상태 변화 비율에 맞춰 보간을 진행
			nowStatefreqTime += Singleton<GameTime>::GetInstance().GetDeltaTime();

			// 보간의 구간을 0.0f에서 1.0f로 조정
			float fromProgress = EffectProgress::NormalizeProgress(nowStatefreqTime, 0.0f, limitStateMoveTimer / StatefreqTime);

			// 이전 위치에서 목표 위치로 보간
			nowPos = EffectProgress::Lerp(nowPos, toPosX, fromProgress);
		}
		else {
			// 시간이 지나면 원 위의 랜덤 점을 새로 계산
			nowStatefreqTime = fmod(nowStatefreqTime, limitStateMoveTimer / StatefreqTime);

			// 원의 반지름이 줄어들며 랜덤한 점을 계산
			toPosX = GetRandomPointOnShrinkingCircle(maxRadius, StateProgress, 1.0f, IdlePos);
		}

		// 제자리에서 떨림을 적용, 'nowPos'는 현재 위치, 떨림만 적용하여 결과 계산
		owner->GetTransform().SetPosition(nowPos.x, nowPos.y); // 두 떨림 합
		//}
	}
	else if (nowStateName == "Enemy_Defence") // 패턴 파회 X, 막음
	{ 
		enemy_Idle->SetActive(false);
		enemy_Attack->SetActive(false);
		enemy_Damaged->SetActive(false);
		enemy_Guard->SetActive(true);
		float fromProgress = EffectProgress::NormalizeProgress(StateProgress, 0.0f, 1.0f);
		Vector2 nowPos = owner->GetTransform().GetPosition();

		// 상태 주파수 시간에 맞춰 보간값 계산 
		if (nowStatefreqTime < limitStateMoveTimer / StatefreqTime) {
			// 상태 변화 비율에 맞춰 보간을 진행
			nowStatefreqTime += Singleton<GameTime>::GetInstance().GetDeltaTime();

			// 보간의 구간을 0.0f에서 1.0f로 조정
			float fromProgress = EffectProgress::NormalizeProgress(nowStatefreqTime, 0.0f, limitStateMoveTimer / StatefreqTime);

			// 이전 위치에서 목표 위치로 보간
			nowPos = EffectProgress::Lerp(nowPos, toPosX, fromProgress);
		}
		else {
			// 시간이 지나면 원 위의 랜덤 점을 새로 계산
			nowStatefreqTime = fmod(nowStatefreqTime, limitStateMoveTimer / StatefreqTime);

			// 원의 반지름이 줄어들며 랜덤한 점을 계산
			toPosX = GetRandomPointOnShrinkingCircle(maxRadius, StateProgress, 1.0f, IdlePos);
		}

		// 제자리에서 떨림을 적용, 'nowPos'는 현재 위치, 떨림만 적용하여 결과 계산
		owner->GetTransform().SetPosition(nowPos.x, nowPos.y); // 두 떨림 합
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

void Enemy::UpdateDeadAnimation()
{
	deadTimer += Singleton<GameTime>::GetInstance().GetDeltaTime();

	enemy_Damaged->SetCapacity(1 - deadTimer / deadMaxTimer);
	owner->GetTransform().Translate({ 0.0f, -EasingList[EasingEffect::InExpo](deadTimer / deadMaxTimer) * 10.0f });
}

void Enemy::CheckChangeScene()
{
	sceneExittimer += Singleton<GameTime>::GetInstance().GetDeltaTime();

	if (!isCreatedResult)
	{
		GameObject* obj = new GameObject();
		//obj->SetRenderLayer(EngineData::RenderLayer::UI);
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		auto comp = obj->AddComponent<StageResult>();
		comp->SetPanelState(ResultPanelState::Win);

		isCreatedResult = true;
	}

	if (sceneExittimer >= sceneExitMaxTimer)
	{
		Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::MENU);
	}
}

void Enemy::CallGuardEffect(int num, Vector2 vector)
{
	GuardEff->CallAnime(num, vector);
}


// 시간에 따라 반지름을 줄이고 total 시간이 되면 반지름이 0이 되는 함수
Vector2 Enemy::GetRandomPointOnShrinkingCircle(float maxRadius, float currentTime, float totalTime, Vector2 middlePos) {
	// 시간에 따른 반지름 변화
	float radius = maxRadius * (1 - currentTime / totalTime);

	// 반지름이 0인 경우에는 원의 중앙에 위치하도록 처리
	if (radius <= 0.0f) {
		return middlePos; // 반지름이 0이면, 원의 중앙 위치 반환
	}

	// 랜덤 각도 (0 ~ 2파이)
	float angle = GameRandom::RandomRange(0.0f, 2 * 3.141592f); // 0에서 2π 사이의 각도

	// 원 위의 점을 구합니다 (극 좌표 -> 직교 좌표)
	float x = radius * cos(angle);
	float y = radius * sin(angle);

	// 중간 위치(middlePos)를 기준으로 원 위의 점을 반환
	return Vector2(middlePos.x + x, middlePos.y + y);
}