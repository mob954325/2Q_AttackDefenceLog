#include "Enemy.h"
#include <random>
#include <cmath>

#include "Components/Base/GameObject.h"
#include "../CsvData/DataClass/EnemyData.h"
#include "../CsvData/CsvDataManager.h"
#include "../Component/StateController.h"
#include "Utils/GameTime.h"





// 각 값은 해당 함수가 출력 중일때, 각 플레그 변화
//														     
//                    IonStartI 다음 루프ㅣ 공격 노드추가ㅣ			    I
//  isPattenCooldoown I   F   I    T      I     F		  I      F      I  
//



void Enemy::OnStart() {
	m_State = owner->GetComponent<StateController>();
	m_PattenManager = owner->GetQuery()->FindByName("AttackPattenManager")->GetComponent<AttackPatternManager>();
	SetStatData("EI_001");
	OnCreateState();
	m_State->SetState("Enemy_Idle");
	SelectPatten(); //  패턴 세팅
	isPattenCooldown = true;
}



// 업데이트에서 시간 받기???? -> 필요없음, 수정하기!!!
void Enemy::OnUpdate() {
	CalSpiritTime();		// 1초마다 기세게이지 증가
	AddPattenLoop();		// 
	PrintConsole();
	std::cout << "Enemy 루프 확인" << std::endl;
	//CalAttackTimePercent();
}

// onChangePatten에 TransitionTime 변경하기!!!



//이후 StateManager에 추가하는거 만들기
void Enemy::SetState(std::string setStateName) {
	m_State->SetState(setStateName);
}

void Enemy::OnCreateState() {
	m_State->CreateState("Enemy_Idle");    // 평소 상태     

	m_State->CreateState("Enemy_AttackSuccess"); // 공격 성공
	m_State->SetNextState("Enemy_AttackSuccess", "Enemy_Idle");
	m_State->SetTransitionTime("Enemy_AttackSuccess", 1.0f);

	m_State->CreateState("Enemy_AttackFail"); // 공격 성공
	m_State->SetNextState("Enemy_AttackFail", "Enemy_Idle");
	m_State->SetTransitionTime("Enemy_AttackFail", 1.0f);

	m_State->CreateState("Enemy_Hit");     //패턴 파회 X, 맞음
	m_State->SetNextState("Enemy_Hit", "Enemy_Idle");
	m_State->SetTransitionTime("Enemy_Hit", 1.0f);

	m_State->CreateState("Enemy_Defence"); //패턴 파회 X, 막음
	m_State->SetNextState("Enemy_Defence", "Enemy_Idle");
	m_State->SetTransitionTime("Enemy_Defence", 1.0f);

	m_State->CreateState("Enemy_Groggy"); //패턴 파회 X, 막음
	m_State->SetNextState("Enemy_Groggy", "Enemy_Idle");
	m_State->SetTransitionTime("Enemy_Groggy", 1.0f);


	m_State->CreateState("Enemy_Dead");   // 죽음
}


// 플레이어 데이터에는 기세가 없음으로 적을 생성 후, 기세를 매개변수에 넣어주기!!
// 패턴을 세팅하는 것은 처음?

// 매개변수를 통해 데이터의 키값을 받아서 데이터를 찾고 데이터의 값을 적에게 전부 인가
void Enemy::SetStatData(std::string tmp) {
	nowEnemyData = CsvDataManager::GetInstance().getDataImpl(nowEnemyData, tmp);
	Object_ID = nowEnemyData->enemyID;					   // ID
	Object_Name = nowEnemyData->enemyName;				   // 이름
	Object_Hp = nowEnemyData->enemyHealth;		           // 체력
	Object_Attack = nowEnemyData->enemyDamage;			   // 공격력
	Object_SpiritAttack = nowEnemyData->enemySpiritdamage; // 기세 공격력
	Object_DefenseRate = nowEnemyData->enemyGuardRate;	   // 방어율
	Object_SpiritAmount = nowEnemyData->enemySpiritamount; // 기세
	Object_NowSpiritAmount = Object_SpiritAmount / 2.0f;   // 현재 기세 설정
	Difficulty = nowEnemyData->enemyDifficulty;			   // 난이도 -> 아마 필요없을듯?

	PattenID = nowEnemyData->enemyPattern;                 // 적의 패턴 가져오기

	Object_CoolTime = nowEnemyData->enemyCooldown;         // 적의 쿨타임 가져오기;
	Object_nowCoolTime = nowEnemyData->enemyCooldown;	   // 현재 적의 쿨타임
	Object_PlayingAttackTime = 0.0f;					   // 패턴의 입력 대기 시간
	Object_nowPlayingAttackTime = 0.0f;					   // 현재 패턴의 입력 대기 시간
}


