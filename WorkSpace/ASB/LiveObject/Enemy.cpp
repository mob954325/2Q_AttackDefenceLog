#include "Enemy.h"
#include <random>
#include <cmath>
#include "../CsvData/DataClass/EnemyData.h"
#include "../CsvData/CsvDataManager.h"





// 각  함수가 끝났을때의 플레그의 결과값
//														     외부 입력 +
//                    IonStartI 다음 루프ㅣ 공격 주기 끝 ㅣ 공격 대기시간 I  패턴 변경 I
//  isPathenChange    I   T   I    F	  I     F         I      F        I    T       I 
//  isPattenCooldoown I   F   I    T      I     F		  I      F        I    F	   I
//. isPlayingPath     I   F   I	   F      I     T         I      F        I    F       I
//



void Enemy::OnStart() {
	//플레이어 상태 설정

	// 쿨타임 + 패턴 설정
	SelectPatten(); // 공격을 했으면 다른 패턴 세팅
	SetCoolTime();  // 쿨타임 다시 설정
	

}



// 업데이트에서 시간 받기???? -> 필요없음, 수정하기!!!
void Enemy::OnUpdate() {


	CalSpiritTime();		// 1초마다 기세게이지 감소
	CalAttackTimePercent();
}



// onChangePatten에 TransitionTime 변경하기!!!



//이후 StateManager에 추가하는거 만들기
void Enemy::SetState(std::string setStateName) {
	m_State.SetState(setStateName);
}

void Enemy::OnCreateState() {
	m_State.CreateState("Enemy_Idle");    // 평소 상태     

	m_State.CreateState("Enemy_AttackSuccess"); // 공격 성공
	m_State.SetNextState("Player_AttackSuccess", "Player_Idle");
	m_State.SetTransitionTime("Player_AttackSuccess", 1.0f);

	m_State.CreateState("Player_Hit");     //패턴 파회 X, 맞음
	m_State.SetNextState("Player_Hit", "Player_Idle");
	m_State.SetTransitionTime("Player_Hit", 1.0f);

	m_State.CreateState("Player_Defence"); //패턴 파회 X, 막음
	m_State.SetNextState("Player_Defence", "Player_Idle");
	m_State.SetTransitionTime("Player_Defence", 1.0f);

	m_State.CreateState("Player_Guard");   // 패턴 파회 O
	m_State.SetNextState("Player_Guard", "Player_Idle");
	m_State.SetTransitionTime("Player_Guard", 1.0f);
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
	Difficulty = nowEnemyData->enemyDifficulty;			   // 난이도 -> 아마 필요없을듯?
														   
}



// 플레이어의 가이드 패턴2개를 1개의 벡터에 담아서 리턴
std::vector<int> Enemy::GetNowPatten() {
	AllNodePattenClass* tmpNode = nullptr;
	std::vector<int> tmp; // 저장한 벡터 선언

	tmpNode = CsvDataManager::GetInstance().getDataImpl(tmpNode, nowPlayerPattenData->Node_pattern01); //포인터에  패턴 1 주소 저장			
	for (int i = 0; i < 10; i++) {
		tmp.push_back(tmpNode->Node_Number[i]);  // 벡터에 값 저장
	}

	tmpNode = CsvDataManager::GetInstance().getDataImpl(tmpNode, nowPlayerPattenData->Node_pattern02); //포인터에  패턴 2 주소 저장
	for (int i = 0; i < 10; i++) {
		tmp.push_back(tmpNode->Node_Number[i]);   // ''
	}
	return tmp;
}



// 배틀 매니저에서 사용될 함수
void Enemy::SelectPatten() {   //각 객체가 사용할 패턴을 고름
	// 난수 발생
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, PattenID.size()); // 1 ~ 10 사이의 정수
	int randomValue = dist(gen);

	// 난수를 index로 ID를 찾고 그걸로 포인터에 해당 데이터 주소를 인가 
	SetAttackPattenData(PattenID[randomValue - 1]);
}





//처음에 받은 기세 게이지로 복구
void Enemy::ResetSpiritAmount() {
	Object_NowSpiritAmount = Object_SpiritAmount / 2.0f;
}







void Enemy::SetCoolTime() {
	//  ( 1 + (현재기세 - 전체기세/2) / 전체기세 /2) * 해당 패턴의 전체 쿨타임
	Object_nowCoolTime = (Object_NowSpiritAmount - Object_SpiritAmount / 0.5f) / Object_SpiritAmount / 2 * Object_CoolTime;


}
void Enemy::CalSpiritTime() {
	if (Object_OverTimeSpirit >= 1) {
		Object_NowSpiritAmount -= 0.3f;									 //초당 0.3씩 감소
		Object_OverTimeSpirit = std::fmod(Object_OverTimeSpirit, 1.0f);  //실수형 나머지 연산자
	}
	Object_OverTimeSpirit += SceneDeltaTime;
}

// 플래그를 정하는 함수
void Enemy::ChangePatten() {
	// 패턴이 바뀌었으면 isPattenChange   : T, 다음 루프에 F
	//                   isPattenCooldown : T
	if (prePlayerPattenData != nowPlayerPattenData) {
		prePlayerPattenData = nowPlayerPattenData;
		isPattenChange = true;
		isPattenCooldown = true;
	}
	else {
		isPattenChange = false;
	}

	// 공격 주기 쿨타임이면 isPattenCooldown  : T, 아니면  isPattenCooldown :  F
	//													   isPlayingPatten  :  T
	if (isPattenCooldown) {
		if (Object_nowCoolTime > 0.0f) {
			Object_nowCoolTime -= SceneDeltaTime; // 쿨타임 감소
		}
		else {
			isPattenCooldown = false;
			isPlayingPatten = true;
		}

	}
	else {
		//패턴 출력
	}
	// 패턴의 입력시간이 다 되거나 외부에 입력에 의해서 종료되면 isPlayingPatten : F
	// 패턴의 입력시간이 줄어드는 중이면 isPlayingPatten : T

	if (isPlayingPatten) {
		// 패턴의 입력대기시간 감소
		Object_nowPlayingAttackTime += SceneDeltaTime;
		if (Object_nowPlayingAttackTime >= Object_PlayingAttackTime)
			isPlayingPatten = false;
	}
	else {
		Object_nowPlayingAttackTime;
	}


	//위의 3가지 플래그가 모두 F -> 패턴 변경 -> 다음 루프 -> isPattenChange =  T
	if (!isPattenChange || !isPattenCooldown || !isPlayingPatten) {
		SelectPatten();
	}
}


//공격
void Enemy::CalAttackTimePercent() {
	if (Object_PlayingAttackTime == 0.0f) return;
	enermyTimePercent = (Object_nowPlayingAttackTime / Object_PlayingAttackTime) * 100.0f;

}






void DeciedState(const std::queue<int> tmpqueue);  //큐와 현재 패턴을 비교
void CalStat();        //여기서 계산