// 플래그를 정하는 함수
void Enemy::AddPattenLoop() {
	// isPattenCooldown : T  -> 쿨타임을 계산
	// isPattenCooldown : F  -> 계산 X
	if (isPattenCooldown) {
		// 패턴의 입력대기시간 카운트
		Object_nowCoolTime -= GameTime::GetInstance().GetDeltaTime();
		// 현재 시간이  정해진 대기시간보다 크거나 같을 경우 
		if (Object_nowCoolTime <= 0.0f) {
			isPattenCooldown = false;
		}
	}
	else {
		SelectPatten(); // 패턴 정하기!!
		SetCoolTime();	// 적일때는 수정하기!!
		SetNowPatten(); // 공격대기시간 + 데이터 주기!!
		isPattenCooldown = true;
	}
}


// 배틀 매니저에서 사용될 함수
void Enemy::SelectPatten() {   //각 객체가 사용할 패턴을 고름
	preEnemyPattenData = nowEnemyPattenData;
	while (1) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, PattenID.size());
		int randomValue = dist(gen);
		SetAttackPattenData(PattenID[randomValue - 1]);
		if (preEnemyPattenData != nowEnemyPattenData)
			break;
	}
}

//패턴 ID에 맞는 데이터를 포인터로 가리킴
void Enemy::SetAttackPattenData(std::string PattID) {
	nowEnemyPattenData = CsvDataManager::GetInstance().getDataImpl(nowEnemyPattenData, PattID);
	Object_PlayingAttackTime = nowEnemyPattenData->eAtkCoolDown;

}



//적의 가이드 패턴을 패턴매니저에 등록
void Enemy::SetNowPatten() {
	AllNodePattenClass* tmpNode = nullptr;
	std::vector<int> tmp; // 저장할 벡터 선언

	tmpNode = CsvDataManager::GetInstance().getDataImpl(tmpNode, nowEnemyPattenData->eNodepattern);

	// 널 포인터 체크: tmpNode가 유효한지 확인
	if (tmpNode != nullptr) {
		// tmpNode가 유효할 때만 벡터에 값을 추가
		tmp = tmpNode->Node_Number;
	}
	// AddPattern 함수 호출
	m_PattenManager->AddPattern(nowEnemyPattenData->ePatternID, Object_PlayingAttackTime, tmp);
}




//처음에 받은 기세 게이지로 복구
void Enemy::ResetSpiritAmount() {
	Object_NowSpiritAmount = Object_SpiritAmount / 2.0f;
}

//쿨타임을 세팅하는 함수
// 연격의 여부에 따라서 객체의 쿨타임이 변경됨
void Enemy::SetCoolTime() {
	if (preEnemyPattenData == nullptr) {  //이전 루프가 없을시
			// ( 1 + (현재기세 - 전체기세/2) / 전체기세 /2) * 해당 패턴의 전체 쿨타임
		Object_nowCoolTime = (1 + ((Object_NowSpiritAmount - Object_SpiritAmount / 2.0f) / Object_SpiritAmount)/ 2.0f  ) * Object_CoolTime; 
	}
	else {  // 이전 루프가 있을 시
		if (preEnemyPattenData->eComboCoolDown == 0) {  // 연격이 아닌때
			//  ( 1 + (현재기세 - 전체기세/2) / 전체기세 /2) * 해당 패턴의 전체 쿨타임 + 이전 루프의 공격시간
			Object_nowCoolTime = (1 + ((Object_NowSpiritAmount - Object_SpiritAmount / 2.0f) / Object_SpiritAmount) / 2.0f) * Object_CoolTime + preEnemyPattenData->eAtkCoolDown;
		}
		else {  // 연격일때
			Object_nowCoolTime = nowEnemyPattenData->eComboCoolDown;
		}
	}
	// 현재 공격중인 시간
	Object_PlayingAttackTime = nowEnemyPattenData->eAtkCoolDown;
	Object_nowTotalCoolTime = Object_nowCoolTime;
}

void Enemy::CalSpiritTime() {
	if (Object_OverTimeSpirit >= 1) {
		Object_NowSpiritAmount += 0.3f;									 //초당 0.3씩 감소
		Object_OverTimeSpirit = std::fmod(Object_OverTimeSpirit, 1.0f);  //실수형 나머지 연산자
	}
	Object_OverTimeSpirit += GameTime::GetInstance().GetDeltaTime();
}


void Enemy::SetCursorPosition(int x, int y)
{
	COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Enemy::PrintConsole() {
	SetCursorPosition(0, 0);
	std::cout << "Enemy HP		    : " << Object_Hp << std::endl;
	std::cout << "Enemy Attack		    : " << Object_Attack << std::endl;
	std::cout << "Enemy SpiritAttack          : " << Object_SpiritAttack << std::endl;
	std::cout << "Enemy NowSpiritAmount       : " << Object_NowSpiritAmount << std::endl;
	std::cout << "Enemy Object_CoolTime	    : " << Object_CoolTime << std::endl;
	std::cout << "Enemy nowCoolTime	    : " << Object_nowCoolTime << std::endl;
	std::cout << "Enemy nowTotalCoolTime	    : " << Object_nowTotalCoolTime << std::endl;
	std::cout << "Enemy PlayingAttackTime	    : " << Object_PlayingAttackTime << std::endl;
	std::cout << "Enemy State       : " << m_State->GetNowName() << std::endl;
}


